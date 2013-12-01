#include "BottlingPlant.h"
#include "Printer.h"
#include "NameServer.h"
#include "Truck.h"
#include "MPRNG.h"

extern MPRNG mprng;

void BottlingPlant::main()
{
	prt->print(Printer::BottlingPlant, 'S');
	prod = new unsigned int[4];
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
		_Accept(~BottlingPlant) {
			closingDown = true;
			_Accept(getShipment) {}
			delete truck;
			break;
		}
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
	if (closingDown) return true;
	prt->print(Printer::BottlingPlant, 'P');
	for (unsigned int i = 0; i < 4; i++) {
		cargo[i] = prod[i];
	}
	return false;
}
