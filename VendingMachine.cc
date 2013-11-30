#include "VendingMachine.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"

void VendingMachine::main()
{
	stock = new unsigned int[4];
	for (unsigned int i = 0; i < 4; i++) {
		stock[i] = 0;
	}
	nameServer->VMregister(this);
	while (true) {
		_Accept(~VendingMachine) {}
		or _When(!beingStocked) _Accept(inventory) {
			beingStocked = true;
		}
		or _When(beingStocked) _Accept(restocked) {
			beingStocked = false;
		}
		or _When(!beingStocked) _Accept(buy) {}
	}
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
