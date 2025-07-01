#pragma once

#include <cassert>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

#include "array_ptr.h"

// Класс-обертка для резервирования памяти
struct ReserveProxyObj {
    size_t capacity;
    explicit ReserveProxyObj(size_t cap) : capacity(cap) {}
};

ReserveProxyObj Reserve(size_t capacity_to_reserve) {
    return ReserveProxyObj(capacity_to_reserve);
};

template <typename Type>
class SimpleVector {
public:
    using Iterator = Type*;
    using ConstIterator = const Type*;


    // Конструктор с резервированием памяти
    explicit SimpleVector(ReserveProxyObj proxy)
        : items_(proxy.capacity)
        , size_(0)
        , capacity_(proxy.capacity)
    {}

    SimpleVector() noexcept = default;

    // Создаёт вектор из size элементов, инициализированных значением по умолчанию
    explicit SimpleVector(size_t size)
        : items_(size)  // Инициализация массива заданного размера
        , size_(size)   // Установка текущего размера вектора
        , capacity_(size) // Установка текущей вместимости вектора
    {
        std::fill(items_.Get(), items_.Get() + size, Type{});
    }

    // Создаёт вектор из size элементов, инициализированных значением value
    SimpleVector(size_t size, const Type& value):
        items_(size)  // Инициализация массива заданного размера
        , size_(size)   // Установка текущего размера вектора
        , capacity_(size) // Установка текущей вместимости вектора
    {

        for (size_t i = 0; i < size; ++i )
            items_[i] = value;
    }

    // Создаёт вектор из std::initializer_list
    SimpleVector(std::initializer_list<Type> init) :
        items_(init.size()),
        size_( init.size()),
        capacity_ (init.size())
    {
        if (init.size() > 0) {
            std::copy(init.begin(), init.end(), items_.Get());
        }
    }
    //------------------------------------------------------

    // Резервирование памяти
    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }

        ArrayPtr<Type> new_items(new_capacity);
        std::copy(begin(), end(), new_items.Get());
        items_.swap(new_items);
        capacity_ = new_capacity;
    }

//     void Reserve(size_t new_capacity) {
//         if (new_capacity > capacity_) {
//             auto new_items = ReallocateCopy(new_capacity);  // может бросить исключение

//             items_.swap(new_items);
//             capacity_ = new_capacity;
//         }
//     }



// private:
//     // Выделяет копию текущего массива с заданной вместимостью
//     ItemsPtr ReallocateCopy(size_t new_capacity) const {
//         ItemsPtr new_items(new_capacity);  // может бросить исключение
//         size_t copy_size = std::min(new_capacity, size_);
//         std::copy(items_.Get(), items_.Get() + copy_size, new_items.Get());  // может бросить исключение
//         return ItemsPtr(new_items.Release());
//     }

