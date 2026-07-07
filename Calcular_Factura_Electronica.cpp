#include <iostream>
using namespace std;

double calcular_tarifa(int mensajes, int minutos_plenos, int minutos_reducidos) {
    double tarifa_base = 5000;
    double total = tarifa_base;

    if (mensajes > 100)
        total += (mensajes - 100) * 5;

    if (minutos_plenos > 60)
        total += (minutos_plenos - 60) * 35;

    total += minutos_reducidos * 20;

    double total_con_iva = total * 1.15;
    return total_con_iva;
}

int main() {
    int mensajes, plenos, reducidos;
    cout << "Ingrese cantidad de mensajes: ";
    cin >> mensajes;
    cout << "Ingrese minutos plenos: ";
    cin >> plenos;
    cout << "Ingrese minutos reducidos: ";
    cin >> reducidos;

    double monto = calcular_tarifa(mensajes, plenos, reducidos);
    cout << "Monto a pagar: " << monto << endl;
    return 0;
}
