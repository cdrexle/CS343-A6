#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

_Monitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
    void main();
  public:
    enum Flavours { PERFECTION, GOOD, BAD, GARBAGE };                 // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
  private:
  	unsigned int* stock;
  	Printer* prt;
  	NameServer* nameServer;
  	unsigned int id;
  	unsigned int sodaCost;
  	unsigned int maxStockPerFlavour;
  	bool beingStocked;
};

#endif
