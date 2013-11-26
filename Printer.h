#ifndef PRINTER_H
#define PRINTER_H

#include <vector>
#include <string>

_Monitor Printer {
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
  private:
  	std::vector<std::string> buffer;
  	unsigned int nStudents;
  	unsigned int nVendingMachines;
  	unsigned int nCouriers;
  	
  	void printPrimitive(unsigned int id, std::string val);
    
    void flushBuffer();
    unsigned int getId(Kind kind);
    unsigned int getId(Kind kind, unsigned int id);
};

#endif
