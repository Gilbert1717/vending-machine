#include "Node.h"
using std::string;
Node::Node(){
    
};
Node::~Node(){
    delete data;
    data = nullptr;
};

Node::Node(Stock* stock){
    this->data = stock;
    this->next = NULL;
};

Stock::Stock(){

};

Stock::Stock(
        std::string id, 
        std::string name, 
        std::string description, 
        Price price,
        unsigned on_hand
){
    // attributes validation
    if (id.length() > IDLEN) {
        throw std::invalid_argument( "Stock ID is too long" );
    }

    if (name.length() > NAMELEN) {
        throw std::invalid_argument( "Stock name is too long" );
    }

    if (description.length() > DESCLEN) {
        throw std::invalid_argument( "Stock description is too long" );
    }
    
    if (on_hand < 0) {
        throw std::invalid_argument( "Stock number cannot be negarive" );
    }

    this->id = id;
    this->name = name;
    this->description = description;
    this->price = price;
    this->on_hand = on_hand;
};

// convert all the stock attributes into one string to write them into output file.
std::string Stock::convertStockToString(){
    std::string result = this->id + STOCK_DELIMITER + this->name + 
        STOCK_DELIMITER + this->description;

    // handle the case when cents is 0
    std::string cents = "00";
    if (this->price.cents != 0) cents = std::to_string(this->price.cents);
    
    result = result + STOCK_DELIMITER + 
        std::to_string(this->price.dollars) + '.' + cents;
    
    result = result + STOCK_DELIMITER + std::to_string(this->on_hand);

    return result;
}

Stock::~Stock(){
    
};

Price::Price(){

};

// Price constructor
Price::Price(unsigned dollars, unsigned cents){
    if ((cents < 0) || (cents > 99)) {
        throw std::invalid_argument("cents cannot be larger than 99 or negative");
    }
    if ((dollars < 0)) {
        throw std::invalid_argument("dollars cannot be negative");
    }
    this->dollars = dollars;
    this->cents = cents;
};

// display price
void Price::display(){
    // if the cents is 0, this method will print double 0 for the cents.
    string cents = std::to_string(this->cents);
    if (this->cents < 10) {
        cents = "0" + cents;
    }
    std::cout << "$" << this->dollars << "." << cents << std::endl;
    
};