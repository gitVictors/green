#include <sstream>
#include <vector>
#include <optional>

// Добавьте сюда классы VectorException и Vector.

class VectorException {

public:
    VectorException(const std::string& message): message_ {"Vector error: " + message} {}
    //  VectorException(std::vector<T> items): items_(items) {}


    std::string GetMessage() const {
        return message_;
    }

private:
         // std::vector<T> items_;
    std::string message_;
};




template<typename T>
class Vector {
public:
    Vector(std::vector<T> items): items_(items) {}

    // Добавьте сюда методы.
    T GetItem(int index) {

        if (index < 0 || index >= items_.size()) {
            throw VectorException("Index out of range");
        }

        return items_[index];
    }

    T GetItem(const std::string& index_str){

        int index;
        std::stringstream ss(index_str);

        // Пытаемся перевести в index.
        if (!(ss >> index)) {
            throw VectorException("Invalid index: not a number");
        }

        return GetItem(index);
    }

private:
    std::vector<T> items_;
};




