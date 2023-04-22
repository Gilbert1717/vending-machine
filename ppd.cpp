#include <iostream>
#include "LinkedList.h"
#include "LoadFiles.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO
    std::vector<std::vector<std::string>> stock = LoadFiles::readFile("stock.dat","|");
    LinkedList stockList = LinkedList();
    stockList.addStockToList(stock);
    stockList.printList();
    
    return EXIT_SUCCESS;
}
