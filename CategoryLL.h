#ifndef CATEGORYLL_H
#define CATEGORYLL_H
#include "LinkedList.h"

class CategoryNode
{
public:
    LinkedList* data;
    string category;
    // pointer to the next node in the list 
    CategoryNode* next;
    CategoryNode* prev;
    
    CategoryNode();
    CategoryNode(LinkedList* stocklist,string category);
    ~CategoryNode();
};


class CategoryLL
{
public:
    CategoryLL();
    CategoryLL(string path);
    ~CategoryLL();
    void insertStock(Stock* stock);
    void insertNode(CategoryNode* newCategoryList);
    CategoryNode* searchByCat(string category);
    void addStockToList(string path);
    void resetStock();
    void printList();
    void outputStockFile();
    Node* searchByID(string ID);
    CategoryNode* node;
    string path;

private:
    CategoryNode* head;
    CategoryNode* tail;
    unsigned count;
};




#endif // NODE_H