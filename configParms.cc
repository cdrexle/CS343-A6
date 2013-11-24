#include "configParms.h"
#include <iostream>
#include <fstream>
#include <sstream>

void processConfigFile( const char *configFile, ConfigParms &cparms ) {
	ifstream file;
	file.open(configFile);
	if (!file.is_open()) {
		cout << "error opening file" << endl;
		return;
	}
	
	string s;
	while (getline(file, s)) {
		if (s.substr(0, 8) == "SodaCost") {
			stringstream ss (s.substr(8));
			unsigned int n;
			ss >> n;
			cparms.sodaCost = n;
		}
		else if (s.substr(0, 11) == "NumStudents") {
			stringstream ss (s.substr(11));
			unsigned int n;
			ss >> n;
			cparms.numStudents = n;
		}
		else if (s.substr(0, 12) == "MaxPurchases") {
			stringstream ss (s.substr(12));
			unsigned int n;
			ss >> n;
			cparms.maxPurchases = n;
		}
		else if (s.substr(0, 18) == "NumVendingMachines") {
			stringstream ss (s.substr(18));
			unsigned int n;
			ss >> n;
			cparms.numVendingMachines = n;
		}
		else if (s.substr(0, 18) == "MaxStockPerFlavour") {
			stringstream ss (s.substr(18));
			unsigned int n;
			ss >> n;
			cparms.maxStockPerFlavour = n;
		}
		else if (s.substr(0, 20) == "MaxShippedPerFlavour") {
			stringstream ss (s.substr(20));
			unsigned int n;
			ss >> n;
			cparms.maxShippedPerFlavour = n;
		}
		else if (s.substr(0, 20) == "TimeBetweenShipments") {
			stringstream ss (s.substr(20));
			unsigned int n;
			ss >> n;
			cparms.timeBetweenShipments = n;
		}
		else if (s.substr(0, 13) == "ParentalDelay") {
			stringstream ss (s.substr(13));
			unsigned int n;
			ss >> n;
			cparms.parentalDelay = n;
		}
		else if (s.substr(0, 11) == "NumCouriers") {
			stringstream ss (s.substr(11));
			unsigned int n;
			ss >> n;
			cparms.numCouriers = n;
		}
	}
}
