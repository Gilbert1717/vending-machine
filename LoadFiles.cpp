#include "LoadFiles.h"

std::vector<std::vector<std::string>> LoadFiles::readFile(
        std::string path, std::string delimiter) {
            std::string line = "";
            std::string tmpString = "";
            // read file to input file stream
            std::ifstream ReadFile(path);
            std::vector<std::vector<std::string>> result;
            /* read each line, split the attributes depending on the delimiter 
            and add them to the result*/
            while (getline(ReadFile, line)) {
                std::vector<std::string> item;
                std::cout << line << std::endl;
                item = split(line, delimiter);
                result.push_back(item);
            }
            ReadFile.close();
            return result;
        }


std::vector<std::string> LoadFiles::split(std::string str, std::string delimiter){
    std::vector<std::string> result;
    while(str.size()){
        std::string::size_type index = str.find(delimiter);
        if(index!=std::string::npos){
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
