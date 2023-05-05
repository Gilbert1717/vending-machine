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
            CoinRegister copyCoins = *(this->coinRegister);
            CoinRegister* copyCoinsPointer = &copyCoins;
            modifyCoinsToRegister(inputCoins, copyCoinsPointer);

            std::vector<int> changeCoins = calculateChange(difference, inputCoins, copyCoins);

            if (changeCoins.size() != 0) {
                modifyCoinsToRegister(inputCoins, this->coinRegister);
                modifyCoinsToRegister(changeCoins, this->coinRegister, true);

                for (int i: changeCoins) {
                    cout << i << endl;
                    
                }

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
            
            modifyCoinsToRegister(inputCoins, this->coinRegister);

        }

    }
    else {
        cout << "Purchase was canceled" << endl;

    }

}

std::vector<int> Purchase::calculateChange(int change, std::vector<int> inputCoins, CoinRegister copyCoins) {
    

    std::vector<int> changeCoins = std::vector<int>();
    bool isPossible = true;
    int nextVal;
    int prevNum = -1;
    
    
    bool running = true;
    while(running) {
        nextVal = nextChange(change, copyCoins, prevNum);

        if (nextVal != -1) {
            isPossible = checkIfPossible(nextVal, change, copyCoins);

            if (isPossible) {
                changeCoins.push_back(nextVal);
                change -= nextVal;
                prevNum = -1;

                if (change == 0) {
                    running = false;

                }
            }
            else {
                prevNum = nextVal;
            }

        }
        else {
            running = false;
            changeCoins = std::vector<int>();

        }

        /*if (TEN_DOLLAR_VALUE <= change && copyCoinsPointer->coins[7].count >= 1) {
            changeCoins.push_back(TEN_DOLLAR_VALUE);
            change -= TEN_DOLLAR_VALUE;
        }
        else if (FIVE_DOLLAR_VALUE <= change && copyCoinsPointer->coins[6].count >= 1) {
            changeCoins.push_back(FIVE_DOLLAR_VALUE);
            change -= FIVE_DOLLAR_VALUE;
        }
        else if (TWO_DOLLAR_VALUE <= change && copyCoinsPointer->coins[5].count >= 1) {
            changeCoins.push_back(TWO_DOLLAR_VALUE);
            change -= TWO_DOLLAR_VALUE;
        }
        else if (ONE_DOLLAR_VALUE <= change && copyCoinsPointer->coins[4].count >= 1) {
            changeCoins.push_back(ONE_DOLLAR_VALUE);
            change -= ONE_DOLLAR_VALUE;
        }
        else if (FIFTY_CENTS_VALUE <= change && copyCoinsPointer->coins[3].count >= 1) {
            changeCoins.push_back(FIFTY_CENTS_VALUE);
            change -= FIFTY_CENTS_VALUE;
        }
        else if (TWENTY_CENTS_VALUE <= change && copyCoinsPointer->coins[2].count >= 1) {
            changeCoins.push_back(TWENTY_CENTS_VALUE);
            change -= TWENTY_CENTS_VALUE;
        }
        else if (TEN_CENTS_VALUE <= change && copyCoinsPointer->coins[1].count >= 1) {
            changeCoins.push_back(TEN_CENTS_VALUE);
            change -= TEN_CENTS_VALUE;
        }
        else if (FIVE_CENTS_VALUE <= change && copyCoinsPointer->coins[0].count >= 1) {
            changeCoins.push_back(FIVE_CENTS_VALUE);
            change -= FIVE_CENTS_VALUE;
        }*/


    }
    


    return changeCoins;
}

void Purchase::modifyCoinsToRegister(std::vector<int> inputCoins, CoinRegister* cr, bool subtractMode) {
    int incrementVal = 1;
    if (subtractMode) {
        incrementVal = -1;

    }

    for (int i: inputCoins) {
        if (i == FIVE_CENTS_VALUE) {
            cr->coins[0].count += incrementVal;
        }
        else if (i == TEN_CENTS_VALUE) {
            cr->coins[1].count += incrementVal;
        }
        else if (i == TWENTY_CENTS_VALUE) {
            cr->coins[2].count += incrementVal;
        }
        else if (i == FIFTY_CENTS_VALUE) {
            cr->coins[3].count += incrementVal;
        }
        else if (i == ONE_DOLLAR_VALUE) {
            cr->coins[4].count += incrementVal;
        }
        else if (i == TWO_DOLLAR_VALUE) {
            cr->coins[5].count += incrementVal;
        }
        else if (i == FIVE_DOLLAR_VALUE) {
            cr->coins[6].count += incrementVal;
        }
        else if (i == TEN_DOLLAR_VALUE) {
            cr->coins[7].count += incrementVal;
        }

    }

}

bool Purchase::checkIfPossible(int num, int change, CoinRegister copyCoins) {
    bool retVal;
    int nextCoin;
    int prevNum = -1;
    if (change == 0) {
        retVal = true;
    }
    else {
        bool running = true;
        while (running) {
            nextCoin = nextChange(change, copyCoins, prevNum);
            
            if (nextCoin == -1) {
                retVal = false;
                running = false;
            }
            else{
                retVal = checkIfPossible(nextCoin, change - nextCoin, copyCoins);

                if (retVal) {
                    running = false;
                }
                else {
                    prevNum = nextCoin;
                }
            }
        }
    }

    return retVal;
}

int Purchase::nextChange(int change, CoinRegister copyCoins, int prevNum) {
    int nextCoin = 0;
    if (TEN_DOLLAR_VALUE <= change && copyCoins.coins[7].count >= 1 && prevNum == -1) {
        nextCoin = TEN_DOLLAR_VALUE;
    }
    else if (FIVE_DOLLAR_VALUE <= change && copyCoins.coins[6].count >= 1 && prevNum > FIVE_DOLLAR_VALUE) {
        nextCoin = FIVE_DOLLAR_VALUE;
    }
    else if (TWO_DOLLAR_VALUE <= change && copyCoins.coins[5].count >= 1 && prevNum > TWO_DOLLAR_VALUE) {
        nextCoin = TWO_DOLLAR_VALUE;
    }
    else if (ONE_DOLLAR_VALUE <= change && copyCoins.coins[4].count >= 1 && prevNum > ONE_DOLLAR_VALUE) {
        nextCoin = ONE_DOLLAR_VALUE;
    }
    else if (FIFTY_CENTS_VALUE <= change && copyCoins.coins[3].count >= 1 && prevNum > FIFTY_CENTS_VALUE) {
        nextCoin = FIFTY_CENTS_VALUE;
    }
    else if (TWENTY_CENTS_VALUE <= change && copyCoins.coins[2].count >= 1 && prevNum > TWENTY_CENTS_VALUE) {
        nextCoin = TWENTY_CENTS_VALUE;
    }
    else if (TEN_CENTS_VALUE <= change && copyCoins.coins[1].count >= 1 && prevNum > TEN_CENTS_VALUE) {
        nextCoin = TEN_CENTS_VALUE;
    }
    else if (FIVE_CENTS_VALUE <= change && copyCoins.coins[0].count >= 1 && prevNum > FIVE_CENTS_VALUE) {
        nextCoin = FIVE_CENTS_VALUE;
    }
    else if (prevNum == FIVE_CENTS_VALUE) {
        nextCoin = -1;
    }

    return nextCoin;

}
