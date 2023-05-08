#include "CoinRegister.h"

using std::string;


CoinRegister::CoinRegister(){
    //Constructor
}
CoinRegister::~CoinRegister(){
    //Destructor
}
void CoinRegister::display(){
    //Prints Header
    std::cout << "Coins Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Denomination    |    Count" << std::endl;
    std::cout << "---------------------------" << std::endl;
    //For each entry in coin list prints out coin
    //Since list is sorted coins need no special printing
    for (unsigned i = 0; i < NUM_DENOMS; i++){
        Denomination value = this->coins[i].denom;
        int count = this->coins[i].count;
        std::cout.width(16);
        if (value == FIVE_CENTS){
            std::cout << std::left << "5 Cents";
        }
        else if (value == TEN_CENTS)
        {
            std::cout << std::left << "10 Cents";
        }
        else if (value == TWENTY_CENTS)
        {
            std::cout << std::left << "20 Cents";
        }
        else if (value == FIFTY_CENTS)
        {
            std::cout << std::left << "50 Cents";
        }
        else if (value == ONE_DOLLAR)
        {
            std::cout << std::left << "1 Dollar";
        }
        else if (value == TWO_DOLLARS)
        {
            std::cout << std::left << "2 Dollar";
        }
        else if (value == FIVE_DOLLARS)
        {
            std::cout << std::left << "5 Dollar";
        }
        else if (value == TEN_DOLLARS)
        {
            std::cout << std::left << "10 Dollar";
        }
        std::cout << "|";
        std::cout.width(9);
        std::cout << std::right << count;
        std::cout << std::endl;
    }
}
void CoinRegister::change(){

}
void CoinRegister::resetCount(){
    //For each coin in register call the reset count method for each
   for(unsigned int i = 0; i < NUM_DENOMS; i++){
        this->coins[i].resetCount();
    }
    std::cout << "Coins have been reset to the default level of "
        << DEFAULT_COIN_COUNT << std::endl;
}
CoinRegister::CoinRegister(std::vector<std::vector<string> > coinVectorList)
{
    unsigned int vectorSize = coinVectorList.size();
    //Creates a temp vector full of integers
    std::vector<std::vector<int> > tempIntVector
        (vectorSize , std::vector<int> (2, 0));

    for(unsigned int j = 0; j < vectorSize; j++){
        tempIntVector.at(j).at(0) = std::stoul 
            (coinVectorList.at(j).at(0),nullptr,0);
        tempIntVector.at(j).at(1) = std::stoul 
            (coinVectorList.at(j).at(1),nullptr,0);
    }
    //Sorts Int Vector
    std::sort(tempIntVector.begin(), tempIntVector.end());
    //Fills up CoinList with given values
    for(unsigned int i = 0; i < vectorSize; i++){
        unsigned int  value = tempIntVector.at(i).at(0);
        unsigned int count = tempIntVector.at(i).at(1);
        //Manually Checks Values
        if (value == TEN_DOLLAR_VALUE){
            this->coins[i].denom = TEN_DOLLARS;
        }
        else if (value ==FIVE_DOLLAR_VALUE)
        {
            this->coins[i].denom = FIVE_DOLLARS;
        }
        else if (value == TWO_DOLLAR_VALUE)
        {
            this->coins[i].denom = TWO_DOLLARS;
        }
        else if (value == ONE_DOLLAR_VALUE)
        {
            this->coins[i].denom = ONE_DOLLAR;
        }
        else if (value == FIFTY_CENTS_VALUE)
        {
            this->coins[i].denom = FIFTY_CENTS;
        }
        else if (value == TWENTY_CENTS_VALUE)
        {
            this->coins[i].denom = TWENTY_CENTS;
        }
        else if (value == TEN_CENTS_VALUE)
        {
            this->coins[i].denom = TEN_CENTS;
        }
        else if (value == FIVE_CENTS_VALUE)
        {
            this->coins[i].denom = FIVE_CENTS;
        }
        this->coins[i].count = count;
    }
}

void CoinRegister::storeInFile(std::string path) {
    std::ofstream coins;
    coins.open(path);
    for (int i = TEN_DOLLARS; i >= FIVE_CENTS; i--) {
        if (this->coins[i].denom == TEN_DOLLARS) {
            coins << TEN_DOLLAR_VALUE << ",";
        }
        else if (this->coins[i].denom == FIVE_DOLLARS) {
            coins << FIVE_DOLLAR_VALUE << ",";
        }
        else if (this->coins[i].denom == TWO_DOLLARS) {
            coins << TWO_DOLLAR_VALUE << ",";
        }
        else if (this->coins[i].denom == ONE_DOLLAR) {
            coins << ONE_DOLLAR_VALUE << ",";
        }
        else if (this->coins[i].denom == FIFTY_CENTS) {
            coins << FIFTY_CENTS_VALUE << ",";
        }
        else if (this->coins[i].denom == TWENTY_CENTS) {
            coins << TWENTY_CENTS_VALUE << ",";
        }
        else if (this->coins[i].denom == TEN_CENTS) {
            coins << TEN_CENTS_VALUE << ",";
        }
        else {
            coins << FIVE_CENTS_VALUE << ",";
        }

        coins << this->coins[i].count << std::endl;


    }

    coins.close();

}
