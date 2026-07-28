#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // TODO: 调用 `std::transform`，将 `v` 中的每个元素乘以 2，并转换为字符串，存入 `ans`
    // std::vector<std::string> ans
    std::vector<std::string> ans(val.size());
    //std::transform() 有四个参数
    //第一个参数：指向输入范围（val 容器）的起始位置的只读迭代器。
    //第二个参数：指向输入范围结束位置（最后一个元素之后）的只读迭代器。
    //第三个参数：指向输出范围（ans 容器）的起始位置的可写迭代器。转换后的结果将从这里开始存放。
    //第四个参数：对每个输入元素 x 执行的操作

    //begin() / end() 返回的是普通迭代器（可读写）
    //cbegin() / cend()是只读迭代器
    std::transform(val.cbegin(), val.cend(),
               ans.begin(),
               [](int x) { return std::to_string(x * 2); });

    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}
