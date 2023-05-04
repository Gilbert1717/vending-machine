#ifndef LOADFILES_H
#define LOADFILES_H
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using std::string;

class LoadFiles
{
public:
    /** path - the file path in the computer
     *  delimiter - The character that separates the attributes of each object 
     *  in the file.  
     **/
    static std::vector<std::vector<string>> readStockFile(
        std::string path);
    
    static std::vector<std::vector<string>> readCoinFile(
        std::string path);

    // split a string into a vector of strings base on input delimiter
    static std::vector<string> split(string str, string delimiter);

    static void print(std::vector <string> const &a);

    // static void LoadFiles::writeStockFile(LinkedList* stockList);

    // static void LoadFiles::writecoinFile();
};


#endif