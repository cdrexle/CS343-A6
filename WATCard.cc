#include "WATCard.h"

WATCard::WATCard( const WATCard & )
{
	
}
          
WATCard& WATCard::operator=( const WATCard & )
{
	
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
