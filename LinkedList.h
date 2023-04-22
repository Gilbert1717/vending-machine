#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...
    void insertNode(Stock* stock);

    void deleteNode(Node* node);

    Node* searchByID(std::string ID);

    Node* searchByName(std::string name);

    void addStock(std::vector<std::vector<std::string>> stockList);

    void printList();

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


