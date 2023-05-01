#ifndef PURCHASE_H
#define PURCHASE_H

#include "LinkedList.h"
#include "CoinRegister.h"
#include <iostream>
#include <vector>

//defines
#define FIVE_CENTS_VALUE 5
#define TEN_CENTS_VALUE 10
#define TWENTY_CENTS_VALUE 20
#define FIFTY_CENTS_VALUE 50
#define ONE_DOLLAR_VALUE 100
#define TWO_DOLLAR_VALUE 200
#define FIVE_DOLLAR_VALUE 500
#define TEN_DOLLAR_VALUE 1000

#define CENT_DOLLAR_CONVERSION 100
class Purchase
{
private:
    /**
     * Checks if user input ID is a valid ID
     * returns true if InputId is valid, false otherwise
    */
    bool verifyID(std:: string inputId);

    // Promts user to pay for their item and updates system accordingly
    void startPurchase(std::string id);

    // Prints information about the selected item
    void printInfo(std::string name, std::string desc, Price price);

    // Prints how much money the user still has to pay
    void requestRemainingPrint(Price price);


    //std::vector<Coin> createEmptyCoinList();

    /**
     * Calculate which coins and how many of each need to be returned as change
     * 
     * @param change Takes amount to be paid in cents as input
     * 
     * @return Returns a vector of all coins to be returned
     */
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