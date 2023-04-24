#include <iostream>
#include "LinkedList.h"
#include "LoadFiles.h"

using std::cout;
using std::endl;
using std::string;

// Funcution declarations
void printMenu();

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO
    bool running = true;
    while (running) {
        printMenu();

        cout << "Select your option (1-9):";
        
        string option;
        std::getline(std::cin, option);

        if (std::cin.eof()) {
            running = false;
        }
        else if (option == "1") {

        }
        else if (option == "2") {
            
        }
        else if (option == "3") {

        }
        else if (option == "4") {

        }
        else if (option == "5") {

        }
        else if (option == "6") {

        }
        else if (option == "7") {

        }
        else if (option == "8") {

        }
        else if (option == "9") {

        }
        else {
            cout << "Invalid" << endl;
        }

        cout << endl;

    }
    
    /*
    std::vector<std::vector<std::string>> stock = LoadFiles::readFile("stock.dat","|");
    LinkedList stockList = LinkedList();
    stockList.addStockToList(stock);
    stockList.printList();*/
    
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
