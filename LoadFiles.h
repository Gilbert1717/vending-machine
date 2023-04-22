#ifndef LOADFILES_H
#define LOADFILES_H
#include <iostream>
#include <fstream>
#include <vector>


class LoadFiles
{
public:
    /** path - the file path in the computer
     *  delimiter - The character that separates the attributes of each object 
     *  in the file.  
     **/
    static std::vector<std::vector<std::string>> readFile(
        std::string path, std::string delimiter);
    // static void readFile(
    //     std::string path, std::string delimiter);

    static std::vector<std::string> split(std::string str, std::string delimiter);

    static void print(std::vector <std::string> const &a);
};


#endif