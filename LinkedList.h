#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include "LoadFiles.h"
#include <algorithm>
using std::string;


class LinkedList
{
public:
    LinkedList();
    // LinkedList(string category);
    ~LinkedList();
    // insert stock to the linkedlist following alphabetic order
    void insertNode(Stock* stock);

    // return true when currName is larger than insertName
    bool compareName(string currName, string insertName);

    void deleteNode(Node* node);

    Node* searchByID(string ID);

    void addStockToList(string path);

    void printList();

    string padding(string s, int length, char filler);

    void resetStock();

    std::vector<string> exportStockListString();

    // void outputStockFile();

private:
    // the beginning of the list
    Node* head;
    Node* tail;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


