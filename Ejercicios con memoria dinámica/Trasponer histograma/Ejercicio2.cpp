// Dynamic Memory Exercise 2: Transpose a histogram.
// We read a non-decreasing sequence of positive integers, draw its histogram
// (asterisk bars), then "transpose" it by rotating 90 degrees.
// The transpose counts how many values are >= each level, producing a new
// non-decreasing array. This demonstrates dynamic memory and 2D thinking.

#include <iostream>
#include <limits>

using namespace std;

// Print the array in format [ a, b, c, ... ].
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

// Draw the histogram: each number becomes a tower of asterisks.
// Example: [3, 1, 2] draws:
//   ***
//   *
//   **
void imprimirHistograma(const int arreglo[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < arreglo[i]; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

// Reset cin after bad input so it doesn't keep repeating the same error forever.
void limpiarEntrada() {
    cin.clear();  // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard bad input
}

// Ask how many numbers the user will enter. Keep asking until we get a positive integer.
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

// Read the series one by one, checking that each number is positive
// AND not smaller than the previous one (the sequence must be non-decreasing).
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

            // Enforce non-decreasing order: new value must be >= previous value.
            if (i > 0 && valor < arreglo[i - 1]) {
                cout << "El siguiente entero no puede ser menor que el anterior." << endl;
                continue;
            }

            arreglo[i] = valor;
            break;  // Valid input, move to the next position
        }
    }
}

int main() {
    cout << "Programa para transponer un histograma no decreciente." << endl;

    int cantidad = leerCantidad();

    // Allocate the input array on the heap.
    int* arreglo = new int[cantidad];

    cout << "Ingrese los enteros, deben estar en orden no decreciente." << endl;
    leerSerie(arreglo, cantidad);

    // Show the original array and its histogram.
    imprimirArreglo(arreglo, cantidad);
    imprimirHistograma(arreglo, cantidad);

    // The largest value is always at the end (since the series never decreases).
    int maximo = arreglo[cantidad - 1];

    // --- The transpose algorithm ---
    // For each level L (from 1 to maximo), count how many values are >= L.
    // This count naturally decreases as L increases (fewer tall bars).
    // We store it in reverse order so the result is non-decreasing,
    // matching the problem's requirement.
    //
    // Example: [1, 3, 3, 5] → levels 1-5:
    //   Level 1: 4 values >= 1 → 4
    //   Level 2: 3 values >= 2 → 3
    //   Level 3: 3 values >= 3 → 3
    //   Level 4: 1 value >= 4  → 1
    //   Level 5: 1 value >= 5  → 1
    //   Reversed: [1, 1, 3, 3, 4]
    int* transpuesto = new int[maximo];
    for (int nivel = 1; nivel <= maximo; nivel++) {
        int conteo = 0;
        for (int i = 0; i < cantidad; i++) {
            if (arreglo[i] >= nivel) {
                conteo++;
            }
        }
        transpuesto[maximo - nivel] = conteo;  // Store in reverse for non-decreasing order
    }

    // Show the transposed array and its histogram.
    imprimirArreglo(transpuesto, maximo);
    imprimirHistograma(transpuesto, maximo);

    // Free both dynamically allocated arrays.
    delete[] arreglo;
    delete[] transpuesto;
    arreglo = nullptr;
    transpuesto = nullptr;

    return 0;
}
