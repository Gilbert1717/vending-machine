#include "AddItem.h"

using std::cout;
using std::endl;
using std::string;


void AddItem::addItem(CategoryLL* itemList) {
    string nextId = getNextId(itemList);
    string input;

    Stock* stock = new Stock();

    // Gets the next valid ID
    stock->id = nextId;
    stock->on_hand = DEFAULT_STOCK_LEVEL;
    cout << "The id of the new stock will be: " << stock->id << endl;


    if (inputName(stock) && inputDesc(stock) && !inputPrice(stock) &&
        inputCategory(stock)) {
        cout << "This item \"" << stock->name << " - " << 
            stock->description << "\" has now been added to the menu."
            << endl;
        
        itemList->insertStock(stock);
    }
    else {
        cout << "Operation cancelled" << endl;
    }
 
}

std::string AddItem::getNextId(CategoryLL* itemList) {
    int testIdNum = 1;
    string testId;
    
    // Checks each int until the first valid number is found
    bool valid = false;
    while (valid == false) {
        testId = intToIdString(testIdNum);
        
        // Checks if ID doesn't already exist in stock list
        Node* node = itemList->searchByID(testId);
        if (node == NULL) {
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
        throw std::invalid_argument
            ("Invalid, please enter price in dollars and cents seperated by '.'");
    }
    
    /**
     * Adds dollars and cents to a vector
     * Throws exception if invalid
     */
    std::size_t dollarCheck;
    string dollarStr = p.substr(0, index);
    int dollars = std::stoi(dollarStr, &dollarCheck);
    string centStr = p.substr(index + 1);
    if (centStr == "") {
        throw std::invalid_argument("Invalid, no cent inputed");
    }
    // If cent string is a single character(eg. 7), then we append '0' to it(7 becomes 70)
    if (centStr.length() < 2) {
        centStr = centStr.append("0");
    }
    // If cent string has more than 2 characters, then we throw an exception for invalid price
    else if (centStr.length() > 2) {
        throw std::invalid_argument("Invalid, cent value must be max 2 digits");
    }
    std::size_t centCheck;
    int cents = std::stoi(centStr, &centCheck);
    // Checks if dollars and cents input don't have invalid charcters
    if (dollarCheck != dollarStr.length() || centCheck != centStr.length()) {
        throw std::invalid_argument("Invalid");
    }
    price.push_back(dollars);
    price.push_back(cents);

    // Checks if dollars or cents are negative
    if (price[0] < 0 || price[1] < 0) {
        throw std::invalid_argument
            ("Invalid, price must not have negative values");
    }

    // Checks if cent values can be bought using allowed coins
    if (price[1] % 5 != 0) {
        throw std::invalid_argument
            ("Invalid, cent value should be a multiple of 5 (eg. 2.25, 2.30)");
    }

    return price;

}

bool AddItem::inputName(Stock* stock) {
    // Gets name of new item
    bool notCancel = true;
    string input;
    cout << "Enter the item name: ";
    std::getline(std::cin, input);
    StripString::stripString(&input);
    if (!std::cin.eof() && input != "")
        stock->name = input;
    else {
        notCancel = false;
    }

    return notCancel;
}

bool AddItem::inputCategory(Stock* stock) {
    // Gets name of new item
    bool notCancel = true;
    string input;
    cout << "Enter the item catergory: ";
    std::getline(std::cin, input);
    StripString::stripString(&input);
    if (!std::cin.eof() && input != "")
        stock->category = input;
    else {
        notCancel = false;
    }

    return notCancel;
}



bool AddItem::inputDesc(Stock* stock) {
    bool notCancel = true;
    string input;
    cout << "Enter the item description: ";
    std::getline(std::cin, input);
    StripString::stripString(&input);
    if (!std::cin.eof() && input != "")
        stock->description = input;
    else {
        notCancel = false;
    }

    return notCancel;
}

bool AddItem::inputPrice(Stock* stock) {
    string input;
    bool valid = false;
    bool cancel = false;
    while (!cancel && !valid) {
        cout << "Enter the price for the item: ";
        std::getline(std::cin, input);
        StripString::stripString(&input);

        if (!std::cin.eof() && input != "") {
            // Checks if enterd value is valid and adds to stock
            try {
                std::vector<int> price = convertPrice(input);

                stock->price.dollars = price[0];
                stock->price.cents = price[1];

                valid = true;
                
            }
            // Catches if covertPrice() throws an invalid_argument exception
            catch (std::invalid_argument& e) {
                // Checks if std::invalid_argument exception was thrown by std::stoi function
                if ((string)e.what() == "stoi") {
                    std::cerr << "Invalid" << endl;
                }
                else {
                    std::cerr << e.what() << endl;
                }
            }
            catch (std::out_of_range& e) {
                std::cerr << "Invalid, entered amount too long." 
                    << endl;
            }
        }
        else {
            cancel = true;
        }
    }

    return cancel;
   
}