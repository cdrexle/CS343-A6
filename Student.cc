#include "Student.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "VendingMachine.h"
#include "MPRNG.h"
#include <iostream>

extern MPRNG mprng;

void Student::main()
{
	int currentNumPurchase = 0;
	//Determines a favorite within [0,3]
	int favoriteFlavour = mprng(3);
	//Determines the number of purchases within [1, maxPurchase]
	int purchaseNum = mprng(numPurchase - 1) + 1;
	printer->print(Printer::Student, Id, 'S', favoriteFlavour, purchaseNum);
	WATCard::FWATCard newWATCard;
	//Create WAT card		
	newWATCard = office->create(Id, 5);
	VendingMachine *tempVendingMachine = server->getMachine(Id);
	while(currentNumPurchase < purchaseNum)
	{
		//Get vending machine
		printer->print(Printer::Student, Id, 'V', tempVendingMachine->getId());
		int purchaseStatus = -1;
		while(purchaseStatus != VendingMachine::BUY)
		{
			yield(mprng(9) + 1);
			bool lostCard = true;
			while(lostCard)
			{
				lostCard = false;
				//Use getBalance to explicit check whether the card was lost when creating it
				try
				{
					newWATCard()->getBalance();
				} 
				catch(WATCardOffice::Lost &lost)
				{
					lostCard = true;
					printer->print(Printer::Student, Id, 'L');
					newWATCard = office->create(Id, 5);
				}
			}

			//Attempt to purchase soda
			purchaseStatus = tempVendingMachine->buy((VendingMachine::Flavours)favoriteFlavour, *newWATCard());		

			//If the WAT card has insufficient funds, call transfer funds
			if(purchaseStatus == VendingMachine::FUNDS)
			{
				//Try and catch the Lost exception during the transfer 
				try
				{
					newWATCard = office->transfer(Id, tempVendingMachine->cost() + 5, newWATCard());
				}
				//If the WATCard is lost during transfer, create a new one
				catch(WATCardOffice::Lost &lost)
				{

					printer->print(Printer::Student, Id, 'L');
					newWATCard = office->create(Id, 5);
				}	
			}
			//If the current vending machine is out of stock, go to the next machine
			if(purchaseStatus == VendingMachine::STOCK)
			{
				tempVendingMachine = server->getMachine(Id);
			}
		}
		printer->print(Printer::Student, Id, 'B', newWATCard()->getBalance());
		//If the soda is bought successfully, increment the counter
		currentNumPurchase++;
	}
	delete newWATCard;
	printer->print(Printer::Student, Id, 'F');
}

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases )
{
	Id = id;
	printer = &prt;
	server = &nameServer;
	office = &cardOffice;
	numPurchase = maxPurchases;
}
