#include <iostream>
#include <stdexcept>
#include <string>

#include "HeapPriorityQueue.h"
#include "LinkedPriorityQueue.h"
#include "PriorityQueue.h"

template <typename T>
void demoPriorityQueue(PriorityQueue<T>& queue, const std::string& name) {
	if (!queue.isEmpty() || queue.getSize() != 0)
		throw std::runtime_error("La cola nueva debe estar vacia.");

	queue.insert("Comunicacion", 10);
	queue.insert("Matematica", 3);
	queue.insert("Arquitectura", 3);
	queue.insert("Estadistica", 5);
	queue.insert("Tarea urgente", 0);

	if (queue.getSize() != 5 || queue.min() != "Tarea urgente")
		throw std::runtime_error("La prioridad inicial es incorrecta.");

	if (queue.removeMin() != "Tarea urgente")
		throw std::runtime_error("Se removio el elemento equivocado.");

	queue.clear();
	if (!queue.isEmpty() || queue.getSize() != 0)
		throw std::runtime_error("clear() no vacio la cola.");

	std::cout << name << " funciona correctamente." << std::endl;
}

// This file is a helper/demo module. The actual program entry point is kept in
// "Colas de Prioridad.cpp" to avoid duplicate main() definitions in the folder.
