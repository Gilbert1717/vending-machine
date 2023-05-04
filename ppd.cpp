#include <iostream>
#include "LinkedList.h"
#include "LoadFiles.h"
#include "Purchase.h"
#include "CoinRegister.h"
#include "AddItem.h"

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
void addItem(LinkedList* stockList);
std::string getNextId(LinkedList* stockList);
std::string intToIdString(int num);
std::vector<int> convertPrice(string p);

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    LinkedList* stockList = new LinkedList();
    //std::vector<std::vector<std::string>> stock = LoadFiles::readStockFile("stock.dat"); // TODO use input arguments
    stockList->addStockToList("stock.dat");


    std::vector<std::vector<std::string> > coins = LoadFiles::readCoinFile("coins.dat");
    CoinRegister* currentRegister = new CoinRegister(coins);
    


    Purchase* purchase = new Purchase(stockList, currentRegister);
    
    
    //Testing
    
    /* validate command line arguments */
    // TODO
    
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
            stockList->outputStockFile("stock1.dat");
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

    Node* item = stockList->searchByID(item_ID);
    if (item != NULL) {
        stockList->deleteNode(item);
    }

}
