#ifndef COINREG_H
#define COINREG_H
#include "Coin.h"
#define size 8

// represents the register of coins 
// will have exactly one of these in the cash register.
class CoinRegister
{
public:
    //Constructors
    CoinRegister();
    ~CoinRegister();
    //MEthods
    void CoinRegister::display();
    void CoinRegister::change();
    void CoinRegister::resetCount();
private:
    //Array of coins
    Coin coins[size];
};


#endif //COINREG_H