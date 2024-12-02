#include <iostream>

#include <fstream>
#include <vector>
#include <algorithm>

int main() {

    std::vector<int> list[2];

    list[0]=std::vector<int>();
    list[1]=std::vector<int>();

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");
    std::string line;
    while (getline (inputFile, line)) {
        auto middle = line.find(' ');
        list[0].push_back( std::stoi( line.substr(0, middle)) );
        list[1].push_back( std::stoi( line.substr(middle, line.size()-middle )) );
    }
    inputFile.close();

    /* Part 1 :
    std::sort(list[0].begin(), list[0].end());
    std::sort(list[1].begin(), list[1].end());

    int difference=0;
    for(int i=0; i<list[0].size(); ++i)
        difference += abs(list[0].at(i) - list[1].at(i));

    std::cout << difference << std::endl;
    */

    int similarity = 0;
    for(int i=0; i<list[0].size(); ++i)
        similarity += list[0].at(i) * std::count(list[1].begin(), list[1].end(), list[0].at(i));

    std::cout << similarity << std::endl;

    return 0;

    /*
     * amelioration possible pour parti deux :
     *  - cache pour les numeros deja traité
     */
}
