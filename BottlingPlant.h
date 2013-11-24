#ifndef BOTTLINGPLANT_H
#define BOTTLINGPLANT_H

_Task BottlingPlant {
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif