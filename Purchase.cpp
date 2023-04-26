#include "Purchase.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

Purchase::Purchase() {

}

Purchase::~Purchase() {

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
    
}

bool Purchase::verifyID(string inputID) {

}
