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
        while(curr->next != NULL) {
            if(curr->next->data->name > newNode->data->name) {
                newNode->next = curr->next;
                curr->next = newNode;
            }
            curr = curr->next;
        }
        curr->next = newNode;
        count ++;
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


void LinkedList::addStock(std::vector<std::vector<std::string>> stockList){
    
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