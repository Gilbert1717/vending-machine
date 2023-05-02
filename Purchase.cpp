#include "Purchase.h"

using std::cout;
using std::endl;
using std::string;

Purchase::Purchase() {
    this->stocklist = nullptr;
    this->coinRegister = nullptr;
}

Purchase::Purchase(LinkedList* stocklist, CoinRegister* coinRegister) {
    this->stocklist = stocklist;
    this->coinRegister = coinRegister;
}

Purchase::~Purchase() {
    //delete stocklist;
}

void Purchase::purchaseMenu() {
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;

    // Gets user input
    cout << "Please enter the id of the item you wish to purchase: ";
    string inputId;
    std::getline(std::cin, inputId);

    if (!std::cin.eof()) {
        if (verifyID(inputId)) {
            if (this->stocklist->searchByID(inputId)->data->on_hand != 0) {
                startPurchase(inputId);

            } 
            else {
                cout << "Sorry, we are out of stock on that item" << endl;
            }
        }
        else {
            cout << "invalid" << endl;

        } 
        
    }
}

bool Purchase::verifyID(string inputID) {
    bool isValid = true;
    
    if (inputID.length() != 5 || inputID[0] != 'I') {
        isValid = false;
    }
    // Checks if an item with inputId exists in stocklist
    else {
        
        if (this->stocklist->searchByID(inputID) == nullptr) {
            isValid = false;

        }

    }

    return isValid;

}

void Purchase::startPurchase(string id) {
    // Gets data of item to be purchased
    string name = this->stocklist->searchByID(id)->data->name;
    string desc = this->stocklist->searchByID(id)->data->description;
    Price price = this->stocklist->searchByID(id)->data->price;

    PurchaseHelp::printInfo(name, desc, price);
    
    // Sets number of decimal values in output to 2  
    cout.precision(2);

    int remaining = price.dollars * CENT_DOLLAR_CONVERSION + price.cents;
    
    
    string input;
    int inputAmount;

    //std::vector<Coin> inputCoins = createEmptyCoinList();
    std::vector<int> inputCoins = std::vector<int>();

    bool cancel = false;
    bool paying = true;
    while (paying) {

        PurchaseHelp::requestRemainingPrint(remaining);
        std::getline(std::cin, input);

        // Checks if user cancels purcahse
        if (std::cin.eof() || input == "") {
            paying = false;
            cancel = true;
            
        }
        else{
            if (PurchaseHelp::validateInputMoney(input)) {
                inputAmount = std::stoi(input);

                inputCoins.push_back(inputAmount);

                remaining -= inputAmount;
            }
            
        
            // Checks if enough money was paid
            if (remaining <= 0) {
                paying = false;
            }

        }

    }

    int sum = 0;
    int comparePrice = price.dollars * CENT_DOLLAR_CONVERSION + price.cents;
    int difference;

    // Checks if purchase was canceled
    if (!cancel) {
        // TODO - add values to coinRegister
        
        // Gets sum of all inputed coins
        for (int i: inputCoins) {
            sum += i;
        }

        // Gets difference of item price from inputed amount
        difference = sum - comparePrice;

        /**
         * If difference > 0, then we need to pay change to the user
         * If difference <= 0, then no need to pay any change
         */
        if (difference > 0) {
            std::vector<int> changeCoins = calculateChange(difference);

            if (changeCoins.size() != 0) {
                cout << "Here is your " << name << " and your change of $ " << endl;

                // Subtract stock count by 1
                this->stocklist->searchByID(id)->data->on_hand--;
            }
            else {
                cout << "Purchase canceled because not enough coins for change." << endl;
            }
        }
        else {
            cout << "Here is your " << name << endl;
            
            // Subtract stock count by 1
            this->stocklist->searchByID(id)->data->on_hand--;
        }

    }
    else {
        cout << "Purchase was canceled" << endl;

    }

}

std::vector<int> Purchase::calculateChange(int change) {
    // TODO
    return std::vector<int>();
}
