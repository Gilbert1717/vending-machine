#include "LoadFiles.h"


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
                item = split(line, "|");
                result.push_back(item);
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
                std::vector<string> item;

                item = split(line, ",");

                result.push_back(item);
            }
            ReadFile.close();
            return result;
        }


std::vector<string> LoadFiles::split(string str, string delimiter){
    std::vector<string> result;
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

void LoadFiles::print(std::vector <string> const &a) {
   std::cout << "The vector elements are : ";
   for(unsigned i=0; i < a.size(); i++)
   std::cout << a.at(i) << ' ' << std::endl;
}
