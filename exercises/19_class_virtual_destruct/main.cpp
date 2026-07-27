#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段

    //❌ 非 const 静态成员不能在类内初始化
    // static int num_a = 0;

    static int num_a;

    A() {
        ++num_a;
    }
    //当执行 delete ab;（ab 是 A* 但指向 B 对象）时，如果析构函数非虚，则只会调用 ~A()，不会调用 ~B()，
    //导致 B::num_b 无法减 1，最终断言 B::num_b == 0 失败。
    //如果 B 有动态分配的资源，也会泄漏。

    //当你通过基类指针删除派生类对象时（如 delete ab;），基类析构函数必须是虚的，
    //否则只会调用基类析构函数，派生类的析构函数不会执行，导致资源泄漏或计数错误。
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};
int A::num_a=0;

struct B final : public A {
    // TODO: 正确初始化静态字段
    static int num_b;

    B() {
        ++num_b;
    }
    ~B() {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};
int B::num_b=0;

int main(int argc, char **argv) {
    //构造一个独立的 A 对象,A::num_a =1
    auto a = new A;
    //构造 B 的基类 A 子对象,构造 B 的剩余部分,A::num_a =2
    auto b = new B;
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    //ab 是一个基类指针，编译器看到的是 A*，调用虚函数时会生成通过虚表（vtable）查找的代码。
    //由于对象的实际类型是 B，虚表指向 B::name()，所以返回 'B'
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    //将基类指针 ab 直接转为派生类引用
    B &bb =dynamic_cast<B&>(*ab);
    //bb 是派生类 B 的引用，静态类型明确是 B。
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
