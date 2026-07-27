#include "../exercise.h"

// READ: 派生类 <https://zh.cppreference.com/w/cpp/language/derived_class>

//在 C++ 中，struct 和 class  它们都用来定义类
//struct：成员和基类默认是 public（公有）。
//class：成员和基类默认是 private（私有）。
static int i = 0;

struct X {
    int x;

    X(int x_) : x(x_) {
        std::cout << ++i << ". " << "X(" << x << ')' << std::endl;
    }
    X(X const &other) : x(other.x) {
        std::cout << ++i << ". " << "X(X const &) : x(" << x << ')' << std::endl;
    }
    ~X() {
        std::cout << ++i << ". " << "~X(" << x << ')' << std::endl;
    }
};
struct A {
    int a;

    A(int a_) : a(a_) {
        std::cout << ++i << ". " << "A(" << a << ')' << std::endl;
    }
    A(A const &other) : a(other.a) {
        std::cout << ++i << ". " << "A(A const &) : a(" << a << ')' << std::endl;
    }
    ~A() {
        std::cout << ++i << ". " << "~A(" << a << ')' << std::endl;
    }
};
struct B : public A {
    X x;
    //当创建 B 的对象时，内存里实际上是先有一个 A 的部分，然后才是 B 自己的部分（比如成员 X x）。

    //如果不写 A(1)，编译器会尝试调用 A 的默认构造函数（A()），
    //但 A 并没有默认构造函数（因为你自己定义了 A(int)），代码就会编译报错。
    B(int b) : A(1), x(b) {
        std::cout << ++i << ". " << "B(" << a << ", X(" << x.x << "))" << std::endl;
    }
    B(B const &other) : A(other.a), x(other.x) {
        std::cout << ++i << ". " << "B(B const &) : A(" << a << "), x(X(" << x.x << "))" << std::endl;
    }
    ~B() {
        std::cout << ++i << ". " << "~B(" << a << ", X(" << x.x << "))" << std::endl;
    }
};

int main(int argc, char **argv) {
    X x = X(1);
    A a = A(2);
    B b = B(3);

    // TODO: 补全三个类型的大小
    static_assert(sizeof(X) == 4, "There is an int in X");
    static_assert(sizeof(A) == 4, "There is an int in A");
    static_assert(sizeof(B) == 8, "B is an A with an X");

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    // 这是不可能的，A 无法提供 B 增加的成员变量的值
    // B ba = A(4);

    //A ab = B(5);  // 看起来像“赋值”，但实际上是“构造”
    //虽然这里用了 =，但因为它是在定义变量 ab 的同时进行初始化，所以编译器会把它解释为：
    //A ab( B(5) ); // 调用 A 的复制构造函数


    // 这也是不可能的，因为 A 是 B 的一部分，就好像不可以把套娃的外层放进内层里。

    //复制构造函数只会拷贝 A 的部分（即基类子对象 a），完全忽略派生类 B 独有的成员（如 X x）。
    A ab = B(5);// 然而这个代码可以编译和运行！
    // THINK: 观察打印出的信息，推测把大象放进冰箱分几步？
    // THINK: 这样的代码是“安全”的吗？
    // NOTICE: 真实场景中不太可能出现这样的代码

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    return 0;
}
