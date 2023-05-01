#include "CoinRegister.h"
CoinRegister::CoinRegister(){
    //Constructor
}
CoinRegister::~CoinRegister(){
    //Destructor
}
void CoinRegister::display(){
    std::cout << "Coins Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Denomination    |    Count" << std::endl;
    std::cout << "---------------------------" << std::endl;
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
        
    }
}
void CoinRegister::change(){

}
void CoinRegister::resetCount(){
    for(unsigned int i = 0; i < NUM_DENOMS; i++){
        this->coins[i].resetCount();
    }
}
CoinRegister::CoinRegister(std::vector<std::vector<std::string> > coinVectorList)
{

    unsigned int vectorSize = coinVectorList.size();
    for(unsigned int i = 0; i < vectorSize; i++){
        std::string value = coinVectorList.at(i).at(0);
        unsigned int count = std::stoul (coinVectorList.at(i).at(1),nullptr,0);
        std::cout << "denom:" << (value);
        std::cout << "|Count:"<<  (count) << std::endl;
        if (value == "1000"){
            this->coins[i].denom = TEN_DOLLARS;
        }
        else if (value == "500")
        {
            this->coins[i].denom = FIVE_DOLLARS;
        }
        else if (value == "200")
        {
            this->coins[i].denom = TWO_DOLLARS;
        }
        else if (value == "100")
        {
            this->coins[i].denom = ONE_DOLLAR;
        }
        else if (value == "50")
        {
            this->coins[i].denom = FIFTY_CENTS;
        }
        else if (value == "20")
        {
            this->coins[i].denom = TWENTY_CENTS;
        }
        else if (value == "10")
        {
            this->coins[i].denom = TEN_CENTS;
        }
        else if (value == "5")
        {
            this->coins[i].denom = FIVE_CENTS;
        }
        this->coins[i].count = count;
    }
}