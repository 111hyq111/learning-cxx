#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// TODO: 正确调用构造函数
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    //上面这行注释提醒：std::vector<bool> 的对象大小（sizeof）不是固定的，
    //它会随着编译器、标准库版本、构建配置（如是否开启调试模式）以及操作系统平台的不同而变化
    //根据下面这行的输出，确定sizeof(vec)等于多少
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 40, "Fill in the correct value.");
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // ref 的类型是 std::vector<bool>::reference，是一个 代理引用,不是 bool&
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`");
        //ref 是 vec[30] 的代理引用，修改 ref 就等于修改 vec[30]。
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // THINK: WHAT and WHY?
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}
