#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ofstream archivo1("datos.txt", ios::app);
    archivo1 << "Holas\n";
    archivo1.close();

    ofstream archivo2("datos.txt", ios::trunc);
    archivo2 << "idk";
    archivo2.close();

    ifstream archivo3("datos.txt");
    string contenido((istreambuf_iterator<char>(archivo3)), istreambuf_iterator<char>());
    archivo3.close();

    cout << contenido << endl;
    return 0;
}
