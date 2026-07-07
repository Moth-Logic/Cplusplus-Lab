#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

bool esprimo(long long num) {
    if (num < 2)
        throw invalid_argument("Numero debe ser Integer Positivo mayor a 2");
    if (num == 2)
        return true;
    if (num % 2 == 0)
        return false;
    for (long long m = 3; m <= (long long)sqrt((double)num); m += 2) {
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
        if (num < 2)
            throw invalid_argument("Numero debe ser mayor a 2");
        cout << "Numeros primos desde 2 hasta " << num << ":" << endl;
        for (long long i = 2; i <= num; i++) {
            if (esprimo(i))
                cout << i << endl;
        }
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
