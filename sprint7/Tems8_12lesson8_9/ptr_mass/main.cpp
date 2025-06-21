#include <cassert>
#include <cstdlib>
#include <utility>  // Для std::swap

template <typename Type>
class ArrayPtr {
public:
    ArrayPtr() = default;

    explicit ArrayPtr(size_t size) {
        raw_ptr_ = (size == 0) ? nullptr : new Type[size];
    }

    explicit ArrayPtr(Type* raw_ptr) noexcept {
        raw_ptr_ = raw_ptr;
    }

    ArrayPtr(const ArrayPtr&) = delete;

    ~ArrayPtr() {
        delete[] raw_ptr_;
    }

    ArrayPtr& operator=(const ArrayPtr&) = delete;

    [[nodiscard]] Type* Release() noexcept {
        Type* ptr = raw_ptr_;
        raw_ptr_ = nullptr;
        return ptr;
    }

    Type& operator[](size_t index) noexcept {
        return raw_ptr_[index];
    }

    const Type& operator[](size_t index) const noexcept {
        assert(raw_ptr_);
        return raw_ptr_[index];
    }

    explicit operator bool() const {
        return raw_ptr_ != nullptr;
    }

    Type* Get() const noexcept {
        return raw_ptr_;
    }

    void swap(ArrayPtr& other) noexcept {
        std::swap(raw_ptr_, other.raw_ptr_);
    }

private:
    Type* raw_ptr_ = nullptr;
};

int main() {
    ArrayPtr<int> numbers(10);
    const auto& const_numbers = numbers;

    numbers[2] = 42;
    assert(const_numbers[2] == 42);
    assert(&const_numbers[2] == &numbers[2]);

    assert(numbers.Get() == &numbers[0]);

    ArrayPtr<int> numbers_2(5);
    numbers_2[2] = 43;

    numbers.swap(numbers_2);

    assert(numbers_2[2] == 42);
    assert(numbers[2] == 43);
}
