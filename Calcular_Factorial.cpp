#include <iostream>
#include <stdexcept>
using namespace std;

long long factorial(long long num) {
    if (num < 0)
        throw invalid_argument("numero debe ser int positivo.");
    long long fact = 1;
    while (num > 1) {
        fact *= num;
        num -= 1;
    }
    return fact;
}

int main() {
    try {
        long long num;
        cout << "Escriba un numero entero positivo: ";
        cin >> num;
        long long result = factorial(num);
        cout << num << "! = " << result << endl;
    } catch (exception& e) {
        cout << "ERROR: " << e.what() << endl;
    }
    return 0;
}