public:
    //---next ----------------------------------------------
    SimpleVector(const SimpleVector& other)
        : items_(other.size_),
        size_(other.size_),
        capacity_(other.size_)
    {

        std::copy(other.begin(), other.end(), items_.Get());

    }

    //операция присваивания
    SimpleVector& operator=(const SimpleVector& rhs) {
        if (this != &rhs) {  // Сравниваем адреса напрямую
            SimpleVector rhs_copy(rhs);
            swap(rhs_copy);
        }
        return *this;
    }

    // Добавляет элемент в конец вектора
    // При нехватке места увеличивает вдвое вместимость вектора
    void PushBack(const Type& item) {

        if (size_ == capacity_){

            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;

            ArrayPtr<Type> item_copy(new_capacity);

            //copy and swap
            std::copy (items_.Get(), items_.Get() + size_, item_copy.Get() );
            items_.swap(item_copy);
            capacity_ = new_capacity;
        }

        items_[size_] =  item;
        size_++;
    }

    // Вставляет значение value в позицию pos.
    // Возвращает итератор на вставленное значение
    // Если перед вставкой значения вектор был заполнен полностью,
    // вместимость вектора должна увеличиться вдвое, а для вектора вместимостью 0 стать равной 1
    // Iterator Insert(ConstIterator pos, const Type& value) {

        //     if (size_ == capacity_){

    //         size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;

    //         ArrayPtr<Type> item_copy(new_capacity);

    //         //copy and swap
    //         std::copy (items_.Get(), items_.Get() + size_, item_copy.Get() );
    //         items_.swap(item_copy);
    //         capacity_ = new_capacity;
    //     }
    //     // Находим позицию для вставки относительно начала массива
    //     size_t pos_offset = pos - cbegin();

    //     // Сдвигаем элементы вправо, чтобы освободить место для вставки
    //     std::copy_backward(items_.Get() + pos_offset, items_.Get() + size_, items_.Get() + size_ + 1);

    //     // Вставляем значение в нужную позицию
    //     items_[pos_offset] = value;

    //     // Увеличиваем размер вектора
    //     ++size_;

    //     return begin() + pos_offset;
    // }

    Iterator Insert(ConstIterator pos, const Type& value) {
        // Проверка валидности позиции
        if (pos < begin() || pos > end()) {
            throw std::out_of_range("Invalid iterator position");
        }

        const size_t offset = pos - begin();

        if (size_ == capacity_) {
            // Увеличиваем capacity
            const size_t new_capacity = std::max(capacity_ * 2, static_cast<size_t>(1));
            ArrayPtr<Type> new_items(new_capacity);

            // Копируем элементы до позиции вставки (используем const_cast)
            std::copy(begin(), const_cast<Iterator>(pos), new_items.Get());

            // Вставляем новый элемент
            new_items[offset] = value;

            // Копируем оставшиеся элементы (используем const_cast)
            std::copy(const_cast<Iterator>(pos), end(), new_items.Get() + offset + 1);

            // Обмениваем буферы
            items_.swap(new_items);
            capacity_ = new_capacity;
        } else {
            // Сдвигаем элементы вправо
            std::copy_backward(begin() + offset, end(), end() + 1);

            // Вставляем элемент
            items_[offset] = value;
        }

        ++size_;
        return begin() + offset;
    }


    // "Удаляет" последний элемент вектора. Вектор не должен быть пустым
    void PopBack() noexcept {
        if (size_ > 0) {
            --size_;
        }
    }

    // Удаляет элемент вектора в указанной позиции
    Iterator Erase(ConstIterator pos) {
        // Проверяем, что позиция находится в допустимых пределах
        assert(pos >= begin() && pos < end());

        // Вычисляем смещение удаляемого элемента
        const size_t offset = pos - begin();

        // Сдвигаем все элементы после pos влево
        std::move(begin() + offset + 1, end(), begin() + offset);

        // Уменьшаем размер вектора
        --size_;

        // Возвращаем итератор на элемент, следующий за удаленным
        return begin() + offset;
    }

    // Обменивает значение с другим вектором
    void swap(SimpleVector& other) noexcept {
        items_.swap(other.items_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    //------------------------------------------------------

    // Возвращает количество элементов в массиве
    size_t GetSize() const noexcept {
        // Напишите тело самостоятельно
        return size_;
    }

    // Возвращает вместимость массива
    size_t GetCapacity() const noexcept {
        // Напишите тело самостоятельно
        return capacity_;
    }

    // Сообщает, пустой ли массив
    bool IsEmpty() const noexcept {
        return size_ == 0;
    }

    // Возвращает ссылку на элемент с индексом index
    Type& operator[](size_t index) noexcept {
        return items_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    const Type& operator[](size_t index) const noexcept {

        return items_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    Type& At(size_t index) {
        // Напишите тело самостоятельно
        if (index >= size_)
            throw std::out_of_range("Index out of range");

        return items_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    const Type& At(size_t index) const {
        // Напишите тело самостоятельно
        if (index >= size_)
            throw std::out_of_range("Index out of range");

        return items_[index];
    }

    // Обнуляет размер массива, не изменяя его вместимость
    void Clear() noexcept {
        size_ = 0;
    }

    // Изменяет размер массива.
    // При увеличении размера новые элементы получают значение по умолчанию для типа Type
    void Resize(size_t new_size) {
        if (new_size > capacity_) {

            const size_t new_capacity = std::max(capacity_ * 2, new_size);

            ArrayPtr<Type> new_items(new_capacity);

            std::move(items_.Get(), items_.Get() + size_, new_items.Get());
            std::fill(new_items.Get() + size_, new_items.Get() + new_size, Type{});
            items_.swap(new_items);
            capacity_ = new_capacity;

        } else if (new_size > size_) {
            std::fill(items_.Get() + size_, items_.Get() + new_size, Type{});
        }
        size_ = new_size;
    }

    // Возвращает итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator begin() noexcept {
        return items_.Get();
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator end() noexcept {
        return items_.Get()+ size_;
    }

    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator begin() const noexcept {
        return items_.Get();
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator end() const noexcept {
        return items_.Get()+ size_;
    }

    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cbegin() const noexcept {
        return items_.Get();
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cend() const noexcept {
        return items_.Get()+ size_;
    }

private:
    ArrayPtr<Type> items_; // Использование ArrayPtr для хранения массива элементов
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template <typename Type>
inline bool operator==(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    // Сначала проверяем размеры
    if (lhs.GetSize() != rhs.GetSize()) {
        return false;
    }
    // Затем сравниваем элементы
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
inline bool operator!=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs == rhs);  // Используем уже реализованный operator==
}

template <typename Type>
inline bool operator<(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return std::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end()
        );
}

template <typename Type>
inline bool operator<=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(rhs < lhs);  // Выражаем через operator<
}

template <typename Type>
inline bool operator>(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return rhs < lhs;  // Выражаем через operator<
}

template <typename Type>
inline bool operator>=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs < rhs);  // Выражаем через operator<
}
