#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    if(i>cache.cached){
        for (int j=cache.cached+1; j<=i; ++j) {
            cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];
        }
        cache.cached=i;
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    // FibonacciCache fib;

    //C++ 不允许直接用一个数组给另一个数组赋值
    // unsigned long long cache[16]={0,1};
    // fib.cache=cache;

    //下面这个初始化可以通过
    //FibonacciCache fib; 是未初始化的，其成员值是不确定的，所以必须显式设置每个成员
    //加上 for (int i = 2; i < 16; ++i) fib.cache[i] = 0; // 可选，因为结构体未初始化时内容是随机的
    // fib.cache[0]=0;
    // fib.cache[1]=1;
    // int cached=1;
    // fib.cached=cached;

    //使用聚合初始化
    FibonacciCache fib={
        {0,1},
        1
    };

    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
