#pragma once
#include <vector>

// Ordena 'arr' en su lugar usando Radix Sort en la base indicada (base >= 2).
// Admite numeros negativos (se procesan por separado y se invierten al final).
void radixSort(std::vector<int>& arr, int base);