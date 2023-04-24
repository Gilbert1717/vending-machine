#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char **argv) {

    //cout << argc << "\n" << argv[2] << std::endl;

    ifstream ReadFile("r.txt");

    string r;
    getline(ReadFile,r);

    cout << r<< endl;
}