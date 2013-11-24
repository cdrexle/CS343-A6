#include <vector>
#include "Bank.h"

Bank::Bank( unsigned int numStudents ) : accounts(numStudents, 0) {}
 
void deposit( unsigned int id, unsigned int amount ) {
	accounts[id] += amount;
}

void withdraw( unsigned int id, unsigned int amount ) {
	if (accounts[i] - amount <= 0) accounts[id] = 0;
	else accounts[id] -= amount;
}
