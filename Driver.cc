#include "mprng.h"
#include "config.h"
#include "Printer.h"
#include "Bank.h"
#include "Parent.h"
#include "WATCardOffice.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "BottlingPlant.h"
#include "Student.h"
#include <iostream>
#include <vector>

using namespace std;

void uMain::main()
{
	char *configName = "soda.config";
	int seed = getpid();
	if(argc >= 2)
	{
		configName = argv[1];
		if(argc >= 3)
		{
			seed = atoi(argv[2]);
			if(argc >= 4)
			{
				//Error 
				return;
			}
		}
	}
	ConfigParms configParms;
	processConfigFile(configName, configParms);
	//Initialize all the necessary classes
	
	Printer *printer = new Printer(configParms.numStudents, configParms.numVendingMachines, configParms.numCouriers);
	Bank *bank = new Bank(configParms.numStudents);
	Parent *parent = new Parent(*printer, *bank, configParms.numStudents, configParms.parentalDelay);
	WATCardOffice *watCardOffice = new WATCardOffice(*printer, *bank, configParms.numCouriers);
	NameServer *nameServer = new NameServer(*printer, configParms.numVendingMachines, configParms.numStudents);
	
	vector <VendingMachine *>machineList;
	
	for(int i = 0; i < configParms.numVendingMachines; i++)
	{
		VendingMachine *vendingMachine = new VendingMachine(*printer, *nameServer, i, configParms.sodaCost, configParms.maxStockPerFlavour);
		machineList.push_back(vendingMachine); 
	}
	
	BottlingPlant *bottlingPlant = new BottlingPlant(*printer, *nameServer, configParms.numVendingMachines,
														configParms.maxShippedPerFlavour, configParms.maxStockPerFlavour,
														configParms.timeBetweenShipments);
	vector <Student *> studentList;
	
	for(int i = 0; i < configParms.numStudents; i++)
	{
		Student *student = new Student(*printer, *nameServer, *watCardOffice, i, configParms.maxPurchases);
		studentList.push_back(student);
	}

	for(int i = 0; i < studentList.size(); i++)
	{
		Student *temp = studentList[i];
		delete temp;
	}
	delete bottlingPlant;
	for(int i = 0; i < machineList.size(); i++)
	{
		VendingMachine *temp = machineList[i];
		delete temp;
	}
	delete nameServer;
	delete watCardOffice;
	delete parent;
	delete bank;
	delete printer;
}
