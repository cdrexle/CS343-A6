#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

_Monitor Printer;
_Monitor Bank;
#include "WATCard.h"
#include <vector>

_Task WATCardOffice {
    //---------------------------------------------------------------------------
    //Definition of Args
    //---------------------------------------------------------------------------
	struct Args {
        int studentId;                              //The ID of the student making the request
        int addAmount;                              //The amount of money to transfer
        bool closing;                               //Indicate whether this job is to terminate the Courier
        WATCard* watCard;                           //Pointer to the WAT card that will be delivered
    };
    //---------------------------------------------------------------------------
    //Definition of Job
    //---------------------------------------------------------------------------
    struct Job {                          
        Args args;                                  //Arguments fields for the job 
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };
    
    //---------------------------------------------------------------------------
    //Definition of Courier Task
    //---------------------------------------------------------------------------
    _Task Courier { 
            int id;                         //ID of Courier
            Bank *bankPtr;                  //Pointer to the bank
            WATCardOffice *officePtr;       //Pointer to the WATCardOffice
            Printer *printer;               //Pointer to printer
            void main();
        public:
            Courier(int id, WATCardOffice &watCardOffice, Bank &bank, Printer &printer);
            ~Courier();

    };              
    Printer *printer;
    Bank *bankPtr;
    int courierNum;                     //Total number of couriers
    int newJobSid;                      //The student ID for the newly created job
    int newJobAddAmount;                //The amount of money to transfer for the newly created job
    Job *newJob;                        //Pointer to a newly created job
    WATCard *newJobWATCard;             //Pointer to a newly created WAT Card
    uCondition noJobs;                  //uCondition when there are no jobs queued up
    bool closing;                       //Indicate that the office is closing
    std::vector <Courier *> courierList;    //List of couriers
    std::vector <Job *> jobList;            //List of available jobs for couriers
    void main();
  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );         
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
