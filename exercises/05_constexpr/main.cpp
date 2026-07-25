#include "../exercise.h"

constexpr unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci(i - 1) + fibonacci(i - 2);
    }
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……

    //constexpr auto	编译时常量，类型自动推导
    //编译时计算 fibonacci(90)，递归调用次数极其庞大，导致编译器的 constexpr 操作数限制被触发（默认 3355 万次）
    //解决方案很简单：去掉 constexpr 关键字，让 fibonacci(ANS_N) 在运行时计算。这样代码就能编译通过
    constexpr auto ANS_N = 90;
    auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
