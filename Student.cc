#include "Student.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "VendingMachine.h"
#include "MPRNG.h"

extern MPRNG mprng;

void Student::main()
{
	int currentNumPurchase = 0;
	//Determines a favorite within [0,3]
	int favoriteFlavour = mprng(3);
	//Determines the number of purchases within [1, maxPurchase]
	int purchaseNum = mprng(numPurchase - 1) + 1;
	while(currentNumPurchase < purchaseNum)
	{
		//Create WAT card
		WATCard::FWATCard newWATCard = office->create(Id, 5);
		//Get vending machine
		VendingMachine *tempVendingMachine = server->getMachine(Id);
		int purchaseStatus = -1;
		while(purchaseStatus != VendingMachine::BUY)
		{
			yield(mprng(9) + 1);
			//Attempt to purchase soda
			purchaseStatus = tempVendingMachine->buy((VendingMachine::Flavours)favoriteFlavour, *newWATCard());		
			//If the WAT card has insufficient funds, call transfer funds
			if(purchaseStatus == VendingMachine::FUNDS)
			{
				//Try and catch the Lost exception during the transfer 
				try
				{
					office->transfer(Id, tempVendingMachine->cost() + 5, newWATCard());
				}
				//If the WATCard is lost during transfer, create a new one
				catch(WATCardOffice::Lost &lost)
				{
					newWATCard = office->create(Id, 5);
				}
			}
			//If the current vending machine is out of stock, go to the next machine
			if(purchaseStatus == VendingMachine::STOCK)
			{
				tempVendingMachine = server->getMachine(Id);
			}
		}
		//If the soda is bought successfully, increment the counter
		currentNumPurchase++;
	}
}

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases )
{
	Id = id;
	printer = &prt;
	server = &nameServer;
	office = &cardOffice;
	numPurchase = maxPurchases;
}
