#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#ifndef INIT_HPP
#define INIT_HPP

// read data from init.txt and return it as a vector

namespace engine
{
    std::vector<int> init(){
        std::vector<int> arr;
        std::ifstream file;
        file.open("init.txt", std::ios::in);
        if(!file.is_open()){
            std::cout << "init.txt not found, creating new file" << std::endl;
            std::ofstream new_file;
            new_file.open("init.txt", std::ios::out);
            new_file << "100\n";
            new_file.close();
            file.open("init.txt", std::ios::in);
        }
        if(file.is_open()){
            std::string line;
            while(getline(file, line)){
                arr.push_back(std::stoi(line));
            }
        }
        file.close();

        return arr;
    }
}
#endif