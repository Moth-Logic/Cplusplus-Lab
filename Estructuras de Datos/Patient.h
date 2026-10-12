#pragma once

#include <string>
#include <ctime>
#include <cstdio>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;
using std::endl;

// Patient class represents a person waiting in the hospital triage system.
// Each patient has an ID, a triage level (1=Blue/Critical to 5=White/Non-urgent),
// and tracks their arrival time and waiting time.
class Patient {
private:
	string id;          // Patient's unique identifier
	int level;          // Triage level: 1 (Blue) through 5 (White)
	time_t arrival;     // Timestamp when the patient arrived (set automatically)
	time_t attended;    // Timestamp when the patient was seen by a doctor (0 if not yet)
	time_t waitingTime; // How long the patient waited in seconds (attended - arrival)

	// Convert a triage level number to its human-readable label.
	string levelLabel(int level) {
		switch (level) {
		case 1: return "AZUL - Resucitacion";    // Blue: needs immediate resuscitation
		case 2: return "ROJO - Emergencia";      // Red: emergency, very urgent
		case 3: return "AMARILLO - Urgente";     // Yellow: urgent but stable
		case 4: return "VERDE - Menos urgente";  // Green: less urgent
		case 5: return "BLANCO - No urgente";    // White: non-urgent
		default: return "DESCONOCIDO";
		}
	}

	// Format a time_t value as a readable date-time string (YYYY-MM-DD HH:MM:SS).
	string formatTime(time_t t) {
		if (t == 0)
			return "N/A";  // Patient hasn't been attended yet
		struct tm info;
		localtime_s(&info, &t);  // Convert timestamp to local time components
		char buffer[32];
		sprintf_s(buffer, sizeof(buffer), "%d-%d-%d %d:%d:%d",
			info.tm_year + 1900, info.tm_mon + 1, info.tm_mday,
			info.tm_hour, info.tm_min, info.tm_sec);
		return string(buffer);
	}

public:
	// Main constructor: creates a patient with ID and triage level.
	// Arrival time is set to the current moment automatically.
	Patient(string id, int level) {
		this->id = id;
		this->level = level;
		arrival = time(nullptr);  // Record when the patient arrived
		attended = 0;            // Not yet attended
		waitingTime = 0;
	}

	// Default constructor: required by LinkedQueue<Patient> so it can create
	// empty Patient objects when managing its internal nodes.
	Patient() {
		id = "";
		level = 0;
		arrival = 0;
		attended = 0;
		waitingTime = 0;
	}

	// Mark the patient as attended and calculate their waiting time.
	void attend() {
		attended = time(nullptr);               // Record current time as the attended time
		waitingTime = attended - arrival;        // Calculate total wait in seconds
	}

	// Print full patient details (ID, condition, arrival/attended times, wait).
	void print() {
		cout << "ID: " << id << endl;
		cout << "CONDICION: " << level << " " << levelLabel(level) << endl;
		cout << "LLEGADA:   " << formatTime(arrival) << endl;
		cout << "ATENDIDO:  " << formatTime(attended) << endl;
		cout << "ESPERA:    " << waitingTime << " s" << endl;
	}

	// Overload << operator so we can print a Patient with cout.
	// This is used when printing the queue contents.
	friend ostream& operator<<(ostream& os, const Patient& p) {
		os << "(Id: " << p.id << ", Nivel: " << p.level << ")";
		return os;
	}
};