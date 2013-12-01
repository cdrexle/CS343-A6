#include "Truck.h"
#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"
#include "MPRNG.h"

void Truck::main()
{
	prt->print(Printer::Truck, 'S');
	// initialize cargo
	cargo = new unsigned int[4];
	VendingMachine** machineList = nameServer->getMachineList();
	while(true) {
		// get coffee
		yield(mprng(9) + 1);
		bool closingDown = plant->getShipment(cargo);
		// exit if closing down
		if (closingDown) break;

		// calculate initial soda in cargo
		int totalSoda = 0;
		for(int i = 0; i < 4; i++)
		{
			totalSoda += cargo[i];
		}
		prt->print(Printer::Truck, 'P', totalSoda);

		for (unsigned int i = 0; i < numVendingMachines; i++) {

			prt->print(Printer::Truck, 'd', machineList[i]->getId(), totalSoda);
			
			//get machine inventory
			unsigned int* inventory = machineList[i]->inventory();
			unsigned int amountNotFilled = 0;
			for (unsigned int j = 0; j < 4; j++) {
				// calculate amount to fill
				unsigned int amountToStock = maxStockPerFlavour - inventory[j];
				// if not enough, sill what you can and remember how much was unfilled
				if (amountToStock > cargo[j]) {
					amountNotFilled += (amountToStock - cargo[j]);
					amountToStock = cargo[j];
				}
				// transfer soda
				cargo[j] -= amountToStock;
				inventory[j] += amountToStock;
				totalSoda -= amountToStock;
			}
			if (amountNotFilled > 0) prt->print(Printer::Truck, 'U', machineList[i]->getId(), amountNotFilled);
			prt->print(Printer::Truck, 'D', machineList[i]->getId(), totalSoda);
			
			//signal to vending machine that its restocked
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
