#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过

    //在 C++ 中，constexpr 是用于变量、函数和构造函数的修饰符，表示它们可以在编译期求值，但不能修饰函数参数。
    //函数参数是运行时传入的，不能强制要求编译期常量 
    //int get(constexpr int i) 是错的

    //在 C++ 中，constexpr 只能出现在函数声明的最前面，不能出现在参数列表之后。
    //int get(int i) constexpr{} 是错的

    //FIB 是 constexpr 对象，只能调用 const 成员函数。
    int get(int i) const{
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    //FIB 是 constexpr 对象,调用成员函数必须匹配 const，所以必须有 const 限定符
    //Fibonacci constexpr FIB{...};是对的
    //但是推荐：constexpr Fibonacci FIB{...};
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
