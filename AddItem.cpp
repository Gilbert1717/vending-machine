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
    StripString::stripString(&input);
    stock->name = input;

    bool isCancelled = false;
    
    if (input != "") {
        // Gets description of new item
        cout << "Enter the item description: ";
        std::getline(std::cin, input);
        StripString::stripString(&input);
        stock->description = input;

        if (input != "") {
            // Gets price of new item
            bool valid = false;
            bool cancel = false;
            while (!cancel && !valid) {
                cout << "Enter the price for the item: ";
                std::getline(std::cin, input);
                StripString::stripString(&input);

                if (input != "") {
                    // Checks if enterd value is valid and adds to stock
                    try {
                        std::vector<int> price = convertPrice(input);

                        stock->price.dollars = price[0];
                        stock->price.cents = price[1];

                        valid = true;
                        
                    }
                    // Catches if covertPrice() throws an invalid_argument exception
                    catch (std::invalid_argument& e) {
                        std::cerr << e.what() << endl;
                    }
                }
                else {
                    cancel = true;
                }
            }

        
            if (!cancel) {
                cout << "This item \"" << stock->name << " - " << stock->description << "\" has now been added to the menu." << endl;

                stockList->insertNode(stock);
            
            }
            else {
                isCancelled = true;
                
            }

        }
        else {
            isCancelled = true;

        }
    }
    else {
        isCancelled = true;

    }

    if (isCancelled) {
        cout << "Operation cancelled" << endl;

    }

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
    while (snum.length() < ID_NUMBER_LENGTH) {
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
        throw std::invalid_argument("Invalid, please enter price in dollars and cents seperated by '.'");

    }
    
    /**
     * Adds dollars and cents to a vector
     * Throws exception if not a number
     */
    int dollars = std::stoi(p.substr(0, index));
    string centStr = p.substr(index + 1);
    if (centStr.length() < 2) {
        centStr = centStr.append("0");
    }
    else if (centStr.length() > 2) {
        centStr = centStr.substr(0, 2);
        cout << centStr;
    }
    int cents = std::stoi(centStr);
    
    price.push_back(dollars);
    price.push_back(cents);

    // Checks if cent values can be bought using allowed coins
    if (price[1] % 5 != 0) {
        throw std::invalid_argument("Invalid, cent value should be a multiple of 5 (eg. 2.25, 2.30)");
    }

    return price;

}
