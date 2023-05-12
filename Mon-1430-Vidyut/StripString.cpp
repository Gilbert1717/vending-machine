#include "StripString.h"

using std::string;

// Modified version of split string function I(Vidyut) made for assignment 1(in the helper class)
void StripString::stripString(string* s) {
    size_t firstNotSpace = s->find_first_not_of(" ");

    if (firstNotSpace == string::npos) {
        s->erase(0,s->length());
        
    }
    else {
        s->erase(0, firstNotSpace);

        size_t lastNotSpace = s->find_last_not_of(" ");

        if (lastNotSpace != s->length()-1) {
            s->erase(lastNotSpace+1);
        }
        
    }

}
