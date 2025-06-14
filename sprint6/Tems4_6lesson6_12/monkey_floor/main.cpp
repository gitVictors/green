#include <iostream>

using namespace std;

template <typename F>
int FindFloor(int n, F drop) {

    int left = 1;
    int right = n;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (drop(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    int n,t;
    cout << "Enter n and target floor number: "s << endl;
    cin >> n >> t;

    int count = 0;
    int found = FindFloor(n, [t, &count](int f) {
        ++count;
        return f >= t;
    });

    cout << "Found floor "s << found << " after "s << count << " drops"s;

    return 0;
}
