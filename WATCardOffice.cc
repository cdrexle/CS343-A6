#include "WATCardOffice.h"
#include "Printer.h"
#include "Bank.h"
#include "WATCard.h"
#include "MPRNG.h"
#include <iostream>

extern MPRNG mprng;

void WATCardOffice::main()
{
	printer->print(Printer::WATCardOffice, 'S');
	//Initialize couriers
	for(int i = 0; i < courierNum; i++)
	{
		WATCardOffice::Courier *courier = new Courier(i, *this, *bankPtr, *printer);
		courierList.push_back(courier);
	}
	while(true)
	{
		_Accept(~WATCardOffice)
		{
			closing = true;
			while(!noJobs.empty())
			{
				noJobs.signalBlock();
			}
			break;
		}
		or _Accept(create)
		{
			//Fill in the Job's args fields
			newJob->args.studentId = newJobSid;
			newJob->args.addAmount = newJobAddAmount;
			newJob->args.watCard = new WATCard();
			newJob->args.closing = false;
			//Insert the job into the list of jobs and signal a courier that is waiting for jobs
			jobList.push_back(newJob);
			noJobs.signalBlock();

		}
		or _Accept(transfer)
		{
			//Fill in the Job's args fields
			newJob->args.studentId = newJobSid;
			newJob->args.addAmount = newJobAddAmount;
			newJob->args.watCard = newJobWATCard;
			newJob->args.closing = false;
			//Insert the job into the list of jobs and signal a courier that is waiting for jobs
			jobList.push_back(newJob);
			noJobs.signalBlock();
		}

		or _Accept(requestWork)
		{
		}
	}
	printer->print(Printer::WATCardOffice, 'F');
}
WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
{
	closing = false;
	courierNum = numCouriers;
	printer = &prt;
	bankPtr = &bank;
}
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount )
{
	printer->print(Printer::WATCardOffice, 'C', sid, amount);
	//Create a new args, information to be filled in later on
	Args newAgrs;
	//Create a new job
	newJob = new Job(newAgrs);

	//Populate the server's private variables to fill in the args fields later on
	newJobSid = sid;
	newJobAddAmount = amount;

	//Return the future to the student, the actual arguments of newJob will be populated in main
	return newJob->result;
}
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
	printer->print(Printer::WATCardOffice, 'T', sid, amount);
	//Create a new args, information to be filled in later on
	Args newAgrs;
	//Create a new job
	newJob = new Job(newAgrs);

	//Populate the server's private variables to fill in the args fields later on
	newJobSid = sid;
	newJobAddAmount = amount;
	newJobWATCard = card;

	//Return the future to the student, the actual arguments of newJob will be populated in main
	return newJob->result;
}
WATCardOffice::Job* WATCardOffice::requestWork()
{
	//If there are no jobs in queue and the office has not closed, then the courier must wait
	if(jobList.size() == 0 && !closing)
	{
		noJobs.wait();
	}

	//If the office has closed, any courier requesting jobs will receive a special job that
	//signals the office is closed
	if(closing)
	{
		Args args;
		args.closing = true;
		Job *terminateJob = new Job(args);
		return terminateJob;
	}
	printer->print(Printer::WATCardOffice, 'W');
	//Return the first job from the queue and erase it from the job list
	Job *firstJob = jobList[0];
	jobList.erase(jobList.begin());
	return firstJob;
}

WATCardOffice::~WATCardOffice()
{
	for(unsigned int i = 0; i < courierList.size(); i++)
	{				
		WATCardOffice::Courier *temp = courierList[i];
		delete temp;
	}
	for(unsigned int i = 0; i < jobList.size(); i++)
	{
		Job *temp = jobList[i];
		delete temp;
	}
}

WATCardOffice::Courier::Courier(int id, WATCardOffice &watCardOffice, Bank &bank , Printer &printer) : id(id), printer(&printer)
{
	bankPtr = &bank;
	officePtr = &watCardOffice;
}

WATCardOffice::Courier::~Courier()
{
}

void WATCardOffice::Courier::main()
{
	printer -> print(Printer::Courier, id, 'S');
	while(true)
	{
		//Requests a new job
		Job *newJob = officePtr->requestWork();
		if(newJob->args.closing)
		{
			delete newJob;
			break;
		}
		printer->print(Printer::Courier, id, 't', newJob->args.studentId, newJob->args.addAmount);

		//Once a new job is received, call withdraw from the bank
		bankPtr -> withdraw(newJob->args.studentId, newJob->args.addAmount);

		//Update the watcard
		newJob->args.watCard->deposit(newJob->args.addAmount);

		//In case where courier loses the WATCard
		if(mprng()%6 == 0)
		{
			
			newJob->result.exception(new WATCardOffice::Lost);
			delete newJob->args.watCard;
		}
		//In case where the courier doesn't lose the WATCard
		else
		{
			newJob->result.delivery(newJob->args.watCard);
		}
		printer->print(Printer::Courier, id, 'T', newJob->args.studentId, newJob->args.addAmount);
		delete newJob;
	}

	printer->print(Printer::Courier, id, 'F');
} 
