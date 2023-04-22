#include "Node.h"

Node::Node(){
    // Stock* data = nullptr;
    // next = NULL;
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
    this->dollars = dollars;
    this->cents = cents;
};