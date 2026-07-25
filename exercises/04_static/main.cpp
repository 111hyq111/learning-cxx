#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？

// 这里的 static 表示 func 只在这个 .cpp 文件内部可见，其他源文件（翻译单元）无法调用它。
// 作用：封装，防止在链接阶段与其它文件中的同名函数冲突。
static int func(int param) {
    // 这条语句只在第一次调用 func 时执行，用当时传入的 param 值初始化 static_。
    // 之后所有调用都会跳过初始化，static_ 保持上一次修改后的值
    static int static_ = param;
    // std::cout << "static_ = " << static_ << std::endl;
    // 这是后置递增：先返回 static_ 当前值，然后将 static_ 加 1。
    return static_++;
}

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}
