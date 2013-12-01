#include <vector>
#include "Bank.h"
#include <iostream>

Bank::Bank( unsigned int numStudents ) : accounts(numStudents, 0) {}
 
void Bank::deposit( unsigned int id, unsigned int amount ) {
	accounts[id] += amount;
	// if funds are added to an accout, wake up couriers
	while (!insufficientFunds.empty()) {

		insufficientFunds.signal();
	}
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	// if insufficient funds, wait until funds are added
	while (accounts[id] < amount) {
		insufficientFunds.wait();
	}
	accounts[id] -= amount;
}
