#include "RadixSort.h"
#include "DLinkedList.h"

#include <algorithm>
#include <vector>

// Radix Sort auxiliar para valores NO negativos (usa long long para
// evitar overflow al tomar valor absoluto de INT_MIN).
static void radixSortNonNeg(std::vector<long long>& arr, int base) {
    if (arr.size() < 2) return;

    long long maxVal = *std::max_element(arr.begin(), arr.end());
    if (maxVal == 0) return;

    std::vector<DLinkedList<long long>> buckets(base);

    long long exp = 1;
    while (maxVal / exp > 0) {
        // Vaciar baldes
        for (auto& b : buckets) b.clear();

        // Distribuir por digito en posicion 'exp'
        for (long long v : arr) {
            int digit = static_cast<int>((v / exp) % base);
            buckets[digit].addLast(v);
        }

        // Recolectar
        arr.clear();
        for (auto& b : buckets) {
            while (!b.isEmpty())
                arr.push_back(b.removeFirst());
        }

        // Evitar overflow de exp*base
        if (exp > maxVal / base) break;
        exp *= base;
    }
}

void radixSort(std::vector<int>& arr, int base) {
    if (base < 2 || arr.size() < 2) return;

    std::vector<long long> negativos;
    std::vector<long long> noNegativos;
    negativos.reserve(arr.size());
    noNegativos.reserve(arr.size());

    for (int v : arr) {
        if (v < 0) negativos.push_back(-static_cast<long long>(v));
        else       noNegativos.push_back(static_cast<long long>(v));
    }

    radixSortNonNeg(noNegativos, base);
    radixSortNonNeg(negativos, base);

    arr.clear();
    arr.reserve(negativos.size() + noNegativos.size());

    // Negativos: mayor valor absoluto primero => mas negativo primero
    for (auto it = negativos.rbegin(); it != negativos.rend(); ++it)
        arr.push_back(static_cast<int>(-(*it)));

    for (long long v : noNegativos)
        arr.push_back(static_cast<int>(v));
}