#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : user_page_counts_(MAX_USER_COUNT_ + 1, -1)  // -1 значит, что не случилось ни одного READ
        , page_achieved_by_count_(MAX_PAGE_COUNT_ + 1, 0) {
    }

    void Read(int user_id, int page_count){
        for (int i = user_page_counts_[user_id] + 1; i <= page_count; ++i){
            ++page_achieved_by_count_[i];
        }

        user_page_counts_[user_id] = page_count;

    }


    double Cheer(int user_id) const {
        const int pages_count = user_page_counts_[user_id];
        if (pages_count == -1) {
            return 0;
        }
        const int user_count = page_achieved_by_count_[0];
        if (user_count == 1) {
            return 1;
        }

        return 1.0 - (page_achieved_by_count_[pages_count] - 1.0) / (user_count - 1.0);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1'000;

    std::vector<int> user_page_counts_;
    std::vector<int> page_achieved_by_count_;
};


int main()
{
    ReadingManager readManager;
    int count_cmd = 0;
    cin >> count_cmd;

    for (int i=  0; i < count_cmd; ++i) {
        string cmd;
        int id;

        cin >> cmd >> id;

        if (cmd == "READ"){
            int page_count = 0;
            cin >> page_count;
            readManager.Read(id, page_count);
        }
        else if ( cmd == "CHEER" ){
             cout << setprecision(6) << readManager.Cheer(id) << "\n";
        }
    }

    return 0;
}
