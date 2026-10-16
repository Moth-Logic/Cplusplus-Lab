// DictionaryPictionary.cpp : Tester for the Dictionary ADT.
// Uses UnsortedListDictionary<string, string> as a small "pictionary" board:
// each KEY is a word and each VALUE is the clue/definition for that word.
// The menu lets you exercise every operation of the abstract Dictionary.

#include <iostream>
#include <string>
#include <cstdlib>

#include "UnsortedListDictionary.h"

using namespace std;

//----------------------------- Input helpers -----------------------------

// Read an int, retrying while the input is not a valid integer.
// Consumes the rest of the line so the next getline() starts clean.
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(10000, '\n');
            return value;
        }
        cout << "  Entrada invalida. Digite un numero entero.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Read a full line of text (words may contain spaces).
string readLine(const string& prompt) {
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

void pauseScreen() {
    cout << "\n  Presione ENTER para continuar...";
    cin.get(); // waits for ENTER (buffer is already clean)
}

void printHeader(const string& title) {
    system("cls");
    cout << "=============================================\n";
    cout << "  " << title << "\n";
    cout << "=============================================\n\n";
}

//----------------------------- Main tester -------------------------------

int main() {
    UnsortedListDictionary<string, string> dict; // word -> clue
    int option = 0;

    do {
        printHeader("DICTIONARY PICTIONARY");
        dict.print(); // show the current pairs
        cout << "  size: " << dict.getSize()
             << " | empty: " << (dict.isEmpty() ? "si" : "no") << "\n\n";
        cout << "  1) insert    (palabra, pista)\n";
        cout << "  2) remove    (palabra)\n";
        cout << "  3) getValue  (pista de una palabra)\n";
        cout << "  4) setValue  (cambiar la pista)\n";
        cout << "  5) contains  (existe la palabra?)\n";
        cout << "  6) getKeys   (todas las palabras)\n";
        cout << "  7) getValues (todas las pistas)\n";
        cout << "  8) clear\n";
        cout << "  0) Salir\n";
        option = readInt("  Opcion: ");

        try {
            switch (option) {
            case 1: {
                string key = readLine("  Palabra: ");
                string value = readLine("  Pista: ");
                dict.insert(key, value);
                cout << "  insert listo.\n";
                break;
            }
            case 2: {
                string key = readLine("  Palabra a eliminar: ");
                cout << "  remove -> " << dict.remove(key) << "\n";
                break;
            }
            case 3: {
                string key = readLine("  Palabra: ");
                cout << "  getValue -> " << dict.getValue(key) << "\n";
                break;
            }
            case 4: {
                string key = readLine("  Palabra: ");
                string value = readLine("  Nueva pista: ");
                dict.setValue(key, value);
                cout << "  setValue listo.\n";
                break;
            }
            case 5: {
                string key = readLine("  Palabra: ");
                cout << "  contains -> " << (dict.contains(key) ? "si" : "no") << "\n";
                break;
            }
            case 6: {
                // getKeys() returns a heap list that WE own, so we delete it.
                List<string>* keys = dict.getKeys();
                cout << "  Keys:   ";
                keys->print();
                delete keys;
                break;
            }
            case 7: {
                List<string>* values = dict.getValues();
                cout << "  Values: ";
                values->print();
                delete values;
                break;
            }
            case 8:
                dict.clear();
                cout << "  Diccionario vaciado.\n";
                break;
            case 0:
                cout << "\nHasta luego!\n";
                break;
            default:
                cout << "  Opcion invalida.\n";
            }
        }
        catch (exception& e) {
            cout << "  ERROR: " << e.what() << "\n";
        }

        if (option != 0)
            pauseScreen();
    } while (option != 0);

    return 0;
}
