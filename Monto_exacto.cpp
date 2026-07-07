#include <iostream>
#include <vector>
using namespace std;

pair<vector<pair<int,int>>, int> monto_exacto(int monto) {
    vector<int> denominaciones = {50000, 20000, 10000, 5000, 2000, 1000, 500, 100, 50, 25, 10, 5};

    vector<pair<int,int>> resultado;

    for (int d : denominaciones) {
        int cantidad = monto / d;
        monto = monto % d;
        resultado.push_back({d, cantidad});
    }

    return {resultado, monto};
}

int main() {
    int monto;
    cout << "Ingrese el monto: ";
    cin >> monto;

    auto par = monto_exacto(monto);
    auto resultado = par.first;
    int sobrante = par.second;

    for (auto& dc : resultado)
        cout << dc.second << " x " << dc.first << endl;

    cout << "Sobran " << sobrante << " colones" << endl;
    return 0;
}
