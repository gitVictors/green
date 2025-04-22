#include <iostream>
#include "operations.h"

int main() {
    using namespace std;

    int a, b, c;
    cin >> a >> b >> c;

    cout << DoOperation(a, b, c, OperationType::OP_SUM) << endl;
    cout << DoOperation(a, b, c, OperationType::OP_MAX) << endl;
    cout << DoOperation(a, b, c, OperationType::OP_PROD) << endl;

    cout << DoOperation(a, double(b), double(c), OperationType::OP_SUM) << endl;
    cout << DoOperation(a, double(b), double(c), OperationType::OP_MAX) << endl;
    cout << DoOperation(a, double(b), double(c), OperationType::OP_PROD) << endl;

    cout << DoOperation(to_string(a),
                        to_string(b),
                        to_string(c),
                        OperationType::OP_SUM)
         << endl;
}
