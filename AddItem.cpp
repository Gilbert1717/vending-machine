#include "AddItem.h"

using std::cout;
using std::endl;
using std::string;


void AddItem::addItem(LinkedList* stockList) {
    string nextId = getNextId(stockList);
    string input;

    Stock* stock = new Stock();

    // Gets the next valid ID
    stock->id = nextId;
    stock->on_hand = DEFAULT_STOCK_LEVEL;
    cout << "The id of the new stock will be: " << stock->id << endl;
    
    // Gets name of new item
    cout << "Enter the item name: ";
    std::getline(std::cin, input);
    stock->name = input;
    
    // Gets description of new item
    cout << "Enter the item description: ";
    std::getline(std::cin, input);
    stock->description = input;

    // Gets price of new item
    bool valid = false;
    while (!valid) {
        cout << "Enter the price for the item: ";
        std::getline(std::cin, input);
        // Checks if enterd value is valid and adds to stock
        try {
            std::vector<int> price = convertPrice(input);

            stock->price.dollars = price[0];
            stock->price.cents = price[1];

            valid = true;
            
        }
        // Catches if covertPrice() throws an invalid_argument exception
        catch (std::invalid_argument& e) {
            cout << "Invalid" << endl;
        }

    }

    cout << "This item \"" << stock->name << " - " << stock->description << "\" has now been added to the menu." << endl;

    stockList->insertNode(stock);

}

std::string AddItem::getNextId(LinkedList* stockList) {
    int testIdNum = 1;
    string testId;
    
    // Checks each int until the first valid number is found
    bool valid = false;
    while (!valid) {
        testId = intToIdString(testIdNum);
        
        // Checks if ID doesn't already exist in stock list
        if (stockList->searchByID(testId) == NULL) {
            valid = true;
            
        }
        else {
            testIdNum++;
            
        }

    }

    return testId;


}

std::string AddItem::intToIdString(int num) {
    string id = "I";

    string snum = std::to_string(num);

    // Adds correct number of 0 before the num
    while (snum.length() < 4) {
        snum = string("0").append(snum);
    }

    id = id.append(snum);

    return id;
    
}

std::vector<int> AddItem::convertPrice(string p) {
    std::vector<int> price = std::vector<int>();

    std::size_t index = p.find_first_of('.');
    
    // Checks if input has a decimal point
    if (index == string::npos) {
        throw std::invalid_argument("Not a float");

    }
    
    /**
     * Adds dollars and cents to a vector
     * Throws exception if not a number
     */
    price.push_back(std::stoi(p.substr(0, index)));
    price.push_back(std::stoi(p.substr(index + 1)));

    // Checks if cent values can be bought using allowed coins
    if (price[1] % 5 != 0) {
        throw std::invalid_argument("Not a multiple of 5");
    }

    return price;

}
