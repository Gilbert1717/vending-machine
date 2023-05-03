#ifndef ADD_ITEM_H
#define ADD_ITEM_H

#include "LinkedList.h"
#include <iostream>
#include <vector>



class AddItem
{
private:
    static std::string getNextId(LinkedList* stockList);
    static std::string intToIdString(int num);
    static std::vector<int> convertPrice(string p);

public:
    static void addItem(LinkedList* stockList);

};

#endif