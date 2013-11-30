#include "NameServer.h"
#include "Printer.h"
#include "VendingMachine.h"
#include <vector>

using namespace std;

void NameServer::main()
{
	vendingMachineList = new VendingMachine*[numVendingMachines];
	unsigned int vid = 0;
	for (unsigned int i = 0; i < numStudents; i++) {
		studentVendingMachines.push_back(vid);
		vid = (vid + 1) % numVendingMachines;
	}
	while(true) {
		_Accept(~NameServer) {}
		or _When(numMachinesRegistered < numVendingMachines) _Accept(VMregister) {
			numMachinesRegistered++;
		}
		or _When (numMachinesRegistered == numVendingMachines) _Accept(getMachine, getMachineList) {}
	}
}

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) :
	prt(&prt),
	numVendingMachines(numVendingMachines),
	numStudents(numStudents)
{}

NameServer::~NameServer() {
	delete[] vendingMachineList;
}

void NameServer::VMregister( VendingMachine *vendingmachine )
{
	vendingMachineList[numMachinesRegistered] = vendingmachine;
}

VendingMachine *NameServer::getMachine( unsigned int id )
{
	unsigned int vid = studentVendingMachines[id];
	studentVendingMachines[id] = (studentVendingMachines[id] + 1) % numVendingMachines;
	return vendingMachineList[vid];
}

VendingMachine **NameServer::getMachineList()
{
	return vendingMachineList;
}
