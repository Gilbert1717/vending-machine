#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;
void test(bool first, vector<int> i) {
    if (!first) {
        i.push_back(5);
        for (int o : i) {
        cout << o << endl;
    }
    cout << endl;
        return;
    }
    
    i.push_back(5);
    for (int o : i) {
        cout << o << endl;
    }
    cout << endl;

    test(false, i);
    for (int o : i) {
        cout << o << endl;
    }
    cout << endl;
    return;
}

int main(int argc, char **argv) {

    //cout << argc << "\n" << argv[2] << std::endl;

    /*ifstream ReadFile("r.txt");

    string r;
    getline(ReadFile,r);

    cout << r<< endl;*/
    //vector<int> i = vector<int>();
    //test(true,i);

    vector<int> i = vector<int>({4});

    cout << i[0] << endl;

}

;