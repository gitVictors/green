#include "ini.h"

using namespace std;



// место для реализаций методов и функций библиотеки ini
// не забудьте, что они должны быть помещены в namespace ini

namespace ini{

Section& Document::AddSection(std::string name){
    return sections_[std::move(name)];
}

const Section& Document::GetSection(const std::string& name) const{
    static const  Section empty_section;

    auto it = sections_.find (name);
    if (it != sections_.end()){
        return it->second;
    }

    return empty_section;
}

std::size_t Document::GetSectionCount() const{
    return sections_.size();
}

void ClearString(string& str) {
    if (!str.empty()) str = str.substr(str.find_first_not_of(' '), str.find_last_not_of(' ') - str.find_first_not_of(' ') + 1);
}

Document Load(istream& input) {
    Document result;
    string line;
    Section* section = nullptr;

    while (getline(input, line)) {
        ClearString(line);

        if (line[0] == '[') {
            string section_name = line.substr(1, line.find(']') - 1);
            section = &result.AddSection(section_name);
        }
        else if (line.find('=') && !line.empty()) {
            string section_key = line.substr(0, line.find_first_of('='));
            string section_value = line.substr(line.find_first_of('=') + 1, line.size() - line.find_first_of('='));
            ClearString(section_key);
            ClearString(section_value);
            section->insert({ section_key, section_value });
        }
        else {
            continue;
        }
    }

    return result;
}


}
