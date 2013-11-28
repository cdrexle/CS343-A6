#include "WATCard.h"

WATCard::WATCard( const WATCard & )
{
	//TODO: FIgure out if we need to do anything here
}
          
WATCard& WATCard::operator=( const WATCard & )
{
	//TODO: FIgure out if we need to do anything here
}

WATCard::WATCard() : balance(0) {}
    
void WATCard::deposit( unsigned int amount )
{
	balance += amount;
}

void WATCard::withdraw( unsigned int amount )
{
	if (balance < amount) return; //Cannot withdraw since not enough funds, should've checked first
	balance -= amount;
}

unsigned int WATCard::getBalance()
{
	return balance;
}
