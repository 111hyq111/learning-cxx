#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

//std::unique_ptr<Resource> 是一个 独占所有权的智能指针，
//它确保 Resource 对象在任何时刻只能被一个指针拥有。
//当 unique_ptr 被销毁（如超出作用域或赋值 nullptr）时，它会自动 delete 所管理的对象，防止内存泄漏。
using Unique = std::unique_ptr<Resource>;
//当调用 reset(R1) 时，R1 被移动进参数 ptr。
//ptr 记录 'r'。
//然后创建并返回一个全新的 Resource（记作 R2），其 _records 初始为空。
//函数返回时，ptr 被销毁，释放 R1（触发 R1 的析构记录）。
//返回的 R2 由外层调用者接管。
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');
    //std::make_unique<Resource>()
    //在堆上动态分配一个 Resource 对象
    //调用 Resource 的默认构造函数来初始化该对象。
    //返回一个 std::unique_ptr<Resource>，它独占管理这个新对象。
    
    //return 语句：先计算返回值（即新创建的 R2 的 unique_ptr）。
    //             然后，函数返回，局部变量 ptr 被销毁。
    //             销毁 ptr 时，因为 ptr 拥有 R1，所以 R1 被 delete，触发析构。
    //             新资源 R2 被返回给调用者，继续存活。
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    //ptr 是一个局部变量，当函数返回时，编译器会尝试将其视为右值（因为它是即将销毁的局部对象），从而触发 移动构造。
    //移动构造会将 ptr 内部管理的裸指针（指向 R1 的地址）转移给返回值（一个临时的 std::unique_ptr）。
    //返回值（临时 std::unique_ptr）现在拥有了 R1。
    //这个临时对象会继续存在，直到外层表达式或函数使用它。
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    forward(drop(reset(forward(forward(reset(nullptr))))));
    //这一行将 全局变量 RECORDS 中的所有记录字符串“移动”到 problems[1] 中，而不是复制。
    //执行后，problems[1] 拥有了 RECORDS 原先的数据，而 RECORDS 变为空（有效但未指定的状态）。
    problems[1] = std::move(RECORDS);
    //problems[1] 表达式：forward(drop(reset(forward(forward(reset(nullptr))))))
    //内层 reset(nullptr) 创建 R1
    //两次 forward 记录 'f'，R1._records = "ff"。
    //用 reset(R1)：reset 先记录 'r'（_records = "ffr"）。
    //              然后创建新资源 R2。
    //              在函数返回时，参数 ptr（拥有 R1）被销毁，R1 析构，将 "ffr" 推入 RECORDS。
    //接着调用 drop(R2)：drop 记录 'd'，销毁 R2，析构推入 "d"。

    //顺序差异点：R1 的析构（推入 "ffr"）和 R2 的析构（推入 "d"）谁先发生？
    //在 GCC/Clang 中，R2 可能在 R1 完全销毁之前就被 drop 处理并析构，所以先记录 "d"，后记录 "ffr"。
    //在 MSVC 中，R1 可能在 reset 返回时立即析构，先记录 "ffr"，后记录 "d"。

    //通过下面的遍历确定正确的析构顺序
    for(auto &p:problems[1])
        std::cout<<p<<std::endl;

    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"d", "ffr"},
        {"d", "d", "r"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
