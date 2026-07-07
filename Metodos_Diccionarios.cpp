#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, string> persona = {
        {"nombre", "Lorenzo"},
        {"edad", "30"},
        {"profesion", "psicologo"}
    };

    cout << "{nombre: " << persona["nombre"] << ", edad: " << persona["edad"] << ", profesion: " << persona["profesion"] << "}" << endl;
    cout << persona["nombre"] << endl;
    cout << persona["edad"] << endl;
    cout << persona["profesion"] << endl;

    for (auto& elemento : persona)
        cout << elemento.first << endl;

    for (auto& kv : persona)
        cout << "clave: " << kv.first << " valor: " << kv.second << endl;

    cout << persona["edad"] << endl;

    persona["altura"] = "1.65";
    for (auto& kv : persona)
        cout << kv.first << ": " << kv.second << " ";
    cout << endl;

    persona.erase("profesion");
    for (auto& kv : persona)
        cout << kv.first << ": " << kv.second << " ";
    cout << endl;

    cout << (persona.count("nombre") > 0 ? "true" : "false") << endl;
    cout << (persona.count("profesion") > 0 ? "true" : "false") << endl;

    return 0;
}
