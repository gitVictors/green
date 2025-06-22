#include <map>
#include <string>
#include <string_view>
#include <assert.h>

using namespace  std;

class Translator {
public:
    Translator() = default;

    void Add(string_view source, string_view target){
        string source_cp ( source );
        string target_cp  (target);

        forward_dict_[source_cp] = target_cp;
        backward_dict_[target_cp] = source;
    }

    string_view TranslateForward(string_view source) const{

        auto it = forward_dict_.find(string(source));
        if (it != forward_dict_.end() ){
            return it->second;
        }
        return "";
    }

    string_view TranslateBackward(string_view target) const{
        auto it = backward_dict_.find(string(target));
        if (it != backward_dict_.end()){
            return it->second;
        }

        return "";
    }

private:
    map<string, string> forward_dict_;
    map<string, string> backward_dict_;

};


void TestSimple() {
    Translator translator;
    translator.Add(string("okno"s), string("window"s));
    translator.Add(string("stol"s), string("table"s));

    assert(translator.TranslateForward("okno"s) == "window"s);
    assert(translator.TranslateBackward("table"s) == "stol"s);
    assert(translator.TranslateForward("table"s) == ""s);
}

int main() {
    TestSimple();
}
