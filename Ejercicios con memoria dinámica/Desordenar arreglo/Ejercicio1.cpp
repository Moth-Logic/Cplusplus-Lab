// La mision: armar un arreglo del 1 al N bien ordenadito y despues
// tirarlo al caos total con puros swaps random. 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Imprime el arreglo bonito, formato [ a, b, c, ...] pq al profe le gusta asi
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

// Le insiste al usuario hasta que escriba un numero decente (>2).
// Si mete letras o un numero chiquito, lo regresamos
int leerN() {
    int n;
    while (true) {
        cout << "Indique la cantidad de numeros a generar: ";
        cin >> n;

        if (cin.fail()) {
            // el usuario escribio "hola" o algo random
            cout << "Entero no valido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (n <= 2) {
            cout << "Debe ser mas de un numero." << endl;
            continue;
        }

        return n;
    }
}

int main() {
    // sembramos la semilla del random con el reloj pq si no, siempre desordena exactamente igual (aburrido)
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Programa para desordenar un arreglo." << endl;

    int n = leerN();

    // aqui nace el arreglo, directo del heap, hot and ready como little ceasars
    int* arreglo = new int[n];

    for (int i = 0; i < n; i++) {
        arreglo[i] = i + 1;
    }

    cout << "Arreglo ordenado: ";
    imprimirArreglo(arreglo, n);

    // hora del desmadre: N/2 swaps entre posiciones random y distintas
    int intercambios = n / 2;
    for (int k = 0; k < intercambios; k++) {
        int a = rand() % n;
        int b;
        do {
            // insistimos hasta que b sea distinto de a, pq intercambiar una posicion consigo misma no desordena nada (flojera inutil)
            b = rand() % n;
        } while (b == a);

        int temp = arreglo[a];
        arreglo[a] = arreglo[b];
        arreglo[b] = temp;
    }

    cout << "Arreglo desordenado: ";
    imprimirArreglo(arreglo, n);

    // liberamos la memoria
    delete[] arreglo;
    arreglo = nullptr;

    return 0;
}
