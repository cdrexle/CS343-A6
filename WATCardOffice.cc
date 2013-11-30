#include "WATCardOffice.h"
#include "Printer.h"
#include "Bank.h"
#include "WATCard.h"
#include "MPRNG.h"

extern MPRNG mprng;

void WATCardOffice::main()
{
	while(true)
	{
		_Accept(~WATCardOffice)
		{
		}
		_Accept(create)
		{
			//Create the Args object the specifies the details of the job
			Args newAgrs;
			newAgrs.studentId = newJobSid;
			newAgrs.addAmount = newJobAddAmount;
			newAgrs.watCard = new WATCard();
			//Create a new job
			newJob = new Job(newAgrs);

			//Insert the job into the list of jobs and signal a courier that is waiting for jobs
			jobList.push_back(newJob);
			jobQueue.signal();

		}
		_Accept(transfer)
		{
			//Create the Args object the specifies the details of the job
			Args newAgrs;
			newAgrs.studentId = newJobSid;
			newAgrs.addAmount = newJobAddAmount;
			newAgrs.watCard = newJobWATCard;

			//Create a new job
			Job *newJob = new Job(newAgrs);

			//Insert the job into the list of jobs and signal a courier that is waiting for jobs
			jobList.push_back(newJob);
			jobQueue.signal();
		}

		_Accept(requestWork)
		{
		}
	}
}
WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
{
	courierNum = numCouriers;
	printer = &prt;
	bankPtr = &bank;
	//Initialize couriers
	for(int i = 0; i < numCouriers; i++)
	{
		WATCardOffice::Courier *courier = new Courier(*this, bank);
		courierList.push_back(courier);
	}
}
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount )
{
	newJobSid = sid;
	newJobAddAmount = amount;
	//Return the future to the student, the actual arguments of newJob will be populated in main
	return newJob->result;
}
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
	newJobSid = sid;
	newJobAddAmount = amount;
	newJobWATCard = card;
	//Return the future to the student, the actual arguments of newJob will be populated in main
	return newJob->result;
}
WATCardOffice::Job* WATCardOffice::requestWork()
{
	//Courier blocks until a job is available
	while(jobList.size() == 0)
	{
		jobQueue.wait();
	}

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
}

WATCardOffice::Courier::Courier(WATCardOffice &watCardOffice, Bank &bank)
{
	bankPtr = &bank;
	officePtr = &watCardOffice;
}

void WATCardOffice::Courier::main()
{
	while(true)
	{
		_Accept(~Courier){}
		_Else
		{
			//Requests a new job
			Job *newJob = officePtr->requestWork();

			//Once a new job is received, call withdraw from the bank
			bankPtr -> withdraw(newJob->args.studentId, newJob->args.addAmount);

			//Update the watcard
			newJob->args.watCard->deposit(newJob->args.addAmount);

			//In case where courier loses the WATCard
			if(mprng()%6 == 0)
			{
				newJob->result.exception(new WATCardOffice::Lost);
			}
			//In case where the courier doesn't lose the WATCard
			else
			{
				newJob->result.delivery(newJob->args.watCard);
			}
		}
	}
} 
