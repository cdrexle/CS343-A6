#include "Parent.h"
#include "Printer.h"
#include "Bank.h"
#include "MPRNG.h"

extern MPRNG mprng;

void Parent::main()
{
	while(true) {
		_Accept(~Parent) {
			break;
		}
		_Else {
			//Determines how much money to give within [1,3]
			unsigned int amount = mprng(2) + 1;
			//Determines which student to give it to: [0, numStudents - 1]
			unsigned int student = mprng(numStudents - 1);
			yield(parentalDelay);
			bank->deposit(student, amount);
		}
	}
}

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
	prt(&prt),
	bank(&bank),
	numStudents(numStudents),
	parentalDelay(parentalDelay)
{}
