#include "PurchaseHelp.h"

using std::cout;
using std::endl;
using std::string;


void PurchaseHelp::printInfo(string name, string desc, Price price) {
    cout << "You have selected \"" << name << " - " << desc 
        << "\". This will cost you ";
    price.display();
    cout << endl;

    cout << "Please hand over the money - ";
    cout << "type in the value of each note/coin in cents.\n";
    cout << "Press enter or ctrl-d on a new line to cancel this purchase:\n";
    
}


void PurchaseHelp::requestRemainingPrint(int remaining) {
    double printDollars = (double)remaining / CENT_DOLLAR_CONVERSION;

    cout << "You still need to give us $" << std::fixed
        << printDollars << ": ";

}


bool PurchaseHelp::validateInputMoney(std::string input) {
    bool isValid = true;

    int inputAmount;
    std::size_t numProcessed;
    try {
        inputAmount = std::stoi(input, &numProcessed);

        if (numProcessed == input.length()) {
        
            if (inputAmount != TEN_DOLLAR_VALUE && inputAmount != FIVE_DOLLAR_VALUE 
            && inputAmount != TWO_DOLLAR_VALUE && inputAmount != ONE_DOLLAR_VALUE 
            && inputAmount != FIFTY_CENTS_VALUE && inputAmount != TWENTY_CENTS_VALUE
            && inputAmount != TEN_CENTS_VALUE && inputAmount != FIVE_CENTS_VALUE) {
                
                cout << "Error: $" << std::fixed << 
                    (double)inputAmount / CENT_DOLLAR_CONVERSION;
                cout << 
                    " is not a valid denomination of money. Please try again."
                        << endl;
                isValid = false;

            }

        }
        else {
            isValid = false;
            cout << "Invalid, please enter price in cents ($1 = 100c)."
                << endl;

        }

    }
    catch (std::invalid_argument& e) {
        isValid = false;
        cout << "Invalid" << endl;

    }
    catch (std::out_of_range& e) {
        isValid = false;
        cout << "Invalid, entered amount too long." << endl;
        
    }
    
    return isValid;

}
