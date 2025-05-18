#include <iostream>
#include <vector>

class Post {
    struct Package {
        std::string sender{};
        std::string addressee{};
        double weight = 0;
    };

public:
    Post() {
    }

    // Резервирует место под посылки.
    void SetPostCapacity(size_t capacity) {
        // Ваша реализация метода.
    }

    // Функция добавления посылки.
    // Ничего не делает, если посылка не вписывается в capacity() вектора.
    void AddPackage(const std::string& sender, const std::string& addressee, double weight) {
        // Ваша реализация метода.
    }

    // Возвращает свободное место: вместимость минус количество посылок.
    int GetFreePlace() const {
        // Ваша реализация метода.
    }

    // Возвращает количество посылок.
    int GetPackagesCount() const {
        // Ваша реализация метода.
    }

    // Этот метод будет использоваться в тестах.
    const auto& GetUnderlying() const {
        return packages_;
    }

private:
    std::vector<Package> packages_;
};
