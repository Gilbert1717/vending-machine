#ifndef COINREG_H
#define COINREG_H
#include "Coin.h"
#include <vector>
#include <algorithm> //Allows Sorting

//defines
#define FIVE_CENTS_VALUE 5
#define TEN_CENTS_VALUE 10
#define TWENTY_CENTS_VALUE 20
#define FIFTY_CENTS_VALUE 50
#define ONE_DOLLAR_VALUE 100
#define TWO_DOLLAR_VALUE 200
#define FIVE_DOLLAR_VALUE 500
#define TEN_DOLLAR_VALUE 1000

#define CENT_DOLLAR_CONVERSION 100

// represents the register of coins 
// will have exactly one of these in the cash register.
class CoinRegister
{
public:
    //Constructors
    CoinRegister();
    CoinRegister(std::vector<std::vector<std::string> > coinVectorList);
    ~CoinRegister();
    //Methods
    //Prints out the coins in the register
    void display();
    //Returns Change hopefully
    void change();
    //Resets the count of coins
    void resetCount();
    
    //Array of coins
    Coin coins[NUM_DENOMS];
private:
    
};


#endif //COINREG_H