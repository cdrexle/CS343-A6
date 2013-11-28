#ifndef PARENT_H
#define PARENT_H

_Monitor Printer;
_Monitor Bank;

_Task Parent {
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
  private:
  	Printer* prt;
  	Bank* bank;
  	unsigned int numStudents;
  	unsigned int parentalDelay;
};

#endif
