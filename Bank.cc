#include <vector>
#include "Bank.h"

Bank::Bank( unsigned int numStudents ) : accounts(numStudents, 0) {}
 
void Bank::deposit( unsigned int id, unsigned int amount ) {
	accounts[id] += amount;
	while (!insufficientFunds.empty()) insufficientFunds.signal();
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while (accounts[id] < amount) insufficientFunds.wait();
	accounts[id] -= amount;
}
