#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

_Monitor Printer;
_Monitor Bank;
#include "WATCard.h"
#include <vector>

_Task WATCardOffice {
	struct Args {
        int studentId;
        int addAmount;
        WATCard* watcard;
    };
    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };
    Printer *printer;
    Bank *bankPtr;
    int courierNum;                     //Total number of couriers
    _Task Courier {
            void main();
        public:
            Courier();

    };                 // communicates with bank
    std::vector <Courier *> courierList;    //List of couriers
    std::vector <Job *> jobList;            //List of available jobs for couriers
    uCondition jobQueue;
    void main();
  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();

    //TODO: This is needed in order to compile, is this correct?
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
