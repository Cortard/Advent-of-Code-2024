#include <iostream>
#include <fstream>
#include <regex>

#define ll long long

typedef struct {
    ll x[3];
    ll y[3];
} Party;

int main() {
    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<Party> parties;

    std::string line;
    while(getline(inputFile, line)){
        std::regex regex(R"(\d+)");
        std::regex_iterator<std::string::iterator> resultIterator(line.begin(), line.end(), regex);

        Party party;
        party.x[0] = std::stoi(resultIterator->str());
        resultIterator++;
        party.y[0] = std::stoi(resultIterator->str());

        getline(inputFile, line);
        resultIterator = std::regex_iterator<std::string::iterator>(line.begin(), line.end(), regex);
        party.x[1] = std::stoi(resultIterator->str());
        resultIterator++;
        party.y[1] = std::stoi(resultIterator->str());

        getline(inputFile, line);
        resultIterator = std::regex_iterator<std::string::iterator>(line.begin(), line.end(), regex);
        party.x[2] = std::stoi(resultIterator->str());
        resultIterator++;
        party.y[2] = std::stoi(resultIterator->str());

        getline(inputFile, line);

        party.x[2]+=10000000000000;
        party.y[2]+=10000000000000;

        parties.push_back(party);
    }

    ll credit = 0;
    for(auto party : parties){
        ll  determinant = party.x[0]*party.y[1] - party.y[0]*party.x[1];
        if(determinant!=0){
            ll a = (party.x[2]*party.y[1] - party.y[2]*party.x[1])/determinant;
            ll b = (party.x[0]*party.y[2] - party.y[0]*party.x[2])/determinant;

            if(party.x[0]*a + party.x[1]*b == party.x[2] && party.y[0]*a + party.y[1]*b == party.y[2]) 
                credit += a * 3 + b;
        }
    }

    std::cout<<credit<<std::endl;

    return 0;
}

/* Part 1
typedef struct {
    int x[3];
    int y[3];
} Party;

int main() {
    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<Party> parties;

    std::string line;
    while(getline(inputFile, line)){
        std::regex regex(R"(\d+)");
        std::regex_iterator<std::string::iterator> resultIterator(line.begin(), line.end(), regex);

        Party party;
        party.x[0] = std::stoi(resultIterator->str());
        resultIterator++;
        party.y[0] = std::stoi(resultIterator->str());

        getline(inputFile, line);
        resultIterator = std::regex_iterator<std::string::iterator>(line.begin(), line.end(), regex);
        party.x[1] = std::stoi(resultIterator->str());
        resultIterator++;
        party.y[1] = std::stoi(resultIterator->str());

        getline(inputFile, line);
        resultIterator = std::regex_iterator<std::string::iterator>(line.begin(), line.end(), regex);
        party.x[2] = std::stoi(resultIterator->str());
        resultIterator++;
        party.y[2] = std::stoi(resultIterator->str());

        getline(inputFile, line);

        parties.push_back(party);
    }

    unsigned long long credit = 0;
    for(auto party : parties){
        int  determinant = party.x[0]*party.y[1] - party.y[0]*party.x[1];
        if(determinant!=0){
            int a = (party.x[2]*party.y[1] - party.y[2]*party.x[1])/determinant;
            int b = (party.x[0]*party.y[2] - party.y[0]*party.x[2])/determinant;

            if(party.x[0]*a + party.x[1]*b == party.x[2] && party.y[0]*a + party.y[1]*b == party.y[2])
                credit+= a*3 + b;
        }
    }

    std::cout<<credit<<std::endl;

    return 0;
}
*/