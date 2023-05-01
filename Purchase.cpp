#include "Purchase.h"

using std::cout;
using std::endl;
using std::string;

Purchase::Purchase() {
    this->stocklist = nullptr;
}

Purchase::Purchase(LinkedList* stocklist) {
    this->stocklist = stocklist;
}

Purchase::~Purchase() {
    //delete stocklist;
}

void Purchase::purchaseMenu() {
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;

    // Gets user input
    cout << "Please enter the id of the item you wish to purchase:";
    string inputId;
    std::getline(std::cin, inputId);

    if (verifyID(inputId)) {
        if (this->stocklist->searchByID(inputId)->data->on_hand == 0) {
            startPurchase(inputId);

        } 
        
    }
    else {
        cout << "invalid" << endl;

        } 
        
    }
    else {
        cout << "invalid" << endl;

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

void Purchase::printInfo(string name, string desc, Price price) {
    cout << "You have selected \"" << name << " - " << desc << "\". This will cost you $";
    price.display();
    cout << endl;

    cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
    cout << "Press enter or ctrl-d on a new line to cancel this purchase:" << endl;
    
}
