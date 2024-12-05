#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

bool isValid(std::vector<std::pair<int,int>>& rules, std::vector<std::map<int,int>>& pages, int i){
    bool valid = true;
    for (auto &rule: rules) {
        if (pages[i].find(rule.first) != pages[i].end() && pages[i].find(rule.second) != pages[i].end()) {
            if (pages[i][rule.first] > pages[i][rule.second]) {
                valid = false;
                break;
            }
        }
    }
    return valid;
}

void fixPage(std::vector<std::pair<int,int>>& rules, std::vector<std::map<int,int>>& pages, std::vector<std::vector<int>>& pagesVector, int i){
    for (auto &rule: rules) {
        if (pages[i].find(rule.first) != pages[i].end() && pages[i].find(rule.second) != pages[i].end()) {
            if (pages[i][rule.first] > pages[i][rule.second]) {
                //swap
                int temp = pagesVector[i][pages[i][rule.first]];
                pagesVector[i][pages[i][rule.first]] = pagesVector[i][pages[i][rule.second]];
                pagesVector[i][pages[i][rule.second]] = temp;
                int tempIndex = pages[i][rule.first];
                pages[i][rule.first] = pages[i][rule.second];
                pages[i][rule.second] = tempIndex;
            }
        }
    }
}

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<std::pair<int,int>> rules;

    std::string line;
    while (getline (inputFile, line) ) {
        std::istringstream ss(line);
        std::string leftNumber, rightNumber;
        int pair[2];
        if (std::getline(ss, leftNumber, '|') && std::getline(ss, rightNumber)) {
            pair[0] = std::stoi(leftNumber); // Convert first part to int
            pair[1] = std::stoi(rightNumber); // Convert second part to int
            rules.emplace_back(pair[0], pair[1]);
        } else {
            break;
        }
    }

    std::vector<std::map<int,int>> pages;
    std::vector<std::vector<int>> pagesVector;
    int i=0;
    while (getline (inputFile, line) ) {
        std::istringstream ss(line);
        std::string number;
        int j=0;
        while(std::getline(ss, number, ',')){
            if(j==0){
                std::map<int,int> page;
                page[std::stoi(number)] = j;
                pages.push_back(page);
                std::vector<int> pageVector;
                pageVector.push_back(std::stoi(number));
                pagesVector.push_back(pageVector);
            } else {
                pages[i][std::stoi(number)] = j;
                pagesVector[i].push_back(std::stoi(number));
            }
            j++;
        }
        i++;
    }

    inputFile.close();

    int sum = 0;
    for(i=0; i<pages.size(); i++){
        if(!isValid(rules, pages, i)){
            while (!isValid(rules, pages, i)) fixPage(rules, pages, pagesVector, i);
            sum += pagesVector[i][pagesVector[i].size()/2];
        }
    }

    std::cout << sum << std::endl;

    return 0;
}

/*
Part 1 :
    int sum = 0;
    for(i=0; i<pages.size(); i++){
        bool valid = true;
        for(auto &rule : rules){
            if(pages[i].find(rule.first) != pages[i].end() && pages[i].find(rule.second) != pages[i].end()){
                if (pages[i][rule.first] > pages[i][rule.second]) {
                    valid = false;
                    break;
                }
            }
        }
        if(valid){
            sum += pagesVector[i][pagesVector[i].size()/2];
        }
    }
*/