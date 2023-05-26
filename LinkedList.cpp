#include "LinkedList.h"
#include <iostream>
using std::vector;

LinkedList::LinkedList() {
   this->head = nullptr;
   this->tail = nullptr;
   this->count = 0;
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
        if(LoadFiles::compareName(head->data->name,newNode->data->name)){
            newNode->next = curr;
            curr->prev = newNode;
            this->head = newNode;
            count ++;
        } 
        
        /*insert to the tail of the linked list if the name of the new node is 
        larger than all nodes in the linked list
        */
        else if(!LoadFiles::compareName(tail->data->name,newNode->data->name)){
            tail->next = newNode;
            newNode->prev = tail;
            this->tail = newNode;
            count ++;
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
                if(LoadFiles::compareName(curr->data->name,newNode->data->name)) {
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




// delete stock function
void LinkedList::deleteNode(Node* node){
    bool remove = false;
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
            this->head = node->next;
            remove = true;
            
        }
        if (node->prev != NULL) {
            node->prev->next = node->next;
            remove = true;
        }
        if (node->prev != NULL) {
            node->prev->next = node->next;
            remove = true;
        }
        if (remove == true) {
            std::cout << "\"" << node->data->id << " - " << 
                    node->data->name << " - " << node->data->description << 
                    "\"" << " has been removed from the system.\n";
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
    if (this->head == NULL) {
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


// reset stock list to the default stock level
void LinkedList::resetStock(){
    Node* curr = head;
    while(curr != NULL){
        curr->data->on_hand = DEFAULT_STOCK_LEVEL;
        curr = curr->next;
    }
    // std::cout << "Stock has been reset to the default level of " 
    //     << DEFAULT_STOCK_LEVEL << std::endl;
}

// Formating the stock table and print the stock out
void LinkedList::printList(){
    Node* curr = head;
    
    // Iterate linkedlist to print each item
    while (curr != nullptr) {
        string nameRow = LoadFiles::padding(curr->data->name, NAMELEN, ' ');
        string on_handRow = LoadFiles::padding(
            std::to_string(curr->data->on_hand),10,' ');
        std::cout << curr->data->id << "|";
        std::cout << nameRow << "|";
        std::cout << on_handRow << "|";
        curr->data->price.display();
        curr = curr->next;
    }
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


