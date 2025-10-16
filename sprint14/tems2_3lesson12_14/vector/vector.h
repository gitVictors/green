#pragma once
#include <cassert>
#include <cstdlib>
// #include <new>
#include <memory>
#include <utility>
#include <type_traits>
#include <algorithm>

template <typename T>
class RawMemory {
public:
    RawMemory() = default;

    // Запрещено копирование для предотвращения двойного освобождения памяти
    RawMemory(const RawMemory&) = delete;
    RawMemory& operator=(const RawMemory&) = delete;

    explicit RawMemory(size_t capacity)
        : buffer_(Allocate(capacity))
        , capacity_(capacity) {
    }

    //Добавлен перемещающий конструктор
    RawMemory(RawMemory&& other) noexcept
        : buffer_(other.buffer_)
        , capacity_(other.capacity_)
    {
        other.buffer_ = nullptr;
        other.capacity_ = 0;
    }

    // Добавлен оператор перемещающего присваивания
    RawMemory& operator=(RawMemory&& other) noexcept {
        if (this != &other) {
            Deallocate(buffer_);
            buffer_ = other.buffer_;
            capacity_ = other.capacity_;
            other.buffer_ = nullptr;
            other.capacity_ = 0;
        }
        return *this;
    }

    ~RawMemory() {
        Deallocate(buffer_);
    }

    T* operator+(size_t offset) noexcept {
        // Разрешается получать адрес ячейки памяти, следующей за последним элементом массива
        assert(offset <= capacity_);
        return buffer_ + offset;
    }

    const T* operator+(size_t offset) const noexcept {
        return const_cast<RawMemory&>(*this) + offset;
    }

    const T& operator[](size_t index) const noexcept {
        return const_cast<RawMemory&>(*this)[index];
    }

    T& operator[](size_t index) noexcept {
        assert(index < capacity_);
        return buffer_[index];
    }

    void Swap(RawMemory& other) noexcept {
        std::swap(buffer_, other.buffer_);
        std::swap(capacity_, other.capacity_);
    }

    const T* GetAddress() const noexcept {
        return buffer_;
    }

    T* GetAddress() noexcept {
        return buffer_;
    }

    size_t Capacity() const {
        return capacity_;
    }

private:
    // Выделяет сырую память под n элементов и возвращает указатель на неё
    static T* Allocate(size_t n) {
        return n != 0 ? static_cast<T*>(operator new(n * sizeof(T))) : nullptr;
    }

    // Освобождает сырую память, выделенную ранее по адресу buf при помощи Allocate
    static void Deallocate(T* buf) noexcept {
        operator delete(buf);
    }

    T* buffer_ = nullptr;
    size_t capacity_ = 0;
};



template <typename T>
class Vector {
public:

    // Оператор копирующего присваивания
    Vector& operator=(const Vector& rhs) {
        if (this != &rhs) {
            if (rhs.size_ > data_.Capacity()) {
                // Если не хватает capacity, создаем новую память
                Vector tmp(rhs);
                Swap(tmp);
            } else {
                // Если capacity достаточно, копируем на месте
                if (size_ > rhs.size_) {
                    // Уничтожаем лишние элементы
                    std::destroy_n(data_.GetAddress() + rhs.size_, size_ - rhs.size_);
                } else if (rhs.size_ > size_) {
                    // Копируем дополнительные элементы
                    std::uninitialized_copy_n(rhs.data_.GetAddress() + size_, rhs.size_ - size_,
                                              data_.GetAddress() + size_);
                }
                // Копируем общую часть
                std::copy_n(rhs.data_.GetAddress(), std::min(size_, rhs.size_), data_.GetAddress());
                size_ = rhs.size_;
            }
        }
        return *this;
    }



    Vector& operator=(Vector&& rhs) noexcept {
        data_.Swap(rhs.data_);
        std::swap(size_, rhs.size_);
        return *this;
    }

    // Метод Swap
    void Swap(Vector& other) noexcept {
        data_.Swap(other.data_);
        std::swap(size_, other.size_);
    }


    Vector () = default;

    Vector(size_t size)
        : data_(size)
        , size_(size)
    {
        std::uninitialized_value_construct_n(data_.GetAddress(), size);
    }

    Vector(const Vector& other)
        : data_(other.size_)
        , size_(other.size_)
    {
        std::uninitialized_copy_n(other.data_.GetAddress(), other.size_, data_.GetAddress());
    }

    Vector(Vector&& other) noexcept
        : data_()
        , size_(other.size_)
    {
        data_.Swap(other.data_);
        other.size_ = 0;
    }

    void Reserve(size_t new_capacity) {

        if (new_capacity <= data_.Capacity()) {
            return;
        }

        RawMemory<T> new_data(new_capacity);

        if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
            std::uninitialized_move_n(data_.GetAddress(), size_, new_data.GetAddress());
        } else {
            std::uninitialized_copy_n(data_.GetAddress(), size_, new_data.GetAddress());
        }

        std::destroy_n(data_.GetAddress(), size_);
        data_.Swap(new_data);
    }

    size_t Size() const noexcept {
        return size_;
    }

    size_t Capacity() const noexcept {
        return data_.Capacity();
    }

    const T& operator[](size_t index) const noexcept {
        return const_cast<Vector&>(*this)[index];
    }

    T& operator[](size_t index) noexcept {
        assert(index < size_);
        return data_[index];
    }

    ~Vector() {
        std::destroy_n(data_.GetAddress(), size_);
    }


    void Resize(size_t new_size) {
        if (new_size > size_) {
            Reserve(new_size);
            std::uninitialized_value_construct_n(data_ + size_, new_size - size_);
        } else if (new_size < size_) {
            std::destroy_n(data_ + new_size, size_ - new_size);
        }
        size_ = new_size;
    }


    void PushBack(T&& value)  {
        EmplaceBack(std::move(value));
    }


    void PushBack(const T& value)  {
        EmplaceBack(value);
    }

    void PopBack() noexcept {
        assert(size_ > 0);
        --size_;
        std::destroy_at(data_ + size_);
    }


    template <typename... Args>
    T& EmplaceBack(Args&&... args) {
        if (size_ == Capacity()) {
            return EmplaceBackWithRealloc(std::forward<Args>(args)...);
        } else {
            // Есть место - строгая гарантия обеспечивается легко
            new (data_ + size_) T(std::forward<Args>(args)...);
            return *(data_ + size_++);
        }
    }

    using iterator = T*;
    using const_iterator = const T*;

    iterator begin() noexcept {
        return data_.GetAddress();
    }
    iterator end() noexcept {
        return data_.GetAddress() + size_;
    }
    const_iterator begin() const noexcept {
        return data_.GetAddress();
    }
    const_iterator end() const noexcept {
        return data_.GetAddress() + size_;
    }
    const_iterator cbegin() const noexcept {
        return begin();
    }
    const_iterator cend() const noexcept {
        return end();
    }


    template <typename... Args>
    iterator Emplace(const_iterator pos, Args&&... args) {

        size_t offset = pos - data_.GetAddress();

        if (size_ == Capacity()) {

            size_t new_capacity = Capacity() == 0 ? 1 : Capacity() * 2;
            RawMemory<T> new_data(new_capacity);

            // Переносим элементы до позиции вставки
            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(data_.GetAddress(), offset, new_data.GetAddress());
            } else {
                std::uninitialized_copy_n(data_.GetAddress(), offset, new_data.GetAddress());
            }

            // Создаем новый элемент
            new (new_data + offset) T(std::forward<Args>(args)...);

            // Переносим элементы после позиции вставки
            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(data_.GetAddress() + offset, size_ - offset,
                                          new_data.GetAddress() + offset + 1);
            } else {
                std::uninitialized_copy_n(data_.GetAddress() + offset, size_ - offset,
                                          new_data.GetAddress() + offset + 1);
            }

            std::destroy_n(data_.GetAddress(), size_);
            data_.Swap(new_data);
            ++size_;
            return data_.GetAddress() + offset;
        } else {
            // Без реаллокации
            if (offset == size_) {
                // Вставка в конец
                new (data_ + size_) T(std::forward<Args>(args)...);
                ++size_;
                return data_.GetAddress() + offset;
            } else {
                // Вставка в середину/начало
                T temp(std::forward<Args>(args)...);
                new (data_ + size_) T(std::move(data_[size_ - 1]));

                for (size_t i = size_ - 1; i > offset; --i) {
                    data_[i] = std::move(data_[i - 1]);
                }

                data_[offset] = std::move(temp);
                ++size_;
                return data_.GetAddress() + offset;
            }
        }
    }

    iterator Erase(const_iterator pos) {
        size_t offset = pos - data_.GetAddress();
        std::destroy_at(data_.GetAddress() + offset);

        for (size_t i = offset; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }

        --size_;
        return data_.GetAddress() + offset;
    }

    iterator Insert(const_iterator pos, const T& value) {
        return Emplace(pos, value);
    }

    iterator Insert(const_iterator pos, T&& value) {
        return Emplace(pos, std::move(value));
    }


private:


    template <typename... Args>
    T& EmplaceBackWithRealloc(Args&&... args) {
        size_t new_capacity = Capacity() == 0 ? 1 : Capacity() * 2;
        RawMemory<T> new_data(new_capacity);

        // Копируем существующие элементы
        if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
            std::uninitialized_move_n(data_.GetAddress(), size_, new_data.GetAddress());
        } else {
            std::uninitialized_copy_n(data_.GetAddress(), size_, new_data.GetAddress());
        }

        // Создаем новый элемент
        T* new_element = new (new_data + size_) T(std::forward<Args>(args)...);

        // Завершаем операцию
        std::destroy_n(data_.GetAddress(), size_);
        data_.Swap(new_data);
        ++size_;

        return *new_element;
    }



    RawMemory<T> data_;
    size_t size_ = 0;


};
