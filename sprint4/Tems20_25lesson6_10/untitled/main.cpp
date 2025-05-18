#include "post.h"
#include <cassert>

void TestEmpty() {
    Post post;
    assert(0 == post.GetUnderlying().capacity());
    post.SetPostCapacity(10);
    assert(0 == post.GetUnderlying().size());
    assert(10 <= post.GetUnderlying().capacity());
}

void Test1() {
    Post post;
    assert(0 == post.GetUnderlying().capacity());
    post.SetPostCapacity(10);
    size_t free = post.GetFreePlace();
    assert(10 <= free);
    for (size_t n = 0; n < free; ++n) {
        post.AddPackage("s1", "a1", 111);
    }
    assert(free == post.GetUnderlying().size());
    assert(free == post.GetUnderlying().capacity());
}

void TestChangeCapacityUp() {
    Post post;
    assert(0 == post.GetUnderlying().capacity());
    post.SetPostCapacity(10);
    size_t free = post.GetFreePlace();
    for (size_t n = 0; n < free; ++n) {
        post.AddPackage("s1", "a1", 111);
    }
    post.AddPackage("s1", "a1", 111);
    assert(free == post.GetUnderlying().size());
    assert(free == post.GetUnderlying().capacity());

    post.SetPostCapacity(free + 1);
    post.AddPackage("s1", "a1", 111);
    assert(free + 1 == post.GetUnderlying().size());
}

void TestChangeCapacityDown() {
    Post post;
    assert(0 == post.GetUnderlying().capacity());
    post.SetPostCapacity(10);
    for (size_t n = 0; n < 6; ++n) {
        post.AddPackage("s1", "a1", 111);
    }
    assert(6 == post.GetUnderlying().size());

    post.SetPostCapacity(5);

    assert(5 == post.GetUnderlying().size());
}

int main() {
    TestEmpty();
    Test1();
    TestChangeCapacityUp();
    TestChangeCapacityDown();
}
