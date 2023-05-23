#ifndef PURCHASE_HELP_H
#define PURCHASE_HELP_H
#define ESC "\033["
#define TXT_COLOUR "0;32m"
#define RESET "\033[0m"

#include "CoinRegister.h"
#include "StripString.h"
#include <iostream>
// \033[1;31;40m Red text \033[0m
class PurchaseHelp
{
private:
    /* data */
public:
    // Prints information about the selected item
    static void printInfo(std::string name, std::string desc, Price price);

    // Prints how much money the user still has to pay
    static void requestRemainingPrint(int remaining, bool enhance);

    // Checks if money input is valid
    static bool validateInputMoney(std::string input);
    
};


#endif // PURCHASE_HELP_H
