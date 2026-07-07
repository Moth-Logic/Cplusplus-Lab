#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    map<string, double> conversiones = {
        {"in", 2.54}, {"ft", 30.48}, {"yd", 91.44}, {"mi", 160934}, {"nm", 185200}
    };

    string unidad;
    double valor;
    cout << "Ingrese la unidad (in, ft, yd, mi, nm): ";
    cin >> unidad;
    transform(unidad.begin(), unidad.end(), unidad.begin(), ::tolower);
    cout << "Ingrese el valor a convertir: ";
    cin >> valor;

    if (conversiones.find(unidad) == conversiones.end()) {
        cout << "Error: unidad no valida" << endl;
        return 0;
    }

    double cm = valor * conversiones[unidad];
    double m = cm / 100;
    double km = cm / 100000;

    cout << "Centimetros: " << cm << endl;
    cout << "Metros: " << m << endl;
    cout << "Kilometros: " << km << endl;
    return 0;
}
