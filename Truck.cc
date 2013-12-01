#include "Truck.h"
#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"
#include "MPRNG.h"

extern MPRNG mprng; 

void Truck::main()
{
	prt->print(Printer::Truck, 'S');
	cargo = new unsigned int[4];
	VendingMachine** machineList = nameServer->getMachineList();
	while(true) {
		yield(mprng(9) + 1); // get coffee
		bool closingDown = plant->getShipment(cargo);
		if (closingDown) break;

		int totalSoda = 0;
		for(int i = 0; i < 4; i++)
		{
			totalSoda += cargo[i];
		}
		prt->print(Printer::Truck, 'P', totalSoda);

		for (unsigned int i = 0; i < numVendingMachines; i++) {

			prt->print(Printer::Truck, 'd', machineList[i]->getId(), totalSoda);

			unsigned int* inventory = machineList[i]->inventory();
			unsigned int amountNotFilled = 0;
			for (unsigned int j = 0; j < 4; j++) {
				unsigned int amountToStock = maxStockPerFlavour - inventory[j];
				if (amountToStock > cargo[j]) {
					amountNotFilled += (amountToStock - cargo[j]);
					amountToStock = cargo[j];
				}
				cargo[j] -= amountToStock;
				inventory[j] += amountToStock;
				totalSoda -= amountToStock;
			}
			if (amountNotFilled > 0) prt->print(Printer::Truck, 'U', machineList[i]->getId(), amountNotFilled);
			prt->print(Printer::Truck, 'D', machineList[i]->getId(), totalSoda);
			
			machineList[i]->restocked();
		}
	}
	prt->print(Printer::Truck, 'F');
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
