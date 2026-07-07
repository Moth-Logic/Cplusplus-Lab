#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

void Histograma(long long num) {
    if (num < 0)
        throw invalid_argument("Numero debe ser entero positivo.");
    cout << num << endl;
    while (num > 0) {
        int numpri = num % 10;
        int numsec = numpri;
        num /= 10;
        cout << numpri << ":" << string(numsec, '*') << endl;
    }
}

int main() {
    Histograma(123456789);
    return 0;
}
