// Le pedimos al usuario una fila de numeros positivos que no bajen nunca (no decreciente), le dibujamos su histograma de asteriscos, y despues lo giramos 90 grados pq si, eso es "transponer".

#include <iostream>
#include <limits>

using namespace std;

// Imprime el arreglo con formato [ a, b, c, ...], el clasico de la casa
void imprimirArreglo(const int arreglo[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arreglo[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// Dibuja el histograma: cada numero se convierte en su torre de asteriscos, una linea por numero
void imprimirHistograma(const int arreglo[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < arreglo[i]; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

// Deja cin como nuevo despues de que el usuario metio basura, pq si no se queda pegado repitiendo el mismo error para siempre
void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Pregunta cuantos numeros van a venir, y no se rinde hasta que sea un entero positivo de verdad
int leerCantidad() {
    int cantidad;
    while (true) {
        cout << "Indique la cantidad de numeros a leer: ";
        cin >> cantidad;

        if (cin.fail()) {
            cout << "Entero no valido." << endl;
            limpiarEntrada();
            continue;
        }
        limpiarEntrada();

        if (cantidad <= 0) {
            cout << "Debe ser un entero positivo." << endl;
            continue;
        }

        return cantidad;
    }
}

// Recibe la serie completa, uno por uno, checando que cada numero sea positivo Y que no sea menor que el anterior (aqui no se vale bajar)
void leerSerie(int arreglo[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        while (true) {
            cout << "Entero " << (i + 1) << ": ";
            int valor;
            cin >> valor;

            if (cin.fail()) {
                cout << "Entero no valido." << endl;
                limpiarEntrada();
                continue;
            }
            limpiarEntrada();

            if (valor <= 0) {
                cout << "Debe ser entero positivo." << endl;
                continue;
            }

            if (i > 0 && valor < arreglo[i - 1]) {
                cout << "El siguiente entero no puede ser menor que el anterior." << endl;
                continue;
            }

            arreglo[i] = valor;
            break;
        }
    }
}

int main() {
    cout << "Programa para transponer un histograma no decreciente." << endl;

    int cantidad = leerCantidad();

    int* arreglo = new int[cantidad];

    cout << "Ingrese los enteros, deben estar en orden no decreciente." << endl;
    leerSerie(arreglo, cantidad);

    imprimirArreglo(arreglo, cantidad);
    imprimirHistograma(arreglo, cantidad);

    // el numero mas grande siempre esta al final, pq la serie nunca baja
    int maximo = arreglo[cantidad - 1];

    // Heres where the magic happens pq para cada nivel L (de 1 hasta el maximo),
    // contamos cuantos elementos del arreglo son >= L. Esa cuenta sale
    // no creciente (obvio, entre mas alto el nivel, menos numeros llegan),
    // asi que la guardamos al reves pa que quede no decreciente, tal
    // como la pide el enunciado
    int* transpuesto = new int[maximo];
    for (int nivel = 1; nivel <= maximo; nivel++) {
        int conteo = 0;
        for (int i = 0; i < cantidad; i++) {
            if (arreglo[i] >= nivel) {
                conteo++;
            }
        }
        transpuesto[maximo - nivel] = conteo;
    }

    imprimirArreglo(transpuesto, maximo);
    imprimirHistograma(transpuesto, maximo);

    // adios memoria, gracias por tu servicio
    delete[] arreglo;
    delete[] transpuesto;
    arreglo = nullptr;
    transpuesto = nullptr;

    return 0;
}
