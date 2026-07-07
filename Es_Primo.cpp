#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

bool esprimo(long long num) {
    if (num < 0)
        throw invalid_argument("Numero debe ser Integer Positivo");
    if (num == 1)
        return false;

    for (long long m = 2; m <= (long long)sqrt((double)num); m++) {
        if (num % m == 0)
            return false;
    }
    return true;
}

int main() {
    try {
        long long num;
        cout << "Escriba un numero entero positivo: ";
        cin >> num;
        bool result = esprimo(num);
        cout << "Its " << (result ? "true" : "false") << " " << num << " is a prime number" << endl;
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
