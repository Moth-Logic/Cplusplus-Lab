#include <iostream>
using namespace std;

long long mcd_euclides(long long M, long long N) {
    if (M < N) swap(M, N);

    while (N != 0) {
        long long R = M % N;
        M = N;
        N = R;
    }

    return M;
}

int main() {
    long long M, N;
    cout << "Ingrese el primer numero: ";
    cin >> M;
    cout << "Ingrese el segundo numero: ";
    cin >> N;

    cout << "El MCD es: " << mcd_euclides(M, N) << endl;
    return 0;
}
