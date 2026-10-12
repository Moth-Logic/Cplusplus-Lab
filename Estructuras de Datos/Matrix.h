#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>

// Matriz bidimensional en memoria dinámica.
// Es un template: T es el tipo de los elementos (int, double, etc.).
template <class T>
class Matrix {
private:
    int rows;
    int columns;
    T** matrix;   // puntero a puntero: arreglo de punteros, cada uno apunta a una fila

    // Valida la posición en un solo lugar para no repetir código
    void checkPosition(int row, int column) const {
        if (row < 0 || row >= rows) {
            throw std::runtime_error("Invalid row");
        }
        if (column < 0 || column >= columns) {
            throw std::runtime_error("Invalid column");
        }
    }

public:
    Matrix(int rows, int columns) {
        if (rows <= 0 || columns <= 0) {
            throw std::runtime_error("Rows and columns must be greater than zero");
        }

        this->rows = rows;       // this-> porque el parámetro se llama igual que el atributo
        this->columns = columns;

        // 1) arreglo de punteros (uno por fila)
        matrix = new T * [rows];

        // 2) cada puntero apunta a un arreglo con 'columns' elementos
        for (int i = 0; i < rows; i++) {
            matrix[i] = new T[columns];
        }
    }

    ~Matrix() {
        // Se libera al revés de como se creó: primero las filas...
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        // ...y al final el arreglo de punteros
        delete[] matrix;
    }

    T getValue(int row, int column) const {
        checkPosition(row, column);
        return matrix[row][column];
    }

    void setValue(int row, int column, T value) {
        checkPosition(row, column);
        matrix[row][column] = value;
    }

    int getRows() const {
        return rows;
    }

    int getColumns() const {
        return columns;
    }
};

#endif