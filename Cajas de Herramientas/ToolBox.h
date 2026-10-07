#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "DLinkedList.h"
#include "Tool.h"

using std::runtime_error;
using std::cout;
using std::endl;

// Tipos de lista que puede usar la caja (y tambien el main para la
// lista de herramientas disponibles). Mismos numeros que el menu.
#define LIST_ARRAY 1
#define LIST_LINKED 2
#define LIST_DLINKED 3

// ToolBox: la caja de herramientas. Guarda sus herramientas en una
// List<Tool>*, y el tipo real (ArrayList/LinkedList/DLinkedList) se
// decide en tiempo de ejecucion segun lo que elija el usuario.
class ToolBox {
private:
	double maxWeight;
	double maxVolume;
	double currentWeight;
	double currentVolume;
	List<Tool>* box;

public:
	ToolBox(double maxWeight, double maxVolume, int listType) {
		this->maxWeight = maxWeight;
		this->maxVolume = maxVolume;
		currentWeight = 0;
		currentVolume = 0;

		switch (listType) {
		case LIST_ARRAY:
			box = new ArrayList<Tool>();
			break;
		case LIST_LINKED:
			box = new LinkedList<Tool>();
			break;
		case LIST_DLINKED:
			box = new DLinkedList<Tool>();
			break;
		default:
			throw runtime_error("Tipo de lista invalido.");
		}
	}

	~ToolBox() {
		delete box;
	}

	ToolBox(const ToolBox&) = delete;
	void operator=(const ToolBox&) = delete;

	void add(Tool t) {
		if (currentWeight + t.weight > maxWeight)
			throw runtime_error("The toolbox weight limit has been exceeded.");
		if (currentVolume + t.volume > maxVolume)
			throw runtime_error("The toolbox volume limit has been exceeded.");

		currentWeight += t.weight;
		currentVolume += t.volume;
		box->append(t);
	}

	Tool remove(int pos) {
		if (box->getSize() == 0)
			throw runtime_error("Toolbox is empty!");
		if (pos < 0 || pos >= box->getSize())
			throw runtime_error("Posicion invalida.");

		box->goToPos(pos);
		Tool removed = box->remove();
		currentWeight -= removed.weight;
		currentVolume -= removed.volume;
		return removed;
	}

	void clear() {
		box->clear();
		currentWeight = 0;
		currentVolume = 0;
	}

	double getMaxWeight() { return maxWeight; }
	double getMaxVolume() { return maxVolume; }
	double getCurrentWeight() { return currentWeight; }
	double getCurrentVolume() { return currentVolume; }

	int toolCount() {
		return box->getSize();
	}

	void print() {
		cout << "Toolbox contents:" << endl;
		if (box->getSize() > 0) {
			box->goToStart();
			int i = 1;
			while (!box->atEnd()) {
				cout << "\t" << i << ". " << box->getElement() << endl;
				box->next();
				i++;
			}
		}
		cout << "Weight: " << currentWeight << "/" << maxWeight << endl;
		cout << "Volume: " << currentVolume << "/" << maxVolume << endl;
	}
};
