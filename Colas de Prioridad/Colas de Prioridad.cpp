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

#define NUM_PRIORIDADES 5  // 5 triage levels: Blue(1), Red(2), Yellow(3), Green(4), White(5)

// Display the current triage queue and the menu options.
void mostrarMenu(LinkedPriorityQueue<Patient>* triage) {
	cout << endl << "TRIAGE - Cola de espera:" << endl;
	triage->print();  // Shows all patients grouped by priority level
	cout << endl;
	cout << "1. Ingresar paciente" << endl;
	cout << "2. Atender paciente" << endl;
	cout << "3. Salir" << endl;
	cout << "Opcion: ";
}

// Read a line from stdin and try to convert it to an integer.
// Returns false if the user typed something that isn't a valid number.
// Uses getline + stoi instead of cin >> to avoid leaving junk in the input buffer.
bool leerEntero(string prompt, int& valor) {
	cout << prompt;
	string linea;
	getline(cin, linea);  // Read the whole line (not just up to whitespace)
	try {
		valor = stoi(linea);  // Try to parse the string as an integer
		return true;
	}
	catch (exception&) {
		return false;  // stoi throws if the string isn't a valid number
	}
}

// Ask the user for patient info and insert them into the triage queue.
// The triage level (1-5) maps to priority index (0-4) since arrays are 0-based.
void ingresarPaciente(LinkedPriorityQueue<Patient>* triage) {
	cout << endl << "Ingresar paciente" << endl;
	cout << "ID: ";
	string id;
	getline(cin, id);

	// Keep asking until the user enters a valid triage level (1-5).
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
		triage->insert(patient, condicion - 1);  // -1 because array index starts at 0
	}
	catch (exception& e) {
		cout << "Error al ingresar paciente: " << e.what() << endl;
	}
}

// Remove the highest-priority patient from the queue and mark them as attended.
// removeMin() always returns the patient with the lowest priority number (= most urgent).
void atenderPaciente(LinkedPriorityQueue<Patient>* triage) {
	try {
		Patient siguiente = triage->removeMin();  // Get the most urgent patient
		siguiente.attend();                       // Record the time they were seen
		cout << endl << "PACIENTE EN ATENCION:" << endl;
		siguiente.print();                        // Show their full details
	}
	catch (exception&) {
		cout << endl << "No hay pacientes en espera." << endl;
	}
}

int main() {
	LinkedPriorityQueue<Patient>* triage;

	// Create the triage priority queue with 5 priority levels.
	try {
		triage = new LinkedPriorityQueue<Patient>(NUM_PRIORIDADES);
	}
	catch (exception& e) {
		cout << "Error critico: " << e.what() << endl;
		return 1;
	}

	// Main menu loop — keeps running until the user chooses to exit.
	bool corriendo = true;
	while (corriendo) {
		mostrarMenu(triage);

		int opcion;
		if (!leerEntero("", opcion)) {
			cout << "Entrada invalida, intente de nuevo." << endl;
			continue;  // Skip the rest of the loop and show menu again
		}

		switch (opcion) {
		case 1:
			ingresarPaciente(triage);  // Add a new patient to the queue
			break;
		case 2:
			atenderPaciente(triage);  // See the next most urgent patient
			break;
		case 3:
			corriendo = false;        // Exit the loop
			break;
		default:
			cout << "Opcion invalida, intente de nuevo." << endl;
		}
	}

	delete triage;  // Free the priority queue and all its nodes
	cout << "bye bye <3 Ten lindo dia! :3" << endl;
	return 0;
}