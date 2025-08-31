#include <cassert>
#include <cstddef>  // нужно для nullptr_t
#include <utility>

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
    T* value_;
public:
    UniquePtr() noexcept  : value_(nullptr) {}
    explicit UniquePtr(T* ptr) noexcept : value_(ptr)
    {}



    // Конструктор перемещения
    UniquePtr(UniquePtr&& other) noexcept : value_(other.value_) {
        other.value_ = nullptr;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Оператор присваивания для nullptr
    UniquePtr& operator=(nullptr_t) noexcept {
        Reset(nullptr);
        return *this;
    }

    // Move-оператор присваивания
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            Reset(nullptr); // Освобождаем текущий ресурс
            value_ = other.value_;
            other.value_ = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~UniquePtr() {
        delete value_;
    }

    // Оператор разыменования
    T& operator*() const noexcept {
        return *value_;
    }

    // Оператор доступа к членам
    T* operator->() const noexcept {
        return value_;
    }

    // Функция Release - отменяет владение и возвращает указатель
    T* Release() noexcept {
        T* released_ptr = value_;
        value_ = nullptr;
        return released_ptr;
    }


    // Функция Reset - захватывает новый указатель
    void Reset(T* ptr = nullptr) noexcept {
        if (value_ != ptr) {
            delete value_;
            value_ = ptr;
        }
    }

    // Функция Swap - обменивается содержимым с другим указателем
    void Swap(UniquePtr& other) noexcept {
        std::swap(value_, other.value_);
    }

    // Функция Get - возвращает указатель
    T* Get() const noexcept {
        return value_;
    }

    // Оператор bool для проверки на пустоту
    explicit operator bool() const noexcept {
        return value_ != nullptr;
    }

};

struct Item {
    static int counter;
    int value;
    Item(int v = 0)
        : value(v)
    {
        ++counter;
    }
    Item(const Item& other)
        : value(other.value)
    {
        ++counter;
    }
    ~Item() {
        --counter;
    }
};

int Item::counter = 0;

void TestLifetime() {
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        assert(Item::counter == 1);

        ptr.Reset(new Item);
        assert(Item::counter == 1);
    }
    assert(Item::counter == 0);

    {
        UniquePtr<Item> ptr(new Item);
        assert(Item::counter == 1);

        auto rawPtr = ptr.Release();
        assert(Item::counter == 1);

        delete rawPtr;
        assert(Item::counter == 0);
    }
    assert(Item::counter == 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    assert(ptr.Get()->value == 42);
    assert((*ptr).value == 42);
    assert(ptr->value == 42);
}

int main() {
    TestLifetime();
    TestGetters();
}
