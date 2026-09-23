#pragma once

#include <string>
#include <iostream>

using std::string;
using std::ostream;

// Tool: representa una herramienta dentro de la caja.
// Atributos publicos a proposito (asi lo pide el enunciado).
class Tool {
public:
	string name;
	double weight;
	double volume;

	// Constructor vacio: lo pide ArrayList (new E[max]) y los nodos
	// centinela de las listas enlazadas.
	Tool() {
		name = "";
		weight = 0;
		volume = 0;
	}

	Tool(string name, double weight, double volume) {
		this->name = name;
		this->weight = weight;
		this->volume = volume;
	}

	// No hace falta tocar la regla de tres: Tool no tiene memoria
	// dinamica propia, asi que copiar/destruir por defecto ya esta bien.

	friend ostream& operator<<(ostream& os, const Tool& tool) {
		os << tool.name << " (w=" << tool.weight << ", v=" << tool.volume << ")";
		return os;
	}
};