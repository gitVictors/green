#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
using namespace filesystem;

int main()
{

    const path dir_path = "./tmp";

    for (const auto& it_entr : directory_iterator(dir_path)){
        if (it_entr.is_directory()){
            cout << "direction: " << it_entr.path() << endl;
        }
        if (it_entr.is_regular_file()) {
            cout << "file name: "<< it_entr.path().filename() <<endl;
        }
    }

    return 0;
}
