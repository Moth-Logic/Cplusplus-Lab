#include <iostream>
using namespace std;

int main() {
    int a;
    cout << "Numero entero mayor que 0: ";
    cin >> a;

    if (a > 0) {
        if (a == 1) {
            cout << 1 << endl;
        } else {
            while (a != 1) {
                if (a % 2 == 0)
                    a = a / 2;
                else
                    a = 3 * a + 1;
                cout << a << endl;
            }
        }
    } else {
        cout << "ERROR: Numero debe ser mayor que 0" << endl;
    }
    return 0;
}
