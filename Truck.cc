#include "Truck.h"
#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"
#include "MPRNG.h"

extern MPRNG mprng; 

void Truck::main()
{
	cargo = new unsigned int[4];
	VendingMachine** machineList = nameServer->getMachineList();
	while(true) {
		yield(mprng(9) + 1); // get coffee
		bool closingDown = plant->getShipment(cargo);
		if (closingDown) break;
		for (unsigned int i = 0; i < numVendingMachines; i++) {
			unsigned int* inventory = machineList[i]->inventory();
			for (unsigned int j = 0; j < 4; j++) {
				unsigned int amountToStock = maxStockPerFlavour - inventory[j];
				if (amountToStock > cargo[j]) amountToStock = cargo[j];
				cargo[j] -= amountToStock;
				inventory[j] += amountToStock;
			}
			machineList[i]->restocked();
		}
	}
}

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
	prt(&prt),
	nameServer(&nameServer),
	plant(&plant),
	numVendingMachines(numVendingMachines),
	maxStockPerFlavour(maxStockPerFlavour)
{}

Truck::~Truck() {
	delete[] cargo;
}
