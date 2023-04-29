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

Stock::~Stock(){
    
};

Price::Price(){

};

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


void Price::display(){
    if (this->cents == 0) {
        std::cout << "$" << this->dollars << ".00" << std::endl;
    }
    else {
        std::cout << "$" << this->dollars << "." << this->cents << std::endl;
    }
};