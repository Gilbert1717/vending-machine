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
    delete this->stocklist;
    this->stocklist = nullptr;
    delete this->coinRegister;
    this->coinRegister = nullptr;
}

void Purchase::purchaseMenu(bool enhance) {
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;

    // Gets user input
    cout << "Please enter the id of the item you wish to purchase: ";
    string inputId;
    std::getline(std::cin, inputId);
    StripString::stripString(&inputId);

    if (!std::cin.eof() && inputId != "") {
        if (verifyID(inputId)) {
            if (this->stocklist->searchByID(inputId)->data->on_hand != 0) {
                startPurchase(inputId, enhance);

            } 
            else {
                cout << "Sorry, we are out of stock on that item" << endl;
            }
        }
        else {
            cout << "Invalid ID" << endl;

        } 
        
    }
    else {
        cout << "Purchase was cancelled" << endl;

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

void Purchase::startPurchase(string id, bool enhance) {
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

        PurchaseHelp::requestRemainingPrint(remaining, enhance);
        std::getline(std::cin, input);
        StripString::stripString(&input);

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
            // Creating a copy of coin register to use while calculating change
            CoinRegister copyCoins = *(this->coinRegister);
            CoinRegister* copyCoinsPointer = &copyCoins;
            // Add the inputed coins into the copy coin register
            modifyCoinsToRegister(inputCoins, copyCoinsPointer);

            std::vector<int> changeCoins = 
                calculateChange(difference, inputCoins, copyCoins);
            
            // Checks if change is possible
            if (changeCoins.size() != 0) {
                // Adding input coins to coin register
                modifyCoinsToRegister(inputCoins, this->coinRegister);
                // Removing change from coin register
                modifyCoinsToRegister(changeCoins, this->coinRegister, true);

                // Printing the change and coins given
                cout << "Here is your " << name 
                    << " and your change of $" 
                    << (double)difference / CENT_DOLLAR_CONVERSION << ":";
                    
                for (int i: changeCoins) {
                    if (i >= ONE_DOLLAR_VALUE) {
                        cout << " $" << i / CENT_DOLLAR_CONVERSION;
                    }
                    else {
                        cout << " " << i << "c";
                    }
                                        
                }
                cout << endl;

                // Subtract stock count by 1
                this->stocklist->searchByID(id)->data->on_hand--;
            }
            else {
                cout << "Purchase canceled because not enough coins for change"
                    << endl;
            }
        }
        else {
            cout << "Here is your " << name << endl;
            
            // Subtract stock count by 1
            this->stocklist->searchByID(id)->data->on_hand--;
            
            modifyCoinsToRegister(inputCoins, this->coinRegister);

        }

    }
    else {
        cout << "Purchase was canceled" << endl;

    }

}

std::vector<int> Purchase::calculateChange(int change, 
                                           std::vector<int> inputCoins,
                                           CoinRegister copyCoins) {
    
    // vector to store all the change coins
    std::vector<int> changeCoins = std::vector<int>();

    bool isPossible = true;
    int nextVal;
    // prevNum gets a value greater than the highest coin denomination
    int prevNum = TEN_DOLLAR_VALUE + 1;
    
    
    bool running = true;
    while(running) {
        nextVal = nextChange(change, copyCoins, prevNum);

        if (nextVal != -1) {
            // Checks if it is possible to get change starting with nextVal
            isPossible = checkIfPossible(change - nextVal, copyCoins);

            if (isPossible) {
                changeCoins.push_back(nextVal);
                change -= nextVal;
                prevNum = TEN_DOLLAR_VALUE + 1;
                modifyCoinsToRegister(std::vector<int>({nextVal}),
                                      &copyCoins, true);
                
                // Checks if we gave enough change
                if (change == 0) {
                    running = false;

                }
            }
            // If not possible, check the next possible value
            else {
                prevNum = nextVal;
                
            }

        }
        // There is not enough coins for change
        else {
            running = false;
            changeCoins = std::vector<int>();

        }

        
    }

    return changeCoins;
}

