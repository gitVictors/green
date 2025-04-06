#include <iostream>
#include <vector>
#include <sstream>




class WarehouseStorage {
public:
    WarehouseStorage(const std::vector<int>& items)
        : items_{items} {}

    // Реализуйте здесь операции сложения и вычитания
    // этого класса и vector<int>.

    WarehouseStorage operator+(const std::vector<int>& vec)const
    {
        std::vector tmp{items_};
        tmp.insert(tmp.end(), vec.begin(), vec.end() );
        return WarehouseStorage{tmp};
    }


    WarehouseStorage operator-(const std::vector<int>& vec) const
    {
        std::vector tmp{items_};
        for (int x : vec){
            for (auto it = tmp.begin(); it != tmp.end();){
                if(*it == x )
                {
                    it = tmp.erase(it);
                }else
                {
                    ++it;
                }
            }
        }

        return WarehouseStorage {tmp};
    }

    void Print(std::ostream &stream, const std::string& name) const {
        stream << name << ": ";
        int i{};
        for (auto &item : items_) {
            if (i++) {
                stream << " ";
            }
            stream << item;
        }
        stream << std::endl;
    }


private:
    std::vector<int> items_;
};





std::vector<int> Read(std::istream &stream) {
    std::string line;
    std::getline(stream, line);
    std::istringstream line_stream(line);

    std::vector<int> ret;
    int val;
    while(line_stream >> val) {
        ret.push_back(val);
    }

    return ret;
}

int main() {
    auto origin = Read(std::cin);
    auto items = Read(std::cin);

    const WarehouseStorage storage{origin};
    storage.Print(std::cout, "Origin");
    (storage + items).Print(std::cout, "Supply");
    (storage - items).Print(std::cout, "Disposal");
}




