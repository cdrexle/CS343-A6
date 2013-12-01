#ifndef NAMESERVER_H
#define NAMESERVER_H

_Monitor Printer;
_Task VendingMachine;

#include <vector>

_Task NameServer {
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
  private:
  	Printer* prt;
	unsigned int numVendingMachines;
	unsigned int numStudents;
  	VendingMachine** vendingMachineList;
  	unsigned int numMachinesRegistered;
  	std::vector<unsigned int> studentVendingMachines;
  	unsigned int studentIdToUpdate;
};

#endif
