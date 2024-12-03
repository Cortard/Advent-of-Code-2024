#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cstring>

int doMultiplication(std::string numberSearchZone){
    int numbers[2];
    std::regex numberRegex(R"([0-9]{1,3})");
    std::smatch numberMatchResult;
    std::regex_search(numberSearchZone,numberMatchResult,numberRegex);

    numbers[0]=stoi(numberMatchResult.str());
    numberSearchZone = numberMatchResult.suffix().str();
    std::regex_search(numberSearchZone,numberMatchResult,numberRegex);
    numbers[1]=stoi(numberMatchResult.str());

    return numbers[0]*numbers[1];
}

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    int sum=0;

    std::string line;
    // part 1 : std::regex regex(R"(mul\([0-9]{1,3}\,[0-9]{1,3}\))");
    std::regex regex(R"((mul\([0-9]{1,3}\,[0-9]{1,3}\))|(do\(\))|(don\'t\(\)))");
    std::smatch matchResult;

    bool doing = true;
    while (getline (inputFile, line)) {

        while (std::regex_search(line, matchResult, regex)){

            std::string resultType = matchResult.str().substr(0,3);
            if(resultType=="do(") doing=true;
            else if(resultType=="don") doing=false;
            else if(doing) sum+= doMultiplication(matchResult.str());

            line = matchResult.suffix().str();
        }
    }
    inputFile.close();

    std::cout<<sum<<std::endl;

    return 0;
}
