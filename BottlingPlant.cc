#include "BottlingPlant.h"
#include "Printer.h"
#include "NameServer.h"
#include "Truck.h"
#include "MPRNG.h"

extern MPRNG mprng;

void BottlingPlant::main()
{
	prt->print(Printer::BottlingPlant, 'S');
	// Initialize production run array
	prod = new unsigned int[4];
	//Initialize the truck
	Truck* truck = new Truck(*prt, *nameServer, *this, numVendingMachines, maxStockPerFlavour);
	while(true) {
		// Production run
		int totalProduction = 0;
		for (unsigned int i = 0; i < 4; i++) {
			prod[i] = mprng(maxShippedPerFlavour);
			totalProduction += prod[i];
		}

		prt->print(Printer::BottlingPlant, 'G', totalProduction);

		yield(timeBetweenShipments);
		// if closing down, wait for truck to come back
		_Accept(~BottlingPlant) {
			closingDown = true;
			_Accept(getShipment) {}
			delete truck;
			break;
		}
		// wait for truck
		or _Accept(getShipment) {}
	}
	prt->print(Printer::BottlingPlant, 'F');
}

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ) :
	prt(&prt),
	nameServer(&nameServer),
	numVendingMachines(numVendingMachines),
	maxShippedPerFlavour(maxShippedPerFlavour),
	maxStockPerFlavour(maxStockPerFlavour),
	timeBetweenShipments(timeBetweenShipments),
	closingDown(false)
{}

BottlingPlant::~BottlingPlant() {
	delete[] prod;
}

bool BottlingPlant::getShipment( unsigned int cargo[] )
{
	// if closing down, notify truck
	if (closingDown) return true;
	prt->print(Printer::BottlingPlant, 'P');
	// copy cargo into truck
	for (unsigned int i = 0; i < 4; i++) {
		cargo[i] = prod[i];
	}
	return false;
}
