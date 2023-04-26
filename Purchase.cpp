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
    delete stocklist;
}

void Purchase::purchaseMenu() {
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;

    // Gets user input
    cout << "Please enter the id of the item you wish to purchase:";
    string inputId;
    std::getline(std::cin, inputId);

    if (verifyID(inputId)) {

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
        catch (std::invalid_argument* e) {
            isValid = false;
            
        }

    }

    return isValid;
}
