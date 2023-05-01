#ifndef PURCHASE_H
#define PURCHASE_H

#include "LinkedList.h"
#include "CoinRegister.h"
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

    
    void startPurchase(std::string id);


    void printInfo(std::string name, std::string desc, Price price);


    void requestRemainingPrint(Price price);


    //std::vector<Coin> createEmptyCoinList();


    std::vector<int> calculateChange(int change);

    LinkedList* stocklist;
    CoinRegister* coinRegister;

public:
    Purchase();
    ~Purchase();

    // Overloaded constructor
    Purchase(LinkedList* stocklist, CoinRegister* coinRegister);  

    // Shows the purchase menu and accepts user inputs
    void purchaseMenu();

};


#endif  // PURCHASE_H