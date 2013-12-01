#include "NameServer.h"
#include "Printer.h"
#include "VendingMachine.h"
#include <vector>
#include <iostream>

using namespace std;

void NameServer::main()
{
	prt->print(Printer::NameServer, 'S');
	// initialize vending machine list
	vendingMachineList = new VendingMachine*[numVendingMachines];
	// Set initial vending machines for students
	unsigned int vid = 0;
	for (unsigned int i = 0; i < numStudents; i++) {
		studentVendingMachines.push_back(vid);
		vid = (vid + 1) % numVendingMachines;
	}
	while(true) {
		_Accept(~NameServer) 
		{
			break;
		}
		// If all machines register, don't accept any more registrations
		or _When(numMachinesRegistered < numVendingMachines) _Accept(VMregister) {
			numMachinesRegistered++;
		}
		// If not all machines registered, don't accept getting machines
		or _When (numMachinesRegistered == numVendingMachines) _Accept(getMachine) {
			// update next machine for student
			studentVendingMachines[studentIdToUpdate] = (studentVendingMachines[studentIdToUpdate] + 1) % numVendingMachines;
		}
		or _When (numMachinesRegistered == numVendingMachines) _Accept(getMachineList) {}
	}
	prt->print(Printer::NameServer, 'F');
}

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) :
	prt(&prt),
	numVendingMachines(numVendingMachines),
	numStudents(numStudents),
	numMachinesRegistered(0)
{}

NameServer::~NameServer() {
	delete[] vendingMachineList;
}

void NameServer::VMregister( VendingMachine *vendingmachine )
{
	prt->print(Printer::NameServer, 'R', vendingmachine->getId());
	vendingMachineList[numMachinesRegistered] = vendingmachine;
}

VendingMachine *NameServer::getMachine( unsigned int id )
{

	unsigned int vid = studentVendingMachines[id];
	studentIdToUpdate = id;

	prt->print(Printer::NameServer, 'N', id, vid);

	return vendingMachineList[vid];
}

VendingMachine **NameServer::getMachineList()
{
	return vendingMachineList;
}
