#ifndef PURCHASE_H
#define PURCHASE_H

#include "LinkedList.h"
#include "CoinRegister.h"
#include "PurchaseHelp.h"
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

    // Promts user to pay for their item and updates system accordingly
    void startPurchase(std::string id, bool enhance);

    // Calculate which coins and how many of each need to be returned as change
    std::vector<int> calculateChange(int change,
                                     std::vector<int> inputCoins,
                                     CoinRegister copyCoins);

    /**
     * Adds/Subtracts coins to register
     * 
     * @param inputCoins List of coins to add/subract
     * @param cr Pointer to coin register to modify
     * @param subtractMode chooses if we add or subract coins. Defult value is false    *
     */
    void modifyCoinsToRegister(std::vector<int> inputCoins,
                               CoinRegister* cr,
                               bool subtractMode = false);

    // Recursive function to check if it is possible to get change for current required change amount
    bool checkIfPossible(int change, CoinRegister copyCoins);

    // Gets next possible value to try for change
    int nextChange(int change, CoinRegister copyCoins, int prevNum);

   

public:
    Purchase();
    ~Purchase();

    // Overloaded constructor
    Purchase(LinkedList* stocklist, CoinRegister* coinRegister);  

    // Shows the purchase menu and accepts user inputs
    void purchaseMenu(bool enhance);
    LinkedList* stocklist;
    CoinRegister* coinRegister;

};


#endif  // PURCHASE_H
