#include <iostream>
#include <string>
#include <vector>
#include "List.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "DLinkedList.h"
#include "Tool.h"
#include "ToolBox.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::stoi;
using std::exception;
using std::vector;

// --- Lectura de enteros validada (solo getline, como pide el enunciado) ---
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

// --- Crea una lista vacia del tipo elegido (1=ArrayList, 2=LinkedList, 3=DLinkedList) ---
List<Tool>* crearLista(int tipo) {
	switch (tipo) {
	case LIST_ARRAY:
		return new ArrayList<Tool>();
	case LIST_LINKED:
		return new LinkedList<Tool>();
	case LIST_DLINKED:
		return new DLinkedList<Tool>();
	default:
		throw std::runtime_error("Tipo de lista invalido.");
	}
}

// --- Llena la lista de herramientas disponibles con el catalogo fijo ---
void cargarHerramientasDisponibles(List<Tool>* lista) {
	lista->append(Tool("Phillips screwdriver", 0.25, 1.5));
	lista->append(Tool("Flat screwdriver", 0.25, 1.5));
	lista->append(Tool("Hammer", 1, 3.5));
	lista->append(Tool("French wrench", 0.75, 3));
	lista->append(Tool("Hacksaw", 0.5, 3));
	lista->append(Tool("Scissors", 0.25, 2.2));
	lista->append(Tool("Cutter", 0.25, 1.5));
	lista->append(Tool("Pliers", 0.5, 1.8));
	lista->append(Tool("Pincers", 0.25, 2));
	lista->append(Tool("Drill", 2, 4));
	lista->append(Tool("Locking pliers", 0.5, 2.5));
	lista->append(Tool("Measuring tape", 0.5, 1.5));
}

int pedirTipoLista() {
	int tipo = -1;
	bool valido = false;
	while (!valido) {
		cout << "Choose the type of list to use:" << endl;
		cout << "1. ArrayList" << endl;
		cout << "2. LinkedList" << endl;
		cout << "3. DLinkedList" << endl;
		if (leerEntero("", tipo) && tipo >= 1 && tipo <= 3) {
			valido = true;
		}
		else {
			cout << "Entrada invalida, intente de nuevo." << endl << endl;
		}
	}
	return tipo;
}

// Devuelve {maxWeight, maxVolume} segun el tamano elegido
void pedirTamanoCaja(double& maxWeight, double& maxVolume) {
	int opcion = -1;
	bool valido = false;
	while (!valido) {
		cout << "Choose the size of the toolbox:" << endl;
		cout << "1. Small  (max weight = 2, max volume = 10)" << endl;
		cout << "2. Medium (max weight = 4, max volume = 14)" << endl;
		cout << "3. Large  (max weight = 6, max volume = 20)" << endl;
		if (leerEntero("", opcion) && opcion >= 1 && opcion <= 3) {
			valido = true;
		}
		else {
			cout << "Entrada invalida, intente de nuevo." << endl << endl;
		}
	}
	switch (opcion) {
	case 1: maxWeight = 2; maxVolume = 10; break;
	case 2: maxWeight = 4; maxVolume = 14; break;
	case 3: maxWeight = 6; maxVolume = 20; break;
	}
}

void agregarHerramienta(ToolBox* caja, List<Tool>* disponibles) {
	cout << endl << "Choose tool to add:" << endl;
	disponibles->goToStart();
	int i = 1;
	while (!disponibles->atEnd()) {
		cout << i << ". " << disponibles->getElement() << endl;
		disponibles->next();
		i++;
	}

	int opcion = -1;
	if (!leerEntero("", opcion) || opcion < 1 || opcion > disponibles->getSize()) {
		cout << "Opcion invalida." << endl;
		return;
	}

	disponibles->goToPos(opcion - 1);
	Tool elegida = disponibles->getElement();

	try {
		caja->add(elegida);
	}
	catch (exception& e) {
		cout << endl << "Error: " << e.what() << endl;
	}
}

void removerHerramienta(ToolBox* caja) {
	cout << endl;
	caja->print();

	if (caja->toolCount() == 0) {
		cout << "Toolbox is empty!" << endl;
		return;
	}

	int opcion = -1;
	if (!leerEntero("Choose tool to remove: ", opcion) || opcion < 1 || opcion > caja->toolCount()) {
		cout << "Opcion invalida." << endl;
		return;
	}

	try {
		caja->remove(opcion - 1);
	}
	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
	}
}

int main() {
	List<Tool>* herramientasDisponibles = nullptr;
	ToolBox* caja = nullptr;

	try {
		int tipoLista = pedirTipoLista();

		double maxWeight, maxVolume;
		pedirTamanoCaja(maxWeight, maxVolume);

		herramientasDisponibles = crearLista(tipoLista);
		cargarHerramientasDisponibles(herramientasDisponibles);

		caja = new ToolBox(maxWeight, maxVolume, tipoLista);
	}
	catch (exception& e) {
		cout << "Error critico al iniciar el programa: " << e.what() << endl;
		delete herramientasDisponibles;
		delete caja;
		return 1;
	}

	bool corriendo = true;
	while (corriendo) {
		cout << endl;
		caja->print();
		cout << endl;
		cout << "Choose toolbox operation:" << endl;
		cout << "1. Add tool" << endl;
		cout << "2. Remove tool" << endl;
		cout << "3. Clear toolbox" << endl;
		cout << "0. Exit" << endl;

		int opcion = -1;
		if (!leerEntero("", opcion)) {
			cout << "Entrada invalida, intente de nuevo." << endl;
			continue;
		}

		try {
			switch (opcion) {
			case 1:
				agregarHerramienta(caja, herramientasDisponibles);
				break;
			case 2:
				removerHerramienta(caja);
				break;
			case 3:
				caja->clear();
				break;
			case 0:
				corriendo = false;
				break;
			default:
				cout << "Opcion invalida, intente de nuevo." << endl;
			}
		}
		catch (exception& e) {
			cout << "Error: " << e.what() << endl;
		}
	}

	delete herramientasDisponibles;
	delete caja;
	cout << "Memoria liberada. Programa finalizado." << endl;
	return 0;
}