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

    // insert stock to the linkedlist following alphabetic order
    void insertNode(Stock* stock);

    void deleteNode(Node* node);

    Node* searchByID(string ID);

    Node* searchByName(string name);

    void addStockToList(string path);

    void printList();

    string padding(string s, int length, char filler);

    void resetStock();

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


