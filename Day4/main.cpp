#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>

/*Part 1
std::map<char, int> wordToInt{{'X', 1}, {'M', 2}, {'A', 3}, {'S', 4}};

int searchInString(std::string string) {
    int nb=0;

    std::regex increasing("XMAS");
    std::regex decreasing("SAMX");

    auto increasingBegin = std::sregex_iterator(string.begin(), string.end(), increasing);
    auto increasingEnd = std::sregex_iterator();
    nb+=(int)std::distance(increasingBegin, increasingEnd);

    auto decreasingBegin = std::sregex_iterator(string.begin(), string.end(), decreasing);
    auto decreasingEnd = std::sregex_iterator();
    nb+=(int)std::distance(decreasingBegin, decreasingEnd);

    return nb;
}

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt")

    std::vector<std::string> lignes;

    std::string line;
    while (getline (inputFile, line)) {
        if(line.at(line.size()-1) == '\r') line.pop_back();
        lignes.emplace_back(line);
    }
    inputFile.close();

    int nb=0;

    std::vector<std::string> columns;

    for(auto& string : lignes) {
        nb += searchInString(string);

        for(int i=0; i<string.size(); ++i) {
            if(columns.size()<=i) columns.emplace_back("");
            columns[i]+=string[i];
        }
    }

    for(auto& string : columns) {
        nb += searchInString(string);
    }

    std::vector<std::string> diagonals;
    // Diagonals from top left to bottom right only top starters
    for(int i=0; i<lignes.size(); ++i) {
        std::string diagonal;
        for(int j=0; j<lignes.size()-i; ++j) {
            diagonal+=lignes[j][j+i];
        }
        diagonals.emplace_back(diagonal);
    }
    for(auto& string : diagonals) {
        nb += searchInString(string);
    }
    diagonals.clear();

    // Diagonals from top left to bottom right only left starters
    for(int i=1; i<lignes.size(); ++i) {
        std::string diagonal;
        for(int j=0; j<lignes.size()-i; ++j) {
            diagonal+=lignes[j+i][j];
        }
        diagonals.emplace_back(diagonal);
    }
    for(auto& string : diagonals) {
        nb += searchInString(string);
    }
    diagonals.clear();

    // Diagonals from top right to bottom left only top starters
    for(int i=0; i<lignes.size(); ++i) {
        std::string diagonal;
        for(int j=0; j<=i; ++j) {
            diagonal+=lignes[j][i-j];
        }
        diagonals.emplace_back(diagonal);
    }
    for(auto& string : diagonals) {
        nb += searchInString(string);
    }
    diagonals.clear();

    // Diagonals from top right to bottom left only right starters
    for(int i=1; i<lignes.size(); ++i) {
        std::string diagonal;
        for(int j=0; j<lignes.size()-i; ++j) {
            diagonal+=lignes[j+i][lignes.size()-1-j];
        }
        diagonals.emplace_back(diagonal);
    }
    for(auto& string : diagonals) {
        nb += searchInString(string);
    }
    diagonals.clear();

    std::cout << nb << std::endl;

    return 0;
}
*/

bool foundMaS(std::vector<std::string>& grid, int i, int j){
    if(grid[i+1][j+1]!='A') return false;
    std::string x;
    x+= grid[i][j];
    x+= grid[i][j+2];
    x+= grid[i+2][j];
    x+= grid[i+2][j+2];
    if(x=="MMSS") return true;
    if(x=="SSMM") return true;
    if(x=="SMSM") return true;
    if(x=="MSMS") return true;
    return false;
}

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<std::string> lignes;

    std::string line;
    while (getline (inputFile, line)) {
        if(line.at(line.size()-1) == '\r') line.pop_back();
        lignes.emplace_back(line);
    }
    inputFile.close();

    int nb=0;

    for(int i=0; i<lignes.size()-2; ++i){
        for(int j=0; j<lignes[i].size(); ++j){
            if(lignes[i][j]=='S' || lignes[i][j]=='M'){
                nb+= foundMaS(lignes, i, j);
            }
        }
    }

    std::cout << nb << std::endl;

    return 0;
}