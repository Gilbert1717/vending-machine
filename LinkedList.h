#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include "LoadFiles.h"
using std::string;


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();


    void insertNode(Stock* stock);

    void deleteNode(Node* node);

    Node* searchByID(string ID);

    Node* searchByName(string name);

    void addStockToList(string path);

    void printList();

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


