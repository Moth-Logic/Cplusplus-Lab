#include <iostream>
#include <cmath>
using namespace std;

bool es_cuadrado_perfecto(long long m) {
    if (m < 0) return false;
    long long raiz = (long long)sqrt((double)m);
    return raiz * raiz == m;
}

int main() {
    long long m;
    cout << "Ingrese un numero entero positivo: ";
    cin >> m;

    if (es_cuadrado_perfecto(m))
        cout << "Si es un cuadrado perfecto" << endl;
    else
        cout << "No es un cuadrado perfecto" << endl;

    return 0;
}
