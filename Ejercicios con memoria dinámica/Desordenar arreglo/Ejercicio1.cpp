// Dynamic Memory Exercise 1: Shuffle an array using random swaps.
// We create an array [1, 2, ..., N], then perform N/2 random swaps
// to randomize the order. This demonstrates dynamic memory allocation
// with new/delete and basic array manipulation.

#include <iostream>
#include <cstdlib>   // For srand(), rand()
#include <ctime>     // For time() — used to seed the random number generator
#include <limits>    // For numeric_limits — used to clear bad input from cin

using namespace std;

// Print the array in a nice format: [ 1, 2, 3, ... ]
// The 'const' means we promise not to modify the array (read-only).
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

// Keep asking the user for a number until they enter a valid integer > 2.
// If they type letters or a small number, we reject and ask again.
int leerN() {
    int n;
    while (true) {
        cout << "Indique la cantidad de numeros a generar: ";
        cin >> n;

        if (cin.fail()) {
            // The user typed something that isn't a number (e.g., "hello")
            cout << "Entero no valido." << endl;
            cin.clear();  // Reset the error flag on cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard the bad input
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Consume the leftover newline

        if (n <= 2) {
            cout << "Debe ser mas de un numero." << endl;
            continue;
        }

        return n;
    }
}

int main() {
    // Seed the random number generator with the current time.
    // Without this, rand() produces the same sequence every run (boring!).
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Programa para desordenar un arreglo." << endl;

    int n = leerN();

    // Allocate an array of n integers on the heap using 'new'.
    // This is dynamic memory — the size is determined at runtime.
    int* arreglo = new int[n];

    // Fill the array with [1, 2, 3, ..., n] — nice and ordered.
    for (int i = 0; i < n; i++) {
        arreglo[i] = i + 1;
    }

    cout << "Arreglo ordenado: ";
    imprimirArreglo(arreglo, n);

    // Perform N/2 random swaps to shuffle the array.
    // Each swap picks two different random positions and exchanges their values.
    int intercambios = n / 2;
    for (int k = 0; k < intercambios; k++) {
        int a = rand() % n;  // Random index from 0 to n-1
        int b;
        do {
            // Keep picking b until it's different from a.
            // Swapping a position with itself does nothing (waste of time).
            b = rand() % n;
        } while (b == a);

        // Classic three-variable swap: temp = a, a = b, b = temp
        int temp = arreglo[a];
        arreglo[a] = arreglo[b];
        arreglo[b] = temp;
    }

    cout << "Arreglo desordenado: ";
    imprimirArreglo(arreglo, n);

    // Free the dynamically allocated memory.
    // Always pair new[] with delete[] and set the pointer to nullptr for safety.
    delete[] arreglo;
    arreglo = nullptr;

    return 0;
}
