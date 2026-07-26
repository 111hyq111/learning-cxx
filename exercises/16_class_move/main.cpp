#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]{0,1}), cached(1) {}

    // TODO: 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept:cache(other.cache),cached(other.cached){
        other.cache=nullptr;
        other.cached=0;
    };

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    // 重构了 “=”操作，返回的是引用
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        //other是引用，this是指针，(*this)将指针变为引用，(&other)将引用变为指针

        // other != *this 是在比较两个对象的内容
        //假设你有两个不同的对象 a 和 b，它们都缓存了相同的斐波那契数列（比如都算到了第10项，内容完全一样）
        // other != *this,代码会跳过移动
        //但 a 和 b 是不同的对象（内存地址不同），应该执行移动
        //所以防止自赋值要比较地址（指针）即 &other!=this
        if(&other!=this){  // ✅ 防止自赋值
            delete[] cache; // 释放自身旧资源
            cache=other.cache;  // 接管源资源
            cached=other.cached;
            other.cache=nullptr; // 源对象置空
            other.cached=0;
        }
        return *this;

    };

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache;
    };

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        while(cached<i)
        {
            cached++;
            cache[cached]=cache[cached-1]+cache[cached-2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    // 调用移动构造
    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    // 调用移动赋值
    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
