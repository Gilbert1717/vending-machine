#include "LoadFiles.h"
#include "Node.h"

// Load stock file and return a vector of stock attributes in string formate
std::vector<std::vector<std::string>> LoadFiles::readStockFile(
        std::string path) {
            string line = "";
            string tmpString = "";

            // read file to input file stream
            std::ifstream ReadFile(path);
            std::vector<std::vector<std::string>> result;

            /* read each line, split the attributes depending on the delimiter 
            and add them to the result*/
            while (getline(ReadFile, line)) {
                std::vector<string> item;
                item = split(line, STOCK_DELIMITER);
                // Throw error if there are not 5 stock attributes
                if (item.size() != 6) {
                    ReadFile.close();
                    throw std::invalid_argument( "invalid stock file" );
                }
                result.push_back(std::move(item));
            }
            ReadFile.close();
            return result;
        }

// Load coins file and return a vector of coin attributes in string formate
std::vector<std::vector<std::string>> LoadFiles::readCoinFile(
        std::string path) {
            string line = "";
            string tmpString = "";

            // read file to input file stream
            std::ifstream ReadFile(path);
            std::vector<std::vector<std::string>> result;
            //Set for the values of coins
            std::set<std::string> values;
            /* read each line, split the attributes depending on the delimiter 
            and add them to the result*/
            while (getline(ReadFile, line)) {
                std::vector<string> coin;
                coin = split(line, ",");
                // Throw error if there are not 5 stock attributes
                if (coin.size() != 2) {
                    ReadFile.close();
                    throw std::invalid_argument( "invalid coin file" );
                }
                values.insert(coin.at(0));
                result.push_back(std::move(coin));
            }
            ReadFile.close();
            if (result.size() != NUM_DENOMS || values.size() != NUM_DENOMS){
                throw std::invalid_argument( "invalid coin file" );
            }
            return result;
        }

// Split string into vector of strings based on input delimiter
std::vector<string> LoadFiles::split(string str, string delimiter){
    std::vector<string> result;
    // Keep substract string base on the delimiter when input string is not empty.
    while(str.size()){
        string::size_type index = str.find(delimiter);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+delimiter.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

// method for testing purpose, can be removed later.
void LoadFiles::print(std::vector <string> const &a) {
   std::cout << "The vector elements are : ";
   for(unsigned i=0; i < a.size(); i++)
   std::cout << a.at(i) << ' ' << std::endl;
}

// compare two strings, return true if the first string is larger than the second
bool LoadFiles::compareName(string currName, string insertName){
    /*initialise string and convert them to lowercase, so that compare
    them will be case-insensitive*/ 
    bool result = false;
    std::transform(currName.begin(), currName.end(), 
        currName.begin(), ::tolower);
    std::transform(insertName.begin(), insertName.end(), 
        insertName.begin(), ::tolower);

    if(currName.compare(insertName) > 0) {
        result = true;
    }
    
    return result;
}

// Function that add paddings to a string
string LoadFiles::padding(string s, int length, char filler){
    string result = s.append(length - s.length(), filler);
    return result;
}



