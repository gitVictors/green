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
        packages_.reserve(capacity);
        if (packages_.size() > capacity){
            packages_.resize(capacity);
             packages_.shrink_to_fit();
        }
       // packages_.shrink_to_fit(); //максимально уменьшаем вместимостью оптимизируем.
    }

    // Функция добавления посылки.
    // Ничего не делает, если посылка не вписывается в capacity() вектора.
    void AddPackage(const std::string& sender, const std::string& addressee, double weight) {
        if (GetFreePlace()> 0){
            packages_.push_back(Package{sender, addressee, weight});
        }
    }

    // Возвращает свободное место: вместимость минус количество посылок.
    int GetFreePlace() const {
        int emp = packages_.capacity() - packages_.size();
        return emp;
    }

    // Возвращает количество посылок.
    int GetPackagesCount() const {
        return packages_.size();
    }

    // Этот метод будет использоваться в тестах.
    const auto& GetUnderlying() const {
        return packages_;
    }

private:
    std::vector<Package> packages_;
};
