#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>
#include <valarray>

enum Operation{
    ADD =0,
    MUL =1,
    CONCAT =2,
};

long long applyPattern(std::vector<long long> const& values, std::vector<Operation>& pattern){
    long long res = values[0];
    for(int i = 1; i < values.size(); ++i){
        switch (pattern[i-1]) {
            case Operation::ADD :
                res += values[i];
                break;
            case Operation::MUL:
                res *= values[i];
                break;
            case Operation::CONCAT:
                std::string str = std::to_string(res) + std::to_string(values[i]);
                res = std::stoll(str);
                break;
        }
    }
    return res;
}

void updatePattern(std::vector<Operation>& pattern){
    int i = 0;
    while(i < pattern.size() && pattern[i]==Operation::CONCAT){
        pattern[i] = Operation::ADD;
        ++i;
    }
    if(i < pattern.size()){
        if(pattern[i] == Operation::ADD){
            pattern[i] = Operation::MUL;
        }else{
            pattern[i] = Operation::CONCAT;
        }
    }
}

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::map<long long, std::vector<long long>> values;

    std::string line;
    while(getline(inputFile,line)){
        std::regex regex("\\d+");

        std::sregex_iterator it(line.begin(), line.end(), regex);
        std::sregex_iterator end;

        long long referenceValue = std::stoll(it->str());
        values.emplace(referenceValue, std::vector<long long>());
        ++it;

        while (it != end) {
            values[referenceValue].push_back(std::stoll(it->str()));
            ++it;
        }
    }

    inputFile.close();

    long long res = 0;
    for(auto const& [key, value] : values){
        std::vector<Operation> pattern(value.size()-1,Operation::ADD);
        std::vector<Operation> patternEnd(value.size()-1,Operation::CONCAT);
        while(pattern != patternEnd){
            if(applyPattern(value, pattern) == key){
                res += key;
                break;
            }
            updatePattern(pattern);
        }
        if(pattern == patternEnd && applyPattern(value, pattern) == key) {
            res += key;
        }
    }

    std::cout << res << std::endl;

    return 0;
}

//optimisation: we can make 'a tree' of all the possible patterns and then check if the value is in the tree
//the tree start with the 3 first results of the 3 operations between the 2 first values