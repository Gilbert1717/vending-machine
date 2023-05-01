#include "Coin.h"

void Coin::resetCount() {
    this->count = DEFAULT_COIN_COUNT;
}
Coin::Coin(){
}
Coin::~Coin(){
}

Coin::Coin(Denomination denom, unsigned count) {
    this->denom = denom;
    this->count = count;
    
}
 // implement functions for managing coins; this may depend on your design.
