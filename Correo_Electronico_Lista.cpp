#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void imprimir(const vector<string>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << "'" << v[i] << "'";
        if (i != v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    vector<string> correos = {"outlook", "hotmail", "gmail"};
    for (auto& c : correos) cout << c << " ";
    cout << endl;

    correos.push_back("yahoo");
    imprimir(correos);

    string eliminado = correos[2];
    correos.erase(correos.begin() + 2);
    cout << eliminado << endl;
    imprimir(correos);

    correos.erase(correos.begin() + 1);
    imprimir(correos);

    int cantidad = correos.size();
    cout << cantidad << endl;

    vector<string> correo2 = {"yahoo", "hotmail", "gmail"};
    correos.insert(correos.end(), correo2.begin(), correo2.end());
    imprimir(correos);

    correos.erase(find(correos.begin(), correos.end(), "yahoo"));
    imprimir(correos);

    correos.insert(correos.begin() + 1, "CTPP");
    imprimir(correos);

    int posicion = find(correos.begin(), correos.end(), "yahoo") - correos.begin();
    cout << "El indice de elementos del operador de la lista es de: " << posicion << endl;

    vector<int> numeros = {3, 2, 1};
    for (int n : numeros) cout << n << " ";
    cout << endl;

    sort(numeros.begin(), numeros.end());
    for (int n : numeros) cout << n << " ";
    cout << endl;

    vector<int> lista = {1, 2, 3};
    for (int n : lista) cout << n << " ";
    cout << endl;
    reverse(lista.begin(), lista.end());
    for (int n : lista) cout << n << " ";
    cout << endl;

    vector<int> otralista = {2, 5, 4, 6, 5, 7, 8, 1};
    int rep = count(otralista.begin(), otralista.end(), 5);
    cout << rep << endl;

    vector<int> listax1 = {1, 2, 3};
    vector<int> listax2 = {4, 5, 6};
    vector<int> listax3 = listax1;
    listax3.insert(listax3.end(), listax2.begin(), listax2.end());

    listax3.clear();
    cout << "[]" << endl;

    listax3 = listax1;
    listax3.insert(listax3.end(), listax2.begin(), listax2.end());
    for (int n : listax3) cout << n << " ";
    cout << endl;

    for (size_t i = 1; i < min((size_t)5, listax3.size()); i++) cout << listax3[i] << " ";
    cout << endl;

    vector<int> copia = listax1;
    for (int n : copia) cout << n << " ";
    cout << endl;

    // Nota: en Python, "copia2 = listax1" crea una referencia al mismo objeto.
    // En C++ usamos una referencia explícita para replicar ese comportamiento.
    vector<int>& copia2 = listax1;
    copia2.push_back(4);
    cout << "Esto es una copia dos ";
    for (int n : copia2) cout << n << " ";
    cout << endl;
    cout << "Esta es una copia de lista1 ";
    for (int n : listax1) cout << n << " ";
    cout << endl;

    return 0;
}
