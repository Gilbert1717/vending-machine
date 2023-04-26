#ifndef PURCHASE_H
#define PURCHASE_H

#include "LinkedList.h"
#include <iostream>
#include <vector>

class Purchase
{
private:
    /**
     * Checks if user input ID is a valid ID
     * returns true if InputId is valid, false otherwise
    */
    bool verifyID(std:: string inputId);

    LinkedList* stocklist;

public:
    Purchase();
    ~Purchase();

    Purchase(LinkedList* stocklist); // Overloaded constructor

    // Shows the purchase menu and accepts user inputs
    void purchaseMenu();

};


#endif  // PURCHASE_H