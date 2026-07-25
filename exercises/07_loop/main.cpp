#include "../exercise.h"
// 特性	            加 static（静态局部变量）	                不加 static（普通局部变量）

// 存储期	        静态存储期：变量在程序启动时分配，              自动存储期：变量在每次进入函数时分配，
//                 在程序结束时销毁，生命周期贯穿整个              在函数退出时销毁，生命周期仅限于单次
//                 程序运行。	                                  函数调用。

// 初始化时机	    仅第一次执行声明时初始化一次                    每次进入函数时都会初始化（如果提供了初始值）
//               （编译时静态初始化或第一次运行时动态初始化）。     或变为未定义状态（如果未初始化）。
//                后续调用跳过初始化，保持之前的值。

// 内存位置	    存储在静态存储区（.data 或 .bss 段）。	        存储在栈（stack）上。

// 函数调用间	    保持状态：函数多次调用之间，	                无状态：每次调用都是全新的变量，与之前的调用无关。
// 的状态          变量的值会保留，可用于缓存、计数器等。

// 可见性	        作用域仅限于函数内部（局部），                  作用域和生命周期都仅限于函数内部。
//                 但生命周期是全局的。

// 线程安全	    在多线程环境下，不加同步机制可能                每次调用独立，通常更易于线程安全（但也不绝对）。
//                 产生数据竞争（非线程安全）。	

// TODO: 改正函数实现，实现正确的缓存优化斐波那契计算
// THINk: 这个函数是一个纯函数（pure function）吗？ 不是一个纯函数
// READ: 纯函数 <https://zh.wikipedia.org/wiki/%E7%BA%AF%E5%87%BD%E6%95%B0>
static unsigned long long fibonacci(int i) {
    // TODO: 为缓存设置正确的初始值

    // 静态缓存，初始化为 {0, 1}，其余元素自动置 0
    static unsigned long long cache[96]={0,1};
    // 记录当前已计算到的最大索引（初始为 1，因为 cache[0] 和 cache[1] 已知）
    static int cached=1;
    // TODO: 设置正确的循环条件
    if(i>cached){
        for (int j=cached+1; j<=i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        // 更新已缓存的最大索引
        cached=i;
    }
    return cache[i];
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib90 = fibonacci(90);
    std::cout << "fibonacci(90) = " << fib90 << std::endl;
    ASSERT(fib90 == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
    return 0;
}
