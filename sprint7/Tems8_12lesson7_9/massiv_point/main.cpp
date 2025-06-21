#include <cassert>
#include <vector>

template <typename T>
void ReverseArray(T* start, size_t size) {
    if (size == 0 && start != nullptr)
        return ;

    T* mss = new T[size];
    //копировать
    for (int i =0; i < size; ++i){
        mss[i] = start[i];
    }
    //разворот
    for (int i = 0; i < size; ++i){
        start [(size-1)-i] = mss [i];
    }

    delete [] mss;
}

int main() {
    using namespace std;

    vector<int> v = {1, 2};
    ReverseArray(v.data(), v.size());
    assert(v == (vector<int>{2, 1}));
}
