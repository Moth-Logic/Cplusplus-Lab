#include <iostream>
using namespace std;

double calcular_impuesto(double salario) {
    double impuesto = 0;

    if (salario > 1200) {
        impuesto += (salario - 1200) * 0.15;
        salario = 1200;
    }

    if (salario > 800) {
        impuesto += (salario - 800) * 0.10;
        salario = 800;
    }

    return impuesto;
}

int main() {
    double salario;
    cout << "Ingrese el salario: ";
    cin >> salario;

    cout << "Impuesto a pagar: " << calcular_impuesto(salario) << endl;
    return 0;
}
