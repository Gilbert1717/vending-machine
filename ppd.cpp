#include <iostream>
#include "LinkedList.h"
#include "LoadFiles.h"
#include "Purchase.h"
#include "CoinRegister.h"
#include "AddItem.h"
#include <sys/stat.h>

using std::cout;
using std::endl;
using std::string;

// Option defines
#define DISPLAY_ITEMS_OPTION "1"
#define PURCHASE_ITEMS_OPTION "2"
#define SAVE_EXIT_OPTION "3"
#define ADD_ITEM_OPTION "4"
#define REMOVE_ITEM_OPTION "5"
#define DISPLAY_COINS_OPTION "6"
#define RESET_STOCK_OPTION "7"
#define RESET_COINS_OPTION "8"
#define ABORT_PROGRAM_OPTION "9"


// Funcution declarations
void printMenu();
void removeItem(LinkedList* stockList);
bool pathValidation(int argc, char **argv);

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
 
    // Structure which would store the metadata
    bool validatePath = pathValidation(argc, argv);
    if (argc == 3 && validatePath) {
        LinkedList* stockList = new LinkedList();
        // Add items from stock file to the linkedlist
        stockList->addStockToList(argv[1]);


        std::vector<std::vector<string> > coins = LoadFiles::readCoinFile(argv[2]);
        CoinRegister* currentRegister = new CoinRegister(coins);
        


        Purchase* purchase = new Purchase(stockList, currentRegister);
    
        
        bool running = true;
        while (running) {
            printMenu();

            cout << "Select your option (1-9): ";
            
            string option;
            std::getline(std::cin, option);

            if (std::cin.eof() || option == ABORT_PROGRAM_OPTION) {
                running = false;
            }
            else if (option == DISPLAY_ITEMS_OPTION) {
                stockList->printList();
            }
            else if (option == PURCHASE_ITEMS_OPTION) {
                purchase->purchaseMenu();
            }
            else if (option == SAVE_EXIT_OPTION) {
                stockList->outputStockFile(argv[1]);
                currentRegister->storeInFile(argv[2]);
                running = false;
            }
            else if (option == ADD_ITEM_OPTION) {
                AddItem::addItem(stockList);
            }
            else if (option == REMOVE_ITEM_OPTION) {
                removeItem(stockList);
            }
            else if (option == DISPLAY_COINS_OPTION) {
                currentRegister->display();
            }
            else if (option == RESET_STOCK_OPTION) {
                stockList->resetStock();
            }
            else if (option == RESET_COINS_OPTION) {
                currentRegister->resetCount();
            }
            else {
                cout << "Invalid" << endl;
            }

            cout << endl;

    }
    
        delete purchase;
        purchase = nullptr;
        delete stockList;
        stockList = nullptr;
        delete currentRegister;
        currentRegister = nullptr;
    }
    else {
        std::cout << "invalid excuting command" << std::endl;
    }
    return EXIT_SUCCESS;
}

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

void removeItem(LinkedList* stockList) {
    cout << "Enter the item id of the item to remove from the menu: ";
    string item_ID;
    std::getline(std::cin, item_ID);

    if (!std::cin.eof() || item_ID != "") {
        Node* item = stockList->searchByID(item_ID);
        if (item != NULL) {
            stockList->deleteNode(item);
        }
    }

}

bool pathValidation(int argc, char **argv) {
    struct stat sb;
    bool valid_path = true;
 
   
    for (int i =0; i < argc; i++) {
        const char* path = argv[i];
        // Calls the function with path as argument
        // If the file/directory exists at the path returns 0
        if (stat(path, &sb) != 0 || (sb.st_mode & S_IFDIR)){
            valid_path = false;
        }
    }
    return valid_path;
}

