#ifndef COINREG_H
#define COINREG_H
#include "Coin.h"
#include <vector>

// represents the register of coins 
// will have exactly one of these in the cash register.
class CoinRegister
{
public:
    //Constructors
    CoinRegister();
    CoinRegister(std::vector<std::vector<std::string> > coinVectorList);
    ~CoinRegister();
    //MEthods
    void display();
    void change();
    void resetCount();
private:
    //Array of coins
    Coin coins[NUM_DENOMS];
};


#endif //COINREG_H