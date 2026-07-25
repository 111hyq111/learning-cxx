#include "../exercise.h"

// READ: 数组 <https://zh.cppreference.com/w/cpp/language/array>

//显式初始化前两个元素：arr[0] = 0，arr[1] = 1。  其余元素自动初始化为 0
unsigned long long arr[90]{0, 1};
unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            // TODO: 补全三目表达式缺失的部分
            //检查 arr[i] 是否非零（即是否已缓存计算结果）
            //若已缓存，直接返回缓存值。 
            //否则：递归计算，将结果存入 arr[i]，并返回该值。
            return arr[i] ? arr[i] : (arr[i] = fibonacci(i - 1) + fibonacci(i - 2));
    }
}

int main(int argc, char **argv) {
    // TODO: 为此 ASSERT 填写正确的值
    //arr 有 90 个元素，每个 unsigned long long 为 8 字节
    ASSERT(sizeof(arr) == 720, "sizeof array is size of all its elements");
    // ---- 不要修改以下代码 ----
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(20) == 6765, "fibonacci(20) should be 6765");
    ASSERT(fibonacci(80) == 23416728348467685, "fibonacci(80) should be 23416728348467685");
    return 0;
}
