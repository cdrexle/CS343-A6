#ifndef STUDENT_H
#define STUDENT_H

_Monitor Printer;
_Task NameServer;
_Task WATCardOffice;

_Task Student {
    void main();
    unsigned int Id;				//Id the current student
    unsigned int numPurchase;		//The max number of purchases the student can make
    Printer *printer;				//Pointer to the printer
    NameServer *server;				//Pointer to the NameServer
    WATCardOffice *office;			//Pointer to WATCardOffice
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases );
};

#endif
