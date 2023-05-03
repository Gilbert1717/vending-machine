#include "AddItem.h"

using std::cout;
using std::endl;
using std::string;


void AddItem::addItem(LinkedList* stockList) {
    string nextId = getNextId(stockList);
    string input;

    Stock* stock = new Stock();
    stock->id = nextId;
    stock->on_hand = DEFAULT_STOCK_LEVEL;

    cout << "Enter the item name: ";
    std::getline(std::cin, input);
    stock->name = input;

    cout << "Enter the item description: ";
    std::getline(std::cin, input);
    stock->description = input;

    bool valid = false;
    while (!valid) {
        cout << "Enter the price for the item: ";
        std::getline(std::cin, input);
        try {
            std::vector<int> price = convertPrice(input);

            stock->price.dollars = price[0];
            stock->price.cents = price[1];

            valid = true;
            
        }
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
    
    bool valid = false;
    while (!valid) {
        testId = intToIdString(testIdNum);

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
    while (snum.length() < 4) {
        snum = string("0").append(snum);
    }

    id = id.append(snum);

    return id;
    
}

std::vector<int> AddItem::convertPrice(string p) {
    std::vector<int> price = std::vector<int>();

    int index = p.find_first_of('.');

    price.push_back(std::stoi(p.substr(0, index)));
    price.push_back(std::stoi(p.substr(index + 1)));

    return price;

}
