#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

#define uint64 uint64_t

#define empty -1

void displayMemory(const std::vector<uint64>& memory) {
    for (uint64 i : memory) {
        if(i!=empty) std::cout << i;
        else std::cout << ".";
    }std::cout << std::endl;
}

void swap(uint64& a, uint64& b) {
    uint64 temp = a;
    a = b;
    b = temp;
}

size_t getSizeOfData(const std::vector<uint64>& memory, size_t right) {
    uint64 id = memory[right];
    size_t length = 0;
    while(memory[right] != empty && memory[right] == id && right >= 0) {
        --right;
        ++length;
    }
    return length;
}

size_t getSizeOfGap(const std::vector<uint64>& memory, size_t left, size_t limit) {
    size_t length = 0;
    while(memory[left] == empty && left < limit) {
        ++left;
        ++length;
    }
    return length;
}

size_t foundGap(const std::vector<uint64>& memory, size_t right, size_t length) {
    size_t left = 0;
    bool continueSearch = true;
    while(left < right && continueSearch) {
        while(memory[left] != empty && left < right) ++left;
        size_t gap;
        if(left < right) gap = getSizeOfGap(memory, left, right);
        else gap = 0;
        if(gap >= length) continueSearch = false;
        else left += gap;
    }

    return left;
}

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<uint64> memory;

    std::string line;
    getline(inputFile, line);

    bool isData = true;
    uint64 id = 0;
    for (char i : line) {
        for(int j = 0; j < i-'0'; j++) {
            if (isData) {
                memory.push_back(id);
            } else {
                memory.push_back(empty);
            }
        }
        if(isData) ++id;
        isData = !isData;
    }

    size_t right = memory.size()-1;
    while(right > 9){
        if(memory[right] == empty) --right;
        else {
            size_t length = getSizeOfData(memory, right);
            size_t toFill = foundGap(memory, right, length);
            if(toFill != right) {
                for (size_t i = 0; i < length; i++) {
                    swap(memory[toFill+i], memory[right-i]);
                }
            }
            right = right - length;
        }
    }

    uint64 sum = 0;
    for (size_t i = 0; i < memory.size(); i++) {
        if(memory[i] != empty) sum += i*memory[i];
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}

/*Part 1:
    size_t left = 0;
    size_t right = memory.size()-1;
    while(left < right){
        while(memory[left] != empty) ++left;
        while(memory[right] == empty) --right;
        if(left < right) {
            swap(memory[left], memory[right]);
            ++left;
            --right;
        }
    }
*/