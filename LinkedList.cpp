#include "LinkedList.h"
#include <iostream>
using std::vector;

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   count = 0;
}

LinkedList::~LinkedList() {
    Node* curr = this->head;
    Node* tmp;
    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        delete tmp;
        tmp = nullptr;
    }
    delete curr;
    curr = nullptr;
}

// inserting stock function
void LinkedList::insertNode(Stock* stock){
    Node* newNode = new Node(stock);
    // insert to head if the linked list is empty
    if (head == NULL){
        head = newNode;
        tail = newNode;
        count ++;
    }

    else {
        // ID validation (if the ID is existing in the list)
        if (searchByID(stock->id) != NULL) {
            throw std::invalid_argument
                ("The ID of this stock is existing in the list");
        }
        Node* curr = head;
        /* if the stock name is smaller than the head of the linked list, insert
        it to the head*/
        if(curr->data->name.compare(newNode->data->name) > 0){
            newNode->next = curr;
            curr->prev = newNode;
            this->head = newNode;
            count ++;
        } 
        
        /*insert to the tail of the linked list if the name of the new node is 
        larger than all nodes in the linked list
        */
        else if(tail->data->name.compare(newNode->data->name) < 0){
            tail->next = newNode;
            newNode->prev = tail;
            this->tail = newNode;
        }

        /* loop through the whole linked list to find the right place to insert
            the node */ 
        else {
            curr = head->next;
            Node* prev = head;
            bool whileLoopContinue = true;

            /* When curr node name is larger than the new node,
            insert the new node before curr node*/
            while(curr != NULL && whileLoopContinue) {  
                /*compare two strings and decide if the node need to be inserted
                into curr node*/ 
                if(compareName(curr->data->name,newNode->data->name)) {
                    newNode->next = curr;
                    curr->prev = newNode;
                    prev->next = newNode;
                    newNode->prev = prev;
                    count ++;
                    whileLoopContinue = false;
                }

                //else move to the next node
                else {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
}


// compare two strings, return true if the first string is larger than the second
bool LinkedList::compareName(string currName, string insertName){
    /*initialise string and convert them to lowercase, so that compare
    them will be case-insensitive*/ 
    bool result = false;
    std::transform(currName.begin(), currName.end(), 
        currName.begin(), ::tolower);
    std::transform(insertName.begin(), insertName.end(), 
        insertName.begin(), ::tolower);

    if(currName.compare(insertName) > 0) {
        result = true;
    }
    
    return result;
}

// delete stock function
void LinkedList::deleteNode(Node* node){
    // Print error message if the linked list is empty
    if (this->head == NULL) {
        std::cout << "Stock List is empty." << std::endl;
    }

    else if (node == nullptr) {
        std::cout << "Item does not exist in stock list\n" << std::endl;
    }

    else {
        // If the input node is the head of the linked list
        if (this->head == node) {
            this->head = this->head->next;
            std::cout << "\"" << node->data->id << " - " << 
                    node->data->name << " - " << node->data->description << 
                    "\"" << " has been removed from the system.\n";
            delete node;
            node = nullptr;
            count --;
        }

        else if(this->tail == node) {
            this->tail = this->tail->prev;
            this->tail->next = NULL;
            std::cout << "\"" << node->data->id << " - " << 
                    node->data->name << " - " << node->data->description << 
                    "\"" << " has been removed from the system.\n";
            delete node;
            node = nullptr;
            count --;
        }

        // delete the node base on the pointer
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            std::cout << "\"" << node->data->id << " - " << 
            node->data->name << " - " << node->data->description << 
            "\"" << "has been removed from the system\n";
            delete node;
            node = nullptr;
            count --;
        } 
    }
}

//Search node base on item ID and return the pointer of this node 
Node* LinkedList::searchByID(std::string ID){
    Node* result = NULL;

    // When list is empty
    if (count == 0) {
        std::cout << "Stock List is empty searchByID." << std::endl;
    }

    // Loop through the whole list
    else {
        Node* curr = head;
        while(curr != NULL){
            if (curr->data->id == ID) {
                result = curr;
            }
            curr = curr->next;
        }
    }  
    return result;
}

// Load the file from the path and add all items into stock list
void LinkedList::addStockToList(string path){
    vector<vector<string>> stockList = LoadFiles::readStockFile(path); 
    
    // enhanced for loop to iterate all items in stock list
    for (std::vector<std::string> item : stockList) { 

        // covert the attributes to the desired variable type
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
                    Price(dollars,cents),on_hand);
        insertNode(stock);
    }
}

// reset stock list to the default stock level
void LinkedList::resetStock(){
    Node* curr = head;
    while(curr != NULL){
        curr->data->on_hand = DEFAULT_STOCK_LEVEL;
        curr = curr->next;
    }
    std::cout << "Stock has been reset to the default level of " 
        << DEFAULT_STOCK_LEVEL << std::endl;
}

// Formating the stock table and print the stock out
void LinkedList::printList(){
    Node* curr = head;

    // print header of the table
    string header = padding("", 70 ,'-');
    std::cout << "Item Menu" << std::endl;
    std::cout << padding("", 10 ,'-') << std::endl;
    std::cout << padding("ID", IDLEN ,' ') << "|";
    std::cout << padding("Name", NAMELEN ,' ') << "|";
    std::cout << padding("Available", 10 ,' ') << "|";
    std::cout << "Price" << std::endl;
    std::cout << header <<std::endl;

    // Iterate linkedlist to print each item
    while (curr != nullptr) {
        string nameRow = padding(curr->data->name, NAMELEN, ' ');
        string on_handRow = padding(std::to_string(curr->data->on_hand),10,' ');
        std::cout << curr->data->id << "|";
        std::cout << nameRow << "|";
        std::cout << on_handRow << "|";
        curr->data->price.display();
        curr = curr->next;
    }
    std::cout << header <<std::endl;
}

// return vector of item string
vector<string> LinkedList::exportStockListString(){
    vector<string> result;

    // Loop through linkedlist
    Node* curr = this->head;
    while (curr != NULL) {
        string item = curr->data->convertStockToString();
        result.push_back(item);
        curr = curr->next;
    }
    return result;
}


// Write stock list into file and store in the target path
void LinkedList::outputStockFile(){
    std::ofstream stock;
    stock.open (this->path);
    std::vector<std::string> stockOutput = exportStockListString();
    for (unsigned i = 0; i<stockOutput.size(); i++){
        stock << stockOutput.at(i) <<std::endl;   
    }
    stock.close();
}

// Function that add paddings to a string
string LinkedList::padding(string s, int length, char filler){
    string result = s.append(length - s.length(), filler);
    return result;
}
