#include "LoadFiles.h"

std::vector<std::vector<std::string>> LoadFiles::readFile(
        std::string path, std::string delimiter) {
            std::string line = "";
            std::string tmpString = "";
            std::ifstream ReadFile(path);
            std::vector<std::vector<std::string>> result;
            while (getline(ReadFile, line)) {
                std::vector<std::string> item;
                std::cout << line << std::endl;
                item = split(line, delimiter);
                result.push_back(item);
            }
            ReadFile.close();
            // For loop to print each element in result for debug purpose.
            // for(int i=0; i < result.size(); i++) {
            //     print(result.at(i));
            //     std::cout << std::endl;
            // }
            return result;
        }


std::vector<std::string> LoadFiles::split(std::string str, std::string delimiter){
    std::vector<std::string> result;
    while(str.size()){
        unsigned long index = str.find(delimiter);
        if(index != std::string::npos){
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

void LoadFiles::print(std::vector <std::string> const &a) {
   std::cout << "The vector elements are : ";
   for(unsigned i=0; i < a.size(); i++)
   std::cout << a.at(i) << ' ' << std::endl;
}
