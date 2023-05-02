#ifndef PURCHASE_HELP_H
#define PURCHASE_HELP_H

#include "CoinRegister.h"
#include <iostream>

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


class PurchaseHelp
{
private:
    /* data */
public:
    // Prints information about the selected item
    static void printInfo(std::string name, std::string desc, Price price);

    // Prints how much money the user still has to pay
    static void requestRemainingPrint(int remaining);

    // Checks if money input is valid
    static bool validateInputMoney(std::string input);
    
};


#endif // PURCHASE_HELP_H