void Purchase::modifyCoinsToRegister(std::vector<int> inputCoins,
                                     CoinRegister* cr,
                                     bool subtractMode) {
    int incrementVal = 1;
    if (subtractMode) {
        incrementVal = -1;

    }

    for (int i: inputCoins) {
        if (i == FIVE_CENTS_VALUE) {
            cr->coins[FIVE_CENTS].count += incrementVal;
        }
        else if (i == TEN_CENTS_VALUE) {
            cr->coins[TEN_CENTS].count += incrementVal;
        }
        else if (i == TWENTY_CENTS_VALUE) {
            cr->coins[TWENTY_CENTS].count += incrementVal;
        }
        else if (i == FIFTY_CENTS_VALUE) {
            cr->coins[FIFTY_CENTS].count += incrementVal;
        }
        else if (i == ONE_DOLLAR_VALUE) {
            cr->coins[ONE_DOLLAR].count += incrementVal;
        }
        else if (i == TWO_DOLLAR_VALUE) {
            cr->coins[TWO_DOLLARS].count += incrementVal;
        }
        else if (i == FIVE_DOLLAR_VALUE) {
            cr->coins[FIVE_DOLLARS].count += incrementVal;
        }
        else if (i == TEN_DOLLAR_VALUE) {
            cr->coins[TEN_DOLLARS].count += incrementVal;
        }

    }

}

bool Purchase::checkIfPossible(int change, CoinRegister copyCoins) {
    bool retVal;
    int nextCoin;
    CoinRegister tmpCopyCoins;
    int prevNum = TEN_DOLLAR_VALUE + 1;
    // Base case - if we have enough change
    if (change == 0) {
        retVal = true;
    }
    else {
        bool running = true;
        while (running) {
            nextCoin = nextChange(change, copyCoins, prevNum);
            
            // if no values are possible
            if (nextCoin == -1) {
                retVal = false;
                running = false;
            }
            else{
                // creates another copy coin register subtract nextCoin from it 
                tmpCopyCoins = copyCoins;
                modifyCoinsToRegister(std::vector<int>({nextCoin}),
                                      &tmpCopyCoins, true);

                // Recursive call with lower change
                retVal = checkIfPossible(change - nextCoin, tmpCopyCoins);
                
                if (retVal) {
                    running = false;

                }
                // Check next possible value
                else {
                    prevNum = nextCoin;
                    
                }
            }
        }
    }

    return retVal;
}

int Purchase::nextChange(int change, CoinRegister copyCoins, int prevNum) {
    int nextCoin;
    if (TEN_DOLLAR_VALUE <= change && 
        copyCoins.coins[TEN_DOLLARS].count >= 1 && 
        prevNum > TEN_DOLLAR_VALUE) {

        nextCoin = TEN_DOLLAR_VALUE;
    }
    else if (FIVE_DOLLAR_VALUE <= change && 
             copyCoins.coins[FIVE_DOLLARS].count >= 1 && 
             prevNum > FIVE_DOLLAR_VALUE) {

        nextCoin = FIVE_DOLLAR_VALUE;
    }
    else if (TWO_DOLLAR_VALUE <= change && 
             copyCoins.coins[TWO_DOLLARS].count >= 1 && 
             prevNum > TWO_DOLLAR_VALUE) {

        nextCoin = TWO_DOLLAR_VALUE;
    }
    else if (ONE_DOLLAR_VALUE <= change && 
             copyCoins.coins[ONE_DOLLAR].count >= 1 && 
             prevNum > ONE_DOLLAR_VALUE) {

        nextCoin = ONE_DOLLAR_VALUE;
    }
    else if (FIFTY_CENTS_VALUE <= change && 
             copyCoins.coins[FIFTY_CENTS].count >= 1 && 
             prevNum > FIFTY_CENTS_VALUE) {

        nextCoin = FIFTY_CENTS_VALUE;
    }
    else if (TWENTY_CENTS_VALUE <= change && 
             copyCoins.coins[TWENTY_CENTS].count >= 1 && 
             prevNum > TWENTY_CENTS_VALUE) {
        nextCoin = TWENTY_CENTS_VALUE;
    }
    else if (TEN_CENTS_VALUE <= change && 
             copyCoins.coins[TEN_CENTS].count >= 1 && 
             prevNum > TEN_CENTS_VALUE) {

        nextCoin = TEN_CENTS_VALUE;
    }
    else if (FIVE_CENTS_VALUE <= change && 
             copyCoins.coins[FIVE_CENTS].count >= 1 && 
             prevNum > FIVE_CENTS_VALUE) {
                
        nextCoin = FIVE_CENTS_VALUE;
    }
    else {
        nextCoin = -1;
    }

    return nextCoin;

}
