#ifndef __BANK_H__
#define __BANK_H__

#include <vector>

_Monitor Bank {
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
  private:
  	std::vector<unsigned int> accounts;
};

#endif
