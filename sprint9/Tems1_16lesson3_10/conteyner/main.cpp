#include <array>
#include <iomanip>
#include <iostream>
// #include <optional>
#include <sstream>
#include <string>
 #include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class VehiclePlate {
public:
    VehiclePlate(char l0, char l1, int digits, char l2, int region)
        : letters_{l0, l1, l2}
        , digits_(digits)
        , region_(region) {
    }

    string ToString() const {
        ostringstream out;
        out << letters_[0] << letters_[1];
        // чтобы дополнить цифровую часть номера слева нулями
        // до трёх цифр, используем подобные манипуляторы:
        // setfill задаёт символ для заполнения,
        // right задаёт выравнивание по правому краю,
        // setw задаёт минимальное желаемое количество знаков
        out << setfill('0') << right << setw(3) << digits_;
        out << letters_[2] << setw(2) << region_;

        return out.str();
    }

    // int Hash() const {
    //     // Преобразуем массив букв в числовое значение
    //     int letters_hash = 0;
    //     for (char letter : letters_) {
    //         letters_hash = letters_hash * 128 + letter;
    //     }

    //     // Объединяем все значения в одно хеш-значение
    //     return letters_hash ^ digits_ ^ region_;
    // }

    int Hash() const {
        return digits_;
    }

    bool operator==(const VehiclePlate& other) const {
        return letters_ == other.letters_ && digits_ == other.digits_ && region_ == other.region_;
    }


private:
    array<char, 3> letters_;
    int digits_;
    int region_;
};

ostream& operator<<(ostream& out, VehiclePlate plate) {
    out << plate.ToString();
    return out;
}

template <typename T>
class HashableContainer {
public:

    void Insert(T elem) {

        //int index = elem.Hash();
        //int index = abs(elem.Hash());
        // const size_t TABLE_SIZE = 100000;
        size_t index = abs(elem.Hash()); //% TABLE_SIZE;



        // если вектор недостаточно велик для этого индекса,
        // то увеличим его, выделив место с запасом
        if (index >= int(elements_.size())) {
            elements_.resize(index * 2 + 1);
        }


        // for ( const auto& element : elements_[index] ){
        //     if (elem == element)
        //         return;
        // }
        // elements_[index].push_back(elem);

        auto it = find(elements_[index].begin(), elements_[index].end(), elem);
        if (it == elements_[index].end()) elements_[index].push_back(elem);
     }



    void PrintAll(ostream& out) const {
        for (const auto& bag : elements_) {
            for (const auto& e : bag) {
                out << e << endl;
            }
        }
    }


    const auto& GetVector() const {
        return elements_;
    }

private:
    // vector<optional<T>> elements_;
    vector<vector<T>> elements_;
   //  std::vector<std::unordered_set<T>> elements_;
};

int main() {

    HashableContainer<VehiclePlate> plate_base;
    plate_base.Insert({'B','H', 840, 'E', 99});
    plate_base.Insert({'O','K', 942, 'K', 78});
    plate_base.Insert({'O','K', 942, 'K', 78});
    plate_base.Insert({'O','K', 942, 'K', 78});
    plate_base.Insert({'O','K', 942, 'K', 78});
    plate_base.Insert({'H','E', 968, 'C', 79});
    plate_base.Insert({'T','A', 326, 'X', 83});
    plate_base.Insert({'H','H', 831, 'P', 116});
    plate_base.Insert({'A','P', 831, 'Y', 99});
    plate_base.Insert({'P','M', 884, 'K', 23});
    plate_base.Insert({'O','C', 34, 'P', 24});
    plate_base.Insert({'M','Y', 831, 'M', 43});
    plate_base.Insert({'B','P', 831, 'M', 79});
    plate_base.Insert({'K','T', 478, 'P', 49});
    plate_base.Insert({'X','P', 850, 'A', 50});

    plate_base.PrintAll(cout);
}


