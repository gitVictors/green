#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

class Duck {
public:
    void SetName(const std::string& name) {
        name_ = name;
        duck_path_ = 0;
    }
    void Fly(int distance) {
        duck_path_ += distance;
        std::cout << name_ << " flies "s << distance << "km. Total flight distance is "s << duck_path_ << "km."s << std::endl;
    }


private:
    std::string name_;
    int duck_path_ ;
};

int main() {

    std::vector<Duck>duck_mss;
    int num_commands = 0;
    int num_ducks = 0;

    std::cin >> num_ducks >> std::ws; //удаляем пробелы

    //чтение имен
    for (int i = 0; i < num_ducks ; ++i){
        Duck tmp_duck;
        std::string str;
        //std::cin >> str>> std::ws;
        std::getline(std::cin, str);
        tmp_duck.SetName(str) ;
        duck_mss.push_back(tmp_duck);
    }
    


    //количество команд
    std::cin >> num_commands >> std::ws;

    //выполнение
    for (int i = 0; i < num_commands; ++i) {
        int duck_number, distance;
        std::cin >> duck_number >> distance;
        duck_mss[duck_number].Fly (distance);
    }
}

