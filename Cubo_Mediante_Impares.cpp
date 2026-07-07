#include <iostream>
using namespace std;

long long cubo(long long n) {
    long long i = 1, ini = 1, acu = 0;

    while (i <= n - 1) {
        ini = ini + (2 * i);
        i += 1;
    }

    acu = ini;
    i = 0;

    while (i < n - 1) {
        ini = ini + 2;
        acu = acu + ini;
        i += 1;
    }

    return acu;
}

int main() {
    long long n;
    cout << "Indique el numero para elevar al cubo: ";
    cin >> n;

    if (n != 0) {
        if (n != 1) {
            long long res = cubo(n);
            cout << "El cubo de " << n << " es: " << res << endl;
        } else {
            cout << n << endl;
        }
    } else {
        cout << n << endl;
    }
    return 0;
}
