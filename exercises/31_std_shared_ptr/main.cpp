#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    //在堆上动态分配一个 int 对象，并将其初始化为 10
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};
    //共有 4 个 shared_ptr 指向该 int 对象 shared、ptrs[0]、ptrs[1]、ptrs[2]

    //std::weak_ptr<int> observer = shared; 创建了一个名为 observer 的 std::weak_ptr<int>，
    //它观察由 shared（一个 std::shared_ptr<int>）管理的 int 对象，但不增加引用计数
    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");
    //释放 ptrs[0] 的引用，引用计数减 1，变为 3
    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");
    //创建了一个全新的 int 对象（值为 10），
    //ptrs[2] 现在指向新对象，不再指向原对象。原对象的引用计数再减 1，变为 1（仅 shared 持有）。
    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    // shared 转移给 ptrs[2]，shared 变为空
    //移动后，ptrs[2] 接管 shared 的引用，但引用计数不变
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "");
    //std::ignore 是一个特殊的占位对象，它的赋值操作被定义为不做任何事，也不会存储值。
    //当你写 std::ignore = std::move(ptrs[0]); 时，ptrs[0] 本身不会被修改，它仍然持有原 int 对象。
    //因此，引用计数保持不变。
    std::ignore = std::move(ptrs[0]);
    std::cout << "use_count after move: " << observer.use_count() << std::endl;
    // 自我移动赋值，无变化
    ptrs[1] = std::move(ptrs[1]);
    //ptrs[2] 转移给 ptrs[1] ptrs[2]变为空，计数减1 → 1
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "");
    //observer.lock() 返回一个指向原对象的 shared_ptr，赋值给 shared。引用计数从 1 增加到 2（shared + ptrs[1]）。
    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
