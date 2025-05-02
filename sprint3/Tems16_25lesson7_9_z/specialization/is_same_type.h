#pragma once

// Напишите здесь реализацию структур.
template <typename T, typename U>
struct IsSameType {
    static constexpr bool value = false;
};

template <typename T>
struct IsSameType<T,T> {
    static constexpr bool value = true;
};


// Шаблонная переменная позволяет использовать
// IsSameTypeV<int, int> вместо IsSameType<int, int>::value.
template<class T, class U>
inline constexpr bool IsSameTypeV = IsSameType<T, U>::value;
