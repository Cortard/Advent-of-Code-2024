#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#define ull unsigned long long

int main() {
    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<ull> originalStones;

    std::string line;
    while(getline(inputFile, line)){
        size_t pos = 0;
        while((pos = line.find(' ')) != std::string::npos){
            originalStones.push_back(std::stoull(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }
        originalStones.push_back(std::stoull(line));
    }

    std::map<ull, ull> stones;
    for(auto stone : originalStones) stones.insert({stone, 1});

    for(int i=0; i<75; ++i){
        std::map<ull, ull> newStones;
        for(auto stone : stones){
            if(stone.first == 0){
                if(stones.find(1) != stones.end()) newStones[1] += stone.second;
                else newStones.insert({1, stone.second});
            } else if(std::to_string(stone.first).length()%2 == 0){
                std::string stoneStr = std::to_string(stone.first);
                ull firstHalf = std::stoull(stoneStr.substr(0, stoneStr.length() / 2));
                ull secondHalf = std::stoull(stoneStr.substr(stoneStr.length() / 2));
                if(newStones.find(firstHalf) != newStones.end()) newStones[firstHalf] += stone.second;
                else newStones.insert({firstHalf, stone.second});
                if(newStones.find(secondHalf) != newStones.end()) newStones[secondHalf] += stone.second;
                else newStones.insert({secondHalf, stone.second});
            } else {
                if(newStones.find(stone.first*2024) != newStones.end()) newStones[stone.first*2024] += stone.second;
                else newStones.insert({stone.first*2024, stone.second});
            }
        }
        stones = newStones;
        std::cout << "Iteration " << i+1 << " done." << std::endl;
    }

    ull count = 0;
    for(auto stone : stones) count += stone.second;
    std::cout << "The number of stones is: " << count << std::endl;

    return 0;
}

/* Part 1 : 186175
#define ull unsigned long long

void blink(std::vector<ull>& stones){
    std::vector<ull> newStones;
    for(ull stone : stones) {
        if(stone == 0){
            newStones.push_back(1);
        } else if(std::to_string(stone).length()%2 == 0){
            std::string stoneStr = std::to_string(stone);
            newStones.push_back(std::stoull(stoneStr.substr(0, stoneStr.length() / 2)));
            newStones.push_back(std::stoull(stoneStr.substr(stoneStr.length() / 2)));
        } else {
            newStones.push_back(stone*2024);
        }
    }
    stones = newStones;
}

int main() {
    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<ull> stones;

    std::string line;
    while(getline(inputFile, line)){
        size_t pos = 0;
        while((pos = line.find(' ')) != std::string::npos){
            stones.push_back(std::stoull(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }
        stones.push_back(std::stoull(line));
    }

    for(int i=0; i<25; ++i) blink(stones);

    std::cout << "The number of stones is: " << stones.size() << std::endl;

    return 0;
}
*/