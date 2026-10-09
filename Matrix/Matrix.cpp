#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"

using std::cout;
using std::endl;

// Llena la matriz con valores aleatorios entre 0 y 99
template <class T>
void llenarAleatorio(Matrix<T>& matriz) {
    for (int f = 0; f < matriz.getRows(); f++) {
        for (int c = 0; c < matriz.getColumns(); c++) {
            matriz.setValue(f, c, static_cast<T>(rand() % 100));
        }
    }
}

// Calcula la suma de dos matrices del mismo tamano y la guarda en 'resultado'
template <class T>
void sumar(const Matrix<T>& a, const Matrix<T>& b, Matrix<T>& resultado) {
    if (a.getRows() != b.getRows() || a.getColumns() != b.getColumns()) {
        throw std::runtime_error("Las matrices deben tener las mismas dimensiones");
    }
    if (resultado.getRows() != a.getRows() || resultado.getColumns() != a.getColumns()) {
        throw std::runtime_error("La matriz resultado debe tener las mismas dimensiones");
    }

    for (int f = 0; f < a.getRows(); f++) {
        for (int c = 0; c < a.getColumns(); c++) {
            resultado.setValue(f, c, a.getValue(f, c) + b.getValue(f, c));
        }
    }
}

// Imprime la matriz con un titulo
template <class T>
void imprimir(const Matrix<T>& matriz, const char* titulo) {
    cout << titulo << endl;
    for (int f = 0; f < matriz.getRows(); f++) {
        for (int c = 0; c < matriz.getColumns(); c++) {
            cout << matriz.getValue(f, c) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    try {
        srand(static_cast<unsigned>(time(0)));

        const int filas = 5;
        const int columnas = 4;

        Matrix<int> a(filas, columnas);
        Matrix<int> b(filas, columnas);
        Matrix<int> c(filas, columnas);

        llenarAleatorio(a);
        llenarAleatorio(b);
        sumar(a, b, c);

        imprimir(a, " Matriz A ");
        imprimir(b, "Matriz B ");
        imprimir(c, "Matriz C (A + B)");
    }
    catch (const std::runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
