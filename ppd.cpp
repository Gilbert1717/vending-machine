#include <iostream>
#include "LinkedList.h"
#include "LoadFiles.h"
#include "Purchase.h"
#include "CoinRegister.h"
#include "AddItem.h"
#include <sys/stat.h>
// Strip string code borrowed from Vidyut's assignment 1 code
#include "StripString.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Option definitions to avoid magic numbers
#define DISPLAY_ITEMS_OPTION "1"
#define PURCHASE_ITEMS_OPTION "2"
#define SAVE_EXIT_OPTION "3"
#define ADD_ITEM_OPTION "4"
#define REMOVE_ITEM_OPTION "5"
#define DISPLAY_COINS_OPTION "6"
#define RESET_STOCK_OPTION "7"
#define RESET_COINS_OPTION "8"
#define ABORT_PROGRAM_OPTION "9"
#define ENHANCEFLAG "-e"


// Funcution declarations
void printMenu();
void removeItem(LinkedList* stockList);
bool pathValidation(int argc, const char* argv1, const char* argv2);
void executingMenu(Purchase* purchase, bool enhance);

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{   
    bool enhance = false;
    // Structure which would store the metadata
    LinkedList* stockList = new LinkedList();
    // Add items from stock file to the linkedlist
    Purchase* purchase = new Purchase();
    if (argc == 4) {
        if (strcmp(argv[1], ENHANCEFLAG) == 0 && 
            pathValidation(argc, argv[2], argv[3])) {
            stockList->addStockToList(argv[2]);
            stockList->path = argv[2];
            // Load coins from coins file
            vector<vector<string> > coins = LoadFiles::readCoinFile(argv[3]);
            CoinRegister* currentRegister = new CoinRegister(coins,argv[3]);
            purchase->stocklist = stockList;
            purchase->coinRegister = currentRegister;
            enhance = true;
        }
        else {
            std::cerr << "invalid excuting command" << endl;
        }
    }
    
    if (argc == 3) {
        if (pathValidation(argc, argv[1], argv[2])) {
            stockList->addStockToList(argv[1]);
            // Load coins from coins file
            stockList->path = argv[1];
            vector<vector<string> > coins = LoadFiles::readCoinFile(argv[2]);
            CoinRegister* currentRegister = new CoinRegister(coins,argv[2]);
            purchase->stocklist = stockList;
            purchase->coinRegister = currentRegister;
        }
        else {
            std::cerr << "invalid excuting command" << endl;
        }
    }

    
    try {
        executingMenu(purchase, enhance);
        }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << endl;
    }
    
    
    return EXIT_SUCCESS;
}

// Prints the user menu
void printMenu() {
    cout << "Main Menu:" << endl;
    cout << "    1.Display Items" << endl;
    cout << "    2.Purchase Items" << endl;
    cout << "    3.Save and Exit" << endl;
    cout << "Administrator-Only Menu:" << endl;
    cout << "    4.Add Item" << endl;
    cout << "    5.Remove Item" << endl;
    cout << "    6.Display Coins" << endl;
    cout << "    7.Reset Stock" << endl;
    cout << "    8.Reset Coins" << endl;
    cout << "    9.Abort Program" << endl;
    
}

// Removes an item from the given stocklist
void removeItem(LinkedList* stockList) {
    cout << "Enter the item id of the item to remove from the menu: ";
    string item_ID;
    std::getline(std::cin, item_ID);
    StripString::stripString(&item_ID);

    // Checking if user cancels the operation or not
    if (!std::cin.eof() && item_ID != "") {
        Node* item = stockList->searchByID(item_ID);
        if (item != NULL) {
            stockList->deleteNode(item);
        }
    }
    else {
        cout << "Operation cancelled" << endl;
    }

}

// Checking if the path exists
bool pathValidation(int argc, const char* argv1, const char* argv2) {
    struct stat sb;
    bool valid_path = true;
    // If the file/directory exists stat(path, &sb) returns 0
    // first condition:the file/directory does not exists
    // second condition:If the path is a directory
    if (stat(argv1, &sb) != 0 || (sb.st_mode & S_IFDIR) ||
        stat(argv2, &sb) != 0 || (sb.st_mode & S_IFDIR)){
        valid_path = false;
    }
    return valid_path;
}


void executingMenu(Purchase* purchase, bool enhance) {
    // Stores coins in an array of coins
    

    bool running = true;
    while (running) {
        printMenu();
        cout << "Select your option (1-9): ";
        string option;
        std::getline(std::cin, option);
        StripString::stripString(&option);

        if (std::cin.eof() || option == ABORT_PROGRAM_OPTION) {
            running = false;
        }
        else if (option == DISPLAY_ITEMS_OPTION) {
            purchase->stocklist->printList();
        }
        else if (option == PURCHASE_ITEMS_OPTION) {
            purchase->purchaseMenu(enhance);
        }
        else if (option == SAVE_EXIT_OPTION) {
            purchase->stocklist->outputStockFile();
            purchase->coinRegister->storeInFile();
            running = false;
        }
        else if (option == ADD_ITEM_OPTION) {
            AddItem::addItem(purchase->stocklist);
        }
        else if (option == REMOVE_ITEM_OPTION) {
            removeItem(purchase->stocklist);
        }
        else if (option == DISPLAY_COINS_OPTION) {
            purchase->coinRegister->display();
        }
        else if (option == RESET_STOCK_OPTION) {
            purchase->stocklist->resetStock();
        }
        else if (option == RESET_COINS_OPTION) {
            purchase->coinRegister->resetCount();
        }
        else {
            cout << "Invalid" << endl;
        }

        cout << endl;
    }
    delete purchase;
    purchase = nullptr;
}
