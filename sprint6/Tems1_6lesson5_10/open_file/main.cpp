#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

// реализуйте эту функцию:
void CreateFiles(const string& config_file){
    string str;
    ofstream outfile;
    ifstream infile(config_file);
    if (!infile.is_open() ){
        return;
    }

    while (getline (infile, str) ){

        if (str[0] != '>'){
            outfile.close();
            outfile.open(str); //открыли новый файл
            if (!outfile.is_open())
                return;
        } else {
            if (!outfile.is_open())
                return;
            outfile << str.substr(1) <<  endl;
        }

        if (!str.empty()) //очищаем строку
            str.clear();
    }

    infile.close();
    outfile.close();
    return;

}

string GetLine(istream& in) {
    string s;
    getline(in, s);
    return s;
}

int main() {
    ofstream("test_config.txt"s) << "a.txt\n"
                                    ">10\n"
                                    ">abc\n"
                                    "b.txt\n"
                                    ">123"s;

    CreateFiles("test_config.txt"s);
    ifstream in_a("a.txt"s);
    assert(GetLine(in_a) == "10"s && GetLine(in_a) == "abc"s);

    ifstream in_b("b.txt"s);
    assert(GetLine(in_b) == "123"s);
}
