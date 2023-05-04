#ifndef PURCHASE_HELP_H
#define PURCHASE_HELP_H

#include "CoinRegister.h"
#include <iostream>

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
