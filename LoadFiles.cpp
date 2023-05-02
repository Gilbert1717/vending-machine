#include "LoadFiles.h"
#include "Node.h"


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
                if (item.size() != 5) {
                    ReadFile.close();
                    throw std::invalid_argument( "invalid stock file" );
                }
                result.push_back(std::move(item));
            }
            ReadFile.close();
            return result;
        }

std::vector<std::vector<std::string>> LoadFiles::readCoinFile(
        std::string path) {
            string line = "";
            string tmpString = "";

            // read file to input file stream
            std::ifstream ReadFile(path);
            std::vector<std::vector<std::string>> result;
            
            /* read each line, split the attributes depending on the delimiter 
            and add them to the result*/
            while (getline(ReadFile, line)) {
                std::vector<string> coin;
                coin = split(line, ",");
                if (coin.size() != 2) {
                    ReadFile.close();
                    throw std::invalid_argument( "invalid coin file" );
                }
                result.push_back(std::move(coin));
            }
            ReadFile.close();
            return result;
        }


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



// void LoadFiles::writecoinFile(){

// }
