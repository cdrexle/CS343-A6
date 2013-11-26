#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Printer.h"

using namespace std;

string toString(unsigned int num) {
	stringstream s;
	s << num;
	string w;
	s >> w;
	return w;
}

string stateToString(char val) {
	stringstream s;
	s << val;
	string w;
	s >> w;
	return w;
}

unsigned int Printer::getId(Printer::Kind kind) {
	switch(kind) {
		case Printer::Parent:
			return 0;
		case Printer::WATCardOffice:
			return 1;
		case Printer::NameServer:
			return 2;
		case Printer::Truck:
			return 3;
		case Printer::BottlingPlant:
			return 4;
	}
}

unsigned int Printer::getId(Printer::Kind kind, unsigned int id) {
	switch(kind) {
		case Printer::Student:
			return 5+id;
		case Printer::Vending:
			return 5+nStudents+id;
		case Printer::Courier:
			return 5+nStudents+nVendingMachines+id;
	}
}

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) : 
	nStudents(numStudents),
	nVendingMachines(numVendingMachines),
	nCouriers(numCouriers),
	buffer(5+numStudents+numVendingMachines+numCouriers)
{
	cout << "Parent" << "\t";
	cout << "WATOff" << "\t";
	cout << "Names" << "\t";
	cout << "Truck" << "\t";
	cout << "Plant" << "\t";
	for (unsigned int i = 0; i < numStudents; i++) {
		cout << "Stud" << i << "\t";
	}
	for (unsigned int i = 0; i < numVendingMachines; i++) {
		cout << "Mach" << i << "\t";
	}
	for (unsigned int i = 0; i < numCouriers; i++) {
		cout << "Cour" << i << "\t";
	}
	cout << endl;
	for (unsigned int i = 0; i < 5+numStudents+numVendingMachines+numCouriers; i++) {
		cout << "*******\t";
	}
	cout << endl;
}

Printer::~Printer() {
	cout << "***********************" << endl;
}

void Printer::flushBuffer() {
	bool allEmpty = true;
	for (unsigned int i = 0; i < buffer.size(); i++) {
		if (buffer[i] != "") {
			allEmpty = false;
			break;
		}
	}
	if (allEmpty) return;

	for (unsigned int i = 0; i < buffer.size(); i++) {
		cout << buffer[i] << "\t";
	}
	for (unsigned int i = 0; i < buffer.size(); i++) {
		buffer[i] = "";
	}
	cout << endl;
}

void Printer::printPrimitive(unsigned int id, string val) {
	if (val != "F") {
		if (buffer[id] != "") flushBuffer();
		buffer[id] = val;
	}
	else {
		flushBuffer();
		for (unsigned int i = 0; i < buffer.size(); i++) {
			if (i != id) cout << "...\t";
			else cout << "F\t";
		}
		cout << endl;
	}
}

void Printer::print( Printer::Kind kind, char state ) {
	unsigned int id = getId(kind);
	printPrimitive(id, stateToString(state));
}

void Printer::print( Kind kind, char state, int value1 ) {
	unsigned int id = getId(kind);
	printPrimitive(id, stateToString(state)+toString(value1));
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
	unsigned int id = getId(kind);
	printPrimitive(id, stateToString(state)+toString(value1)+","+toString(value2));
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
	unsigned int id = getId(kind, lid);
	printPrimitive(id, stateToString(state));
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	unsigned int id = getId(kind, lid);
	printPrimitive(id, stateToString(state)+toString(value1));
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	unsigned int id = getId(kind, lid);
	printPrimitive(id, stateToString(state)+toString(value1)+","+toString(value2));
}
