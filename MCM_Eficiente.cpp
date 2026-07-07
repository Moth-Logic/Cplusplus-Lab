#include <iostream>
using namespace std;

long long mcd(long long A, long long B) {
    while (B != 0) {
        long long t = B;
        B = A % B;
        A = t;
    }
    return A;
}

long long mcm(long long A, long long B) {
    long long D = mcd(A, B);
    return (A * B) / D;
}

int main() {
    long long A, B;
    cout << "Ingrese el primer numero: ";
    cin >> A;
    cout << "Ingrese el segundo numero: ";
    cin >> B;

    cout << "El MCM es: " << mcm(A, B) << endl;
    return 0;
}
