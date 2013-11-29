#include "WATCardOffice.h"
#include "Printer.h"
#include "Bank.h"
#include "WATCard.h"

void WATCardOffice::main()
{

}
WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
{
	courierNum = numCouriers;
	printer = &prt;
	bankPtr = &bank;
	//Initialize couriers
	for(int i = 0; i < numCouriers; i++)
	{
		WATCardOffice::Courier *courier = new Courier();
		courierList.push_back(courier);
	}
}
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount )
{
	//Create the Args object the specifies the details of the job
	Args newAgrs;
	newAgrs.studentId = sid;
	newAgrs.originalAmount = 0;
	newAgrs.addAmount = amount;

	//Create a new future WAT card
	WATCard::FWATCard newCard;

	//Create a new job
	Job *newJob = new Job(newAgrs);
	newJob->result = newCard;

	//Insert the job into the list of jobs and signal a courier that is waiting for jobs
	jobList.push_back(newJob);
	jobQueue.signal();

	//Return the future to the student
	return newCard;
}
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
	//Create the Args object the specifies the details of the job
	Args newAgrs;
	newAgrs.studentId = sid;
	newAgrs.originalAmount = card->getBalance();
	newAgrs.addAmount = amount;

	//TODO: does this make sense???
	delete card;
	//Create a new future WAT card
	WATCard::FWATCard newCard;

	//Create a new job
	Job *newJob = new Job(newAgrs);
	newJob->result = newCard;

	//Insert the job into the list of jobs and signal a courier that is waiting for jobs
	jobList.push_back(newJob);
	jobQueue.signal();

	//Return the future to the student
	return newCard;
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

WATCardOffice::Courier::Courier()
{

}

void WATCardOffice::Courier::main()
{

} 