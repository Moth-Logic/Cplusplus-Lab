#include <iostream>
#include <string>
#include "LinkedPriorityQueue.h"
#include "Patient.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::stoi;
using std::exception;

#define NUM_PRIORIDADES 5

void mostrarMenu(LinkedPriorityQueue<Patient>* triage) {
	cout << endl << "TRIAGE - Cola de espera:" << endl;
	triage->print();
	cout << endl;
	cout << "1. Ingresar paciente" << endl;
	cout << "2. Atender paciente" << endl;
	cout << "3. Salir" << endl;
	cout << "Opcion: ";
}

// Lee una linea con getline y trata de convertirla a int.
// Devuelve false si el usuario escribio algo que no es un numero.
bool leerEntero(string prompt, int& valor) {
	cout << prompt;
	string linea;
	getline(cin, linea);
	try {
		valor = stoi(linea);
		return true;
	}
	catch (exception&) {
		return false;
	}
}

void ingresarPaciente(LinkedPriorityQueue<Patient>* triage) {
	cout << endl << "Ingresar paciente" << endl;
	cout << "ID: ";
	string id;
	getline(cin, id);

	int condicion = -1;
	bool valido = false;
	while (!valido) {
		if (leerEntero("CONDICION (1-Azul, 2-Rojo, 3-Amarillo, 4-Verde, 5-Blanco): ", condicion)
			&& condicion >= 1 && condicion <= 5) {
			valido = true;
		}
		else {
			cout << "Entrada invalida, intente de nuevo." << endl;
		}
	}

	try {
		Patient patient(id, condicion);
		triage->insert(patient, condicion - 1);
	}
	catch (exception& e) {
		cout << "Error al ingresar paciente: " << e.what() << endl;
	}
}

void atenderPaciente(LinkedPriorityQueue<Patient>* triage) {
	try {
		Patient siguiente = triage->removeMin();
		siguiente.attend();
		cout << endl << "PACIENTE EN ATENCION:" << endl;
		siguiente.print();
	}
	catch (exception&) {
		cout << endl << "No hay pacientes en espera." << endl;
	}
}

int main() {
	LinkedPriorityQueue<Patient>* triage;

	try {
		triage = new LinkedPriorityQueue<Patient>(NUM_PRIORIDADES);
	}
	catch (exception& e) {
		cout << "Error critico: " << e.what() << endl;
		return 1;
	}

	bool corriendo = true;
	while (corriendo) {
		mostrarMenu(triage);

		int opcion;
		if (!leerEntero("", opcion)) {
			cout << "Entrada invalida, intente de nuevo." << endl;
			continue;
		}

		switch (opcion) {
		case 1:
			ingresarPaciente(triage);
			break;
		case 2:
			atenderPaciente(triage);
			break;
		case 3:
			corriendo = false;
			break;
		default:
			cout << "Opcion invalida, intente de nuevo." << endl;
		}
	}

	delete triage;
	cout << "Memoria liberada. Programa finalizado." << endl;
	return 0;
}