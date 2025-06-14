#include <iostream>
#include <string>

using namespace std;

template <typename F>
string BruteForceInternal(F check, const string& begin, int n) {
    if (n == 5) {
        return check(begin) ? begin : "";
    }

    for (char c = 'A'; c <= 'Z'; ++c) {
        string result = BruteForceInternal(check, begin + c, n + 1);
        if (!result.empty()) {
            return result;
        }
    }

    return "";
}

template <typename F>
string BruteForce(F check) {
    return BruteForceInternal(check, "", 0);
}

int main() {
    string pass = "ARTUR"s;
    auto check = [pass](const string& s) {
        return s == pass;
    };
    cout << BruteForce(check) << endl;
}


// template <typename F>
// string BruteForce(F check) {
//     for (char a = 'A'; a <= 'Z'; ++a)
//         for (char b = 'A'; b <= 'Z'; ++b)
//             for (char c = 'A'; c <= 'Z'; ++c)
//                 for (char d = 'A'; d <= 'Z'; ++d)
//                     for (char e = 'A'; e <= 'Z'; ++e) {
//                         string s = {a, b, c, d, e};
//                         if (check(s)) return s;
//                     }
//     return "";
// }
