#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <limits>
#include <algorithm>
#include <random>

#include "RadixSort.h"

static void printList(const std::vector<int>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << arr[i];
    }
    std::cout << "]\n";
}

static bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i - 1] > arr[i]) return false;
    return true;
}

int main() {
    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    // Rango de valores aleatorios (ajustable)
    std::uniform_int_distribution<int> dist(-1'000'000, 1'000'000);

    char repetir;
    do {
        int n;
        std::cout << "Tamano de la lista a ordenar: ";
        while (!(std::cin >> n) || n < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ingrese un entero no negativo: ";
        }

        int base;
        std::cout << "Base numerica a utilizar (>= 2): ";
        while (!(std::cin >> base) || base < 2) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ingrese una base >= 2: ";
        }

        // Crear y llenar lista
        std::vector<int> list(n);
        for (int i = 0; i < n; ++i)
            list[i] = dist(rng);

        std::cout << "\nLista original:\n";
        if (n <= 50) printList(list);
        else         std::cout << "(omitida, n = " << n << ")\n";

        // Medir tiempo
        auto t0 = std::chrono::high_resolution_clock::now();
        radixSort(list, base);
        auto t1 = std::chrono::high_resolution_clock::now();

        double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

        std::cout << "\nLista ordenada:\n";
        if (n <= 50) printList(list);
        else std::cout << (isSorted(list) ? "Ordenada correctamente."
                                          : "ERROR: la lista NO quedo ordenada.")
                       << "\n";

        if (n > 50) {
            std::cout << "Verificacion: " << (isSorted(list) ? "OK" : "FALLO") << "\n";
        }

        std::cout << "\nTiempo de ejecucion: " << ms << " ms\n";

        std::cout << "\nDesea repetir? (s/n): ";
        std::cin >> repetir;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n";

    } while (repetir == 's' || repetir == 'S');

    return 0;
}