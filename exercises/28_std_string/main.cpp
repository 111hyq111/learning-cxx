#include "../exercise.h"
#include <string>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    //std::string_literals 命名空间中定义了 用户定义字面量运算符 operator ""s，
    //它接受一个字符串字面量，返回一个 std::string 对象。
    //引入该命名空间后，编译器在遇到 "任意文本"s 时，会调用这个运算符，生成一个临时 std::string。
    using namespace std::string_literals;
    auto hello = "Hello"s;
    auto world = "world";
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    //std::is_same_v 接受两个类型作为模板参数，如果它们相同则结果为 true，否则为 false
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    //"world" 是 C 风格字符串字面量，类型是 const char[6]，
    //但在声明变量时使用 auto，类型推导会退化为指针，因此 world 的类型是 const char*，而不是数组类型。。
    ASSERT((std::is_same_v<decltype(world), const char*>), "Fill in the missing type.");
    // TODO: 将 `?` 替换为正确的字符串
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    return 0;
}
