#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    // TODO: 调用 `std::accumulate` 计算：
    //       - 数据类型为 float；
    //       - 形状为 shape；
    //       - 连续存储；
    //       的张量占用的字节数
    // int size =

    //std::accumulate有四个参数
    //第一个参数：指向数组 shape 的第一个元素（即 1），定义累加的起始位置。
    //第二个参数：指向数组 shape 的最后一个元素之后的位置（即 shape+4），表示累加范围结束。
    //第三个参数：初始累加值，也是返回值的类型（int）。因为这里做乘法，初始值应为 1（乘法单位元）。若做加法，初始值应为 0。
    //第四个参数：累加操作。接受两个参数（当前累加值和当前元素），返回新累加值。std::multiplies<int> 实现乘法，即 acc = acc * value。
    
    //如果shape是vector, shape.begin()     shape.end()
    //如果shape是数组， std::begin(shape) std::end(shape)
    int total_elements = std::accumulate(
    std::begin(shape), std::end(shape),
    1,
    [](int a, int b) { return a * b; }
    );
    int size=total_elements*sizeof(DataType);
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
