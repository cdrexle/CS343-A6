#ifndef STUDENT_H
#define STUDENT_H

_Monitor Printer;
_Task NameServer;
_Task WATCardOffice;

#include "VendingMachine.h"
#include "MPRNG.h"

_Task Student {
    void main();
    unsigned int Id;
    unsigned int numPurchase;
    Printer *printer;
    NameServer *server;
    WATCardOffice *office;
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases );
};

#endif
