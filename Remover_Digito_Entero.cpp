#include <iostream>
using namespace std;

long long elimina(long long n, int d) {
    long long res = 0, fac = 1;

    while (n > 0) {
        int dig = n % 10;
        n = n / 10;

        if (dig != d) {
            res = res + dig * fac;
            fac = fac * 10;
        }
    }

    return res;
}

int main() {
    long long n;
    int d;
    cout << "Ingrese el numero: ";
    cin >> n;
    cout << "Ingrese el digito a eliminar: ";
    cin >> d;

    cout << elimina(n, d) << endl;
    return 0;
}
