#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
   head = nullptr;
   count = 0;
}

LinkedList::~LinkedList() {
    // TODO
    delete this->head;
    head = nullptr;
}

void LinkedList::insertNode(Stock* stock){
    Node* newNode = new Node(stock);

    if (head == NULL){
        head = newNode;
        count ++;
        return;
    }

    else {
        Node* curr = head;
        if(curr->data->name.compare(newNode->data->name) > 0){
            newNode->next = curr;
            this->head = newNode;
            count ++;
        } 
        else {
            curr = head->next;
            Node* prev = head;
            while(curr != NULL) {
                if(curr->data->name.compare(newNode->data->name) > 0) {
                    newNode->next = curr;
                    prev->next = newNode;
                    count ++;
                    return;
                }
                prev = curr;
                curr = curr->next;
            }
        
            if (curr == NULL) {
                prev->next = newNode;
            }
        }
        
        
    }
}

void LinkedList::deleteNode(Node* node){
    if (this->head == NULL) {
        std::cout << "Stock List is empty." << std::endl;
        return;
    }

    else {
        if (this->head == node) {
            this->head = this->head->next;
            delete node;
            node = nullptr;
            count --;
        }
        else {
            Node* pre = NULL;
            Node* curr = head;
            while (curr->next != NULL){
                pre = curr;
                curr = curr->next;
                if (curr == node) {
                    pre->next = curr->next;
                    delete curr;
                    curr = nullptr;
                    count --;
                }
            }   
            // std::cout << "The item does not exist in the list." << std::endl;
        } 
    }
}

//Search node base on item ID and return the pointer of this node 
Node* LinkedList::searchByID(std::string ID){
    if (count == 0) {
        throw std::invalid_argument( "Stock List is empty." );
    }
    else {
        Node* curr = head;
        while(curr != NULL){
            if (curr->data->id == ID) {
                return curr;
            }
            curr = curr->next;
        }
        throw std::invalid_argument( "The item does not exist in the list." );   
    }  
}


void LinkedList::addStockToList(std::vector<std::vector<std::string>> stockVectorList){
    for (std::vector<std::string> item : stockVectorList) { 
        std::vector<std::string> itemPrice = LoadFiles::split(item.at(3),".");
        unsigned long dollars = std::stoul (itemPrice.at(0),nullptr,0);
        unsigned long cents = std::stoul (itemPrice.at(1),nullptr,0);
        unsigned long on_hand = std::stoul (item.at(4),nullptr,0);
        insertNode(new Stock(item.at(0),item.at(1),item.at(2),Price(dollars,cents),on_hand));
    }
}

void LinkedList::printList(){
    Node* curr = head;
    std::cout << "Item Menu" << std::endl;
    std::cout << "------------------------" <<std::endl;
    while (curr != nullptr) {
        std::cout << curr->data->id << "|";
        std::cout << curr->data->name << "|";
        std::cout << curr->data->description << "|";
        curr->data->price.display();
        std::cout << "|";
        std::cout << curr->data->on_hand << std::endl;
        std::cout << "------------------------" <<std::endl;
        curr = curr->next;
    }
}
// Node* LinkedList::searchByName(std::string Name){
//     if (count == 0) {
//         std::cout << "Stock List is empty." << std::endl;
//         return;
//     }
//     else {
//         Node* curr = head;
//         while(curr != NULL){
//             if (curr->data->id == Name) {
//                 return curr;
//             }
//             curr = curr->next;
//         }
//         std::cout << "The item does not exist in the list." << std::endl;     
//     }  
// }