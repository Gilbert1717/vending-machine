#ifndef PURCHASE_H
#define PURCHASE_H

class Purchase
{
private:
    bool verifyID(std:: string inputId);
    
public:
    Purchase();
    ~Purchase();

    void purchaseMenu();

};


#endif  // PURCHASE_H