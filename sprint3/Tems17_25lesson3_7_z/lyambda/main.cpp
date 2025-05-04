#include <iostream>
#include <string>

void PrintStrStatistics(const std::string& str) {

    auto num_count = [&](char sp){
        int num_synb = 0;
        for (char ch : str){
            if (ch == sp)
                num_synb++;
        }
        return num_synb;
    };

    int num_space = num_count (' ');
    int num_dot  = num_count ('.');
    int num_comma = num_count (',');

    std::cout << "Пробелов: " << num_space
              << ", точек: " << num_dot
              << ", запятых: " << num_comma << std::endl;
}

int main() {
    std::string str;
    std::getline(std::cin, str);
    PrintStrStatistics(str);
}



