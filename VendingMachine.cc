#include "VendingMachine.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"
#include <iostream>

void VendingMachine::main()
{
	prt->print(Printer::Vending, id, 'S', sodaCost);
	stock = new unsigned int[4];
	for (unsigned int i = 0; i < 4; i++) {
		stock[i] = 0;
	}
	nameServer->VMregister(this);
	while (true) {
		_Accept(~VendingMachine) {
			break;
		}
		or _When(!beingStocked) _Accept(inventory) {
			prt->print(Printer::Vending, id, 'r');
			beingStocked = true;
		}
		or _When(beingStocked) _Accept(restocked) {
			prt->print(Printer::Vending, id, 'R');
			beingStocked = false;
		}
		or _When(!beingStocked) _Accept(buy) {}
	}
	prt->print(Printer::Vending, id, 'F');
}
VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour ) :
	prt(&prt),
	nameServer(&nameServer),
	id(id),
	sodaCost(sodaCost),
	maxStockPerFlavour(maxStockPerFlavour),
	beingStocked(false)
{}

VendingMachine::~VendingMachine() {
	delete[] stock;
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card )
{
	if (stock[flavour] == 0) return STOCK;
	// There's at least one soda for the student
	
	if (card.getBalance() < sodaCost) return FUNDS;
	// balance >= sodaCost
	
	stock[flavour] -= 1;
	card.withdraw(sodaCost);

	prt->print(Printer::Vending, id, 'B', flavour, stock[flavour]);
	
	return BUY;
}

unsigned int *VendingMachine::inventory()
{
	return stock;
}

void VendingMachine::restocked() {}

_Nomutex unsigned int VendingMachine::cost()
{
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId()
{
    return id;
}
