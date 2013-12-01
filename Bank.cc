#include <vector>
#include "Bank.h"
#include <iostream>

Bank::Bank( unsigned int numStudents ) : accounts(numStudents, 0) {}
 
void Bank::deposit( unsigned int id, unsigned int amount ) {
	accounts[id] += amount;
	// for(int i = 0; i < accounts.size(); i++)
	// {
	// 	std::cout<<"id: "<<i<<"amount "<<accounts[i]<<std::endl;
	// }
	while (!insufficientFunds.empty()) {

		insufficientFunds.signal();
	}
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while (accounts[id] < amount) {
		//std::cout<<"forced to wait "<<id<<" amount "<<amount<<std::endl;
		insufficientFunds.wait();
	}
	accounts[id] -= amount;
}
