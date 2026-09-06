#pragma once

#include <string>
#include <ctime>
#include <cstdio>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;
using std::endl;

class Patient {
private:
	string id;
	int level;
	time_t arrival;
	time_t attended;
	time_t waitingTime;

	string levelLabel(int level) {
		switch (level) {
		case 1: return "AZUL - Resucitacion";
		case 2: return "ROJO - Emergencia";
		case 3: return "AMARILLO - Urgente";
		case 4: return "VERDE - Menos urgente";
		case 5: return "BLANCO - No urgente";
		default: return "DESCONOCIDO";
		}
	}
	string formatTime(time_t t) {
		if (t == 0)
			return "N/A";
		struct tm* info = localtime(&t);
		char buffer[32];
		sprintf(buffer, "%d-%d-%d %d:%d:%d",
			info->tm_year + 1900, info->tm_mon + 1, info->tm_mday,
			info->tm_hour, info->tm_min, info->tm_sec);
		return string(buffer);
	}

public:
	Patient(string id, int level) {
		this->id = id;
		this->level = level;
		arrival = time(nullptr);
		attended = 0;
		waitingTime = 0;
	}
	// Constructor por defecto: lo pide el enunciado para que LinkedQueue<Patient> pueda crear nodos sin problema.
	Patient() {
		id = "";
		level = 0;
		arrival = 0;
		attended = 0;
		waitingTime = 0;
	}
	void attend() {
		attended = time(nullptr);
		waitingTime = attended - arrival;
	}
	void print() {
		cout << "ID: " << id << endl;
		cout << "CONDICION: " << level << " " << levelLabel(level) << endl;
		cout << "LLEGADA:   " << formatTime(arrival) << endl;
		cout << "ATENDIDO:  " << formatTime(attended) << endl;
		cout << "ESPERA:    " << waitingTime << " s" << endl;
	}

	friend ostream& operator<<(ostream& os, const Patient& p) {
		os << "(Id: " << p.id << ", Nivel: " << p.level << ")";
		return os;
	}
};