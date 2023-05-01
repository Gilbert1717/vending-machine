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
        /** 
        * Searches stocklist for an item with inputId
        * If no item exists with this ID, then the method throws a std::invalid_argument exception
        */ 
        try {
            this->stocklist->searchByID(inputID);

        }
        // Catch std::invalid_argument exception
        catch (std::invalid_argument& e) {
            isValid = false;
            
        }

    }

    return isValid;
}

void Purchase::startPurchase(string id) {
    string name = this->stocklist->searchByID(id)->data->name;
    string desc = this->stocklist->searchByID(id)->data->description;
    Price price = this->stocklist->searchByID(id)->data->price;

    printInfo(name, desc, price);

    int dollars = price.dollars;
    int cents = price.cents;

    string input;
    int inputAmount;

    //std::vector<Coin> inputCoins = createEmptyCoinList();
    std::vector<int> inputCoins = std::vector<int>();

    bool cancel = false;
    bool paying = true;
    while (paying) {
        cout << "You still need to give us $" << dollars << "." << cents << ": ";
        std::getline(std::cin, input);

        // Checks if user cancels purcahse
        if (std::cin.eof() || input == "") {
            paying = false;
            cancel = true;
            
        }
        else{
            inputAmount = std::stoi(input);
            if (inputAmount == 1000 || inputAmount == 500 || inputAmount == 200
            || inputAmount == 100 || inputAmount == 50 || inputAmount == 20
            || inputAmount == 10 || inputAmount == 5) {

                inputCoins.push_back(inputAmount);

                if (inputAmount >= 100) {
                    dollars -= inputAmount / 100;
                }
                else {
                    cents -= inputAmount;
                }
            }
            else {
                cout.precision(2);
                cout << "Error: $" << std::fixed << (double)inputAmount / 100;
                cout << " is not a valid denomination of money. Please try again." << endl;
            }
        
            // Checks if enough money was paid
            if (dollars <= 0 && cents <= 0) {
                paying = false;
            }

        }

    }

    int sum = 0;
    int comparePrice = price.dollars * 100 + price.cents;
    int difference;
    if (!cancel) {
        // TODO - add values to coinRegister
        
        for (int i: inputCoins) {
            sum += i;
        }

        difference = sum - comparePrice;

        if (difference > 0) {
            std::vector<int> changeCoins = calculateChange(difference);

            cout << "Here is your " << name << " and your change of $ " << endl;
        }
        else {
            cout << "Here is your " << name << endl;
        }

    }
    
}

void Purchase::printInfo(string name, string desc, Price price) {
    cout << "You have selected \"" << name << " - " << desc << "\". This will cost you $";
    price.display();
    cout << endl;

    cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
    cout << "Press enter or ctrl-d on a new line to cancel this purchase:" << endl;
    
}

void Purchase::requestRemainingPrint(Price price) {
    cout << "You still need to give us $";
    price.display();
    cout << ": ";

}

std::vector<int> Purchase::calculateChange(int change) {
    // TODO
}

/*std::vector<Coin> Purchase::createEmptyCoinList() {
    std::vector<Coin> coins = std::vector<Coin>();

    coins.push_back(Coin(TEN_DOLLARS, 0));
    coins.push_back(Coin(FIVE_DOLLARS, 0));
    coins.push_back(Coin(TWO_DOLLARS, 0));
    coins.push_back(Coin(ONE_DOLLAR, 0));
    coins.push_back(Coin(FIFTY_CENTS, 0));
    coins.push_back(Coin(TWENTY_CENTS, 0));
    coins.push_back(Coin(TEN_CENTS, 0));
    coins.push_back(Coin(FIVE_CENTS, 0));

    return coins;
}*/
