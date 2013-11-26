#include <vector>
#include "Bank.h"

Bank::Bank( unsigned int numStudents ) : accounts(numStudents, 0) {}
 
void Bank::deposit( unsigned int id, unsigned int amount ) {
	accounts[id] += amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	if (accounts[id] - amount <= 0) accounts[id] = 0;
	else accounts[id] -= amount;
}
