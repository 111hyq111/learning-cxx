#include "../exercise.h"
#include <cstring>
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        ASSERT(vec.size() == 5, "Fill in the correct value.");
        // THINK: `std::vector` 的大小是什么意思？与什么有关？
        //sizeof(vector)：在 libstdc++（GCC）中，vector 通常包含三个指针（_M_start, _M_finish, _M_end_of_storage），
        //大小为 24 字节（64 位）    64 位系统的内存地址宽度就是 64 位（即 8 字节）
        //任何指针（无论指向什么类型）都占用 8 字节来存储这个地址。 3*8=24字节
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
            double ans[]{1, 2, 3, 4, 5};
            ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
        }
        {
            vec.push_back(6);
            ASSERT(vec.size() == 6, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
            vec.pop_back();
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        }
        {
            vec[4] = 6;
            ASSERT(vec[0] == 1, "Fill in the correct value.");
            ASSERT(vec[1] == 2, "Fill in the correct value.");
            ASSERT(vec[2] == 3, "Fill in the correct value.");
            ASSERT(vec[3] == 4, "Fill in the correct value.");
            ASSERT(vec[4] == 6, "Fill in the correct value.");
        }
        {
            // THINK: `std::vector` 插入删除的时间复杂度是什么？
            //vec.insert(1, 1.5); 是错的，必须使用迭代器
            vec.insert(vec.begin()+1, 1.5);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}), "Make this assertion pass.");
            //vec.erase(3); 是错的，必须使用迭代器
            vec.erase(vec.begin()+3);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 4, 6}), "Make this assertion pass.");
        }
        {
            //vec.shrink_to_fit() 是 std::vector 的成员函数，用于请求释放多余的内存容量，
            //使 capacity() 尽可能接近 size()，
            vec.shrink_to_fit();
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
            //vec.clear() 会销毁当前 vector 中的所有元素，将 size() 变为 0，
            //但不会释放已分配的内存（即 capacity() 保持不变）。
            vec.clear();
            ASSERT(vec.empty(), "`vec` is empty now.");
            ASSERT(vec.size() == 0, "Fill in the correct value.");
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
        }
    }
    {
        std::vector<char> vec(48, 'z'); // TODO: 调用正确的构造函数
        ASSERT(vec[0] == 'z', "Make this assertion pass.");
        ASSERT(vec[47] == 'z', "Make this assertion pass.");
        ASSERT(vec.size() == 48, "Make this assertion pass.");
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        {
            auto capacity = vec.capacity();
            //vec.resize(16) 会将向量的大小（size）更改为 16。
            //如果新大小小于当前大小，它会移除末尾多余的元素；
            //如果新大小大于当前大小，则会插入默认构造的元素。
            //在代码中，vec 初始大小为 48，调用 resize(16) 后，
            //末尾的 32 个元素被销毁，size 变为 16，但 capacity 保持不变（仍为 48），
            //因为 resize 不会主动释放已分配的内存。
            vec.resize(16);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == 48, "Fill in a correct identifier.");
        }
        {
            //vec.reserve(256) 会确保容器的容量（capacity）至少为 256，
            //如果当前容量小于 256，则重新分配内存以容纳至少 256 个元素。size() 保持不变，因为不会插入或删除任何元素。
            vec.reserve(256);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
        }
        {
            vec.push_back('a');
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            ASSERT(vec.size() == 20, "Fill in the correct value.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
            ASSERT(vec[15] == 'z', "Fill in the correct value.");
            ASSERT(vec[16] == 'a', "Fill in the correct value.");
            ASSERT(vec[17] == 'b', "Fill in the correct value.");
            ASSERT(vec[18] == 'c', "Fill in the correct value.");
            ASSERT(vec[19] == 'd', "Fill in the correct value.");
        }
    }

    return 0;
}
