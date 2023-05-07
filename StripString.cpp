#include "StripString.h"

using std::string;

// Split string function I(Vidyut) made for assignment 1(in the helper class)
void StripString::stripString(string* s) {
    unsigned firstNotSpace = s->find_first_not_of(" ");
    
    s->erase(0, firstNotSpace);

    unsigned lastNotSpace = s->find_last_not_of(" ");

    if (lastNotSpace != s->length()-1) {
        s->erase(lastNotSpace+1);
    }
}
