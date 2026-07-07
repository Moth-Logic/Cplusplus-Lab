#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

double convertir(double valor, string origen, string destino) {
    map<string, double> factores = {
        {"B", pow(2,0)}, {"K", pow(2,10)}, {"M", pow(2,20)}, {"G", pow(2,30)},
        {"T", pow(2,40)}, {"P", pow(2,50)}, {"E", pow(2,60)}, {"Z", pow(2,70)}, {"Y", pow(2,80)}
    };
    transform(origen.begin(), origen.end(), origen.begin(), ::toupper);
    transform(destino.begin(), destino.end(), destino.begin(), ::toupper);
    return valor * factores[origen] / factores[destino];
}

int main() {
    double v;
    string o, d;
    cout << "Valor: ";
    cin >> v;
    cout << "Unidad origen (B,K,M,G,T,P,E,Z,Y): ";
    cin >> o;
    cout << "Unidad destino (B,K,M,G,T,P,E,Z,Y): ";
    cin >> d;
    cout << "Resultado: " << convertir(v, o, d) << endl;
    return 0;
}
