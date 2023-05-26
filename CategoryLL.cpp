#include "CategoryLL.h"
using std::string;
using std::vector;


CategoryLL::CategoryLL(){
    this->head = nullptr;
    this->tail = nullptr;
}

CategoryLL::~CategoryLL(){
    CategoryNode* curr = this->head;
    CategoryNode* tmp = nullptr;
    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        delete tmp;
        tmp = nullptr;
    }
    delete curr;
    curr = nullptr;
}

CategoryLL::CategoryLL(string path){
    this->head = nullptr;
    this->tail = nullptr;
    this->path = path;
}

CategoryNode* CategoryLL::searchByCat(string category){
    CategoryNode* result = NULL;

    // Loop through the whole list
    if (this->head != NULL){
        CategoryNode* curr = head;
        while(curr != NULL){
            if (curr->category == category) {
                result = curr;
            }
            curr = curr->next;
        }
    }  
    return result;
}


// insert the node to the last element of category linked list.
bool CategoryLL::insertNode(CategoryNode* newNode){
    bool success = true;
    // ID validation (if the ID is existing in the list)
    if (searchByCat(newNode->category) != NULL) {
            success = false;
    }

    else {
        if (head == NULL){
            this->head = newNode;
            this->tail = newNode;
        }

        else {
            newNode->prev = this->tail;
            this->tail->next = newNode;
            this->tail = newNode;
        }
    }
    return success;
}


void CategoryLL::insertStock(Stock* stock){
    Node* newNode = new Node(stock);
    if (searchByID(stock->id)!= NULL) {
            throw std::invalid_argument
                ("The ID of this stock is existing in the list");
        }
    CategoryNode* stockList = searchByCat(newNode->data->category);
    // insert to head if the linked list is empty
    if (stockList == NULL) {
        CategoryNode* newStockList = new CategoryNode();
        newStockList->category = stock->category;
        newStockList->data = new LinkedList();
        newStockList->data->insertNode(stock);
        insertNode(newStockList);
    }

    else {
        
        stockList->data->insertNode(stock);
    }
}

void CategoryLL::resetStock(){
    CategoryNode* curr = head;
    while(curr != NULL){
        curr->data->resetStock();
        curr = curr->next;
    }
    std::cout << "Stock has been reset to the default level of " 
        << DEFAULT_STOCK_LEVEL << std::endl;
}

// Formating the stock table and print the stock out
void CategoryLL::printList(){
    CategoryNode* curr = head;

    // print header of the table
    string header = LoadFiles::padding("", 70 ,'-');
    std::cout << "Item Menu" << std::endl;
    std::cout << LoadFiles::padding("", 10 ,'-') << std::endl;
    std::cout << LoadFiles::padding("ID", IDLEN ,' ') << "|";
    std::cout << LoadFiles::padding("Name", NAMELEN ,' ') << "|";
    std::cout << LoadFiles::padding("Available", 10 ,' ') << "|";
    std::cout << "Price" << std::endl;
    std::cout << header <<std::endl;

    // Iterate linkedlist to print each item
    while (curr != nullptr) {
        std::cout << curr->category << ":" << std::endl;
        curr->data->printList();
        std::cout << std::endl;
        curr = curr->next;
    }
    std::cout << header <<std::endl;
}

void CategoryLL::addStockToList(string path){
    vector<vector<string>> stockList = LoadFiles::readStockFile(path); 
    
    // enhanced for loop to iterate all items in stock list
    for (std::vector<std::string> item : stockList) { 
        // covert the attributes to the desired variable type
        // if (item.at(6))
        std::vector<std::string> itemPrice = LoadFiles::split(item.at(3),".");

        // price validation
        if (itemPrice.size() != 2) {
            throw std::invalid_argument( "Invalid price." );
        }

        unsigned long dollars;
        unsigned long cents;
        unsigned long on_hand;
        // try to convert strings to numbers, if any of the value is invalid, throw
        // an invalid_argument error
        try {
            dollars = std::stoul (itemPrice.at(0),nullptr,0);
            cents = std::stoul (itemPrice.at(1),nullptr,0);
            on_hand = std::stoul (item.at(4),nullptr,0);
        }
        catch (std::invalid_argument& e) {
            throw std::invalid_argument("Wrong attribute value");
        }

        // Create stock and store them into linked list
        Stock* stock = new Stock(item.at(0),item.at(1),item.at(2),
                    Price(dollars,cents),on_hand,item.at(5));
        insertStock(stock);
    }
}

Node* CategoryLL::searchByID(string ID){
    CategoryNode* curr = this->head;
    Node* result = NULL;
    bool found = false;
    // Iterate linkedlist to print each item
    while (curr != NULL && !found) {
        result = curr->data->searchByID(ID);
        curr = curr->next;
        if (result != NULL) {
            found = true;
        }
    }
    return result;
}

void CategoryLL::outputStockFile(){
    std::ofstream stock;
    stock.open (this->path);
    CategoryNode* curr = head;
    while (curr != NULL) {
        std::vector<std::string> stockOutput = curr->data->exportStockListString();
        for (unsigned i = 0; i<stockOutput.size(); i++){
            stock << stockOutput.at(i) <<std::endl;   
        }
        curr = curr->next;
    }
    
    stock.close();
}

CategoryNode::CategoryNode(){
    
};

CategoryNode::~CategoryNode(){
    delete data;
    data = nullptr;
};

CategoryNode::CategoryNode(LinkedList* stocklist, string category){
    this->data = stocklist;
    this->category = category;
    this->next = NULL;
    this->prev = NULL;
};



