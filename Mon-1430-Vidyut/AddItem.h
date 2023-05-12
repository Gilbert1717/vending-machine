#ifndef ADD_ITEM_H
#define ADD_ITEM_H

#include "LinkedList.h"
#include "StripString.h"
#include <iostream>
#include <vector>

// Length of an ID excluding the 'I"
#define ID_NUMBER_LENGTH 4


class AddItem
{
private:
    // Gets the next valid id in the stock list
    static std::string getNextId(LinkedList* stockList);

    // Converts a int into an valid id
    static std::string intToIdString(int num);

    // Converts a price string to a vector with dollars and cents
    static std::vector<int> convertPrice(string p);

    /**
     * Validates and stores input name
     * Returns false in cancelled
    */ 
    static bool inputName(Stock* stock);

    /**
     * Validates and stores input description
     * Returns false if cancelled
    */
    static bool inputDesc(Stock* stock);

    /**
     * Validates and stores input price
     * Returns true if cancelled
    */
    static bool inputPrice(Stock* stock);


public:
    // Adds a new item to the stock
    static void addItem(LinkedList* stockList);

};

#endif