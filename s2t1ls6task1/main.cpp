#include <iostream>
#include <string>

using namespace std::literals;

class Duck {
public:
    void SetName(const std::string& name) {
        name_ = name;
    }
    void Fly(int distance) {
        // Напишите тело метода самостоятельно.
    }

private:
    std::string name_;
    // Добавьте члены-данные при необходимости.
};

int main() {
    Duck duck1;
    duck1.SetName("Whisper Quack"s);
    Duck duck2;
    duck2.SetName("Fire Wing"s);

    int num_commands = 0;
    std::cin >> num_commands;

    for (int i = 0; i < num_commands; ++i) {
        int duck_number, distance;
        std::cin >> duck_number >> distance;
        if (duck_number == 1) {
            duck1.Fly(distance);
        } else if (duck_number == 2) {
            duck2.Fly(distance);
        }
    }
}