#ifndef COINREG_H
#define COINREG_H
#include "Coin.h"
#include <vector>
#include <iostream>
#include <fstream>
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

using std::vector;
using std::string;
// represents the register of coins 
// will have exactly one of these in the cash register.
class CoinRegister
{
public:
    //Constructors
    CoinRegister();
    CoinRegister(vector<vector<string> > coinVectorList, string path);
    ~CoinRegister();
    //Methods
    //Prints out the coins in the register
    void display();
    //Resets the count of coins
    void resetCount();

    void storeInFile();
    
    //Array of coins
    Coin coins[NUM_DENOMS];

    std::string path;
private:
    
};


#endif //COINREG_H