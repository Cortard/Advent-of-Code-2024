#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>

enum opcode {
    adv = 0,
    bxl = 1,
    bst = 2,
    jnz = 3,
    bxc = 4,
    out = 5,
    bdv = 6,
    cdv = 7
};

enum registerName {
    A = 0,
    B = 1,
    C = 2
};

void readFile(std::ifstream &file, long long registerValues[], std::vector<long long> &instructions);

std::string execute(std::vector<long long> &instructions, long long registerValues[]);

bool foundInstruction(std::vector<long long> instructions, int i, long long min, long long max, long long& respond);

/* translate of the 'input' program in c++
do {
    output2 += std::to_string(((*a%8)^(long long)(*a >> ((*a%8)^7))) % 8) +  ",";
    *a = (int)(*a / 8);
} while (*a != 0);
 */

int main() {
    //std::ifstream file("./../example.txt");
    std::ifstream file("./../input.txt");
    long long registerValues[3];
    std::vector<long long> instructions;
    readFile(file, registerValues, instructions);

    long long max = LLONG_MAX; for(auto i : instructions) max/=8;
    long long respond;
    foundInstruction(instructions, (int)instructions.size()-1, 1, max, respond);
    std::cout << respond << std::endl;


    return 0;
}

void readFile(std::ifstream &file, long long registerValue[], std::vector<long long> &instructions) {
    std::string line;
    for (long long i = 0; i < 3; i++) {
        std::getline(file, line);
        std::regex regex(R"(\d+)");
        std::smatch match;
        std::regex_search(line, match, regex);
        registerValue[i] = std::stoi(match.str());
    }
    std::getline(file, line);
    std::getline(file, line);
    std::regex regex(R"(\d+)");
    std::smatch match;
    while (std::regex_search(line, match, regex)) {
        instructions.push_back(std::stoi(match.str()));
        line = match.suffix();
    }
}

std::string execute(std::vector<long long> &instructions, long long registerValues[]) {
    std::string output;
    for (long long i = 0; i < instructions.size(); i += 2) {
        auto instruction = (opcode) instructions[i];

        long long operand = instructions[i + 1];
        if (4 <= operand && operand <= 6) operand = registerValues[operand - 4];

        switch (instruction) {
            case adv: {
                long long numerator = registerValues[A];
                auto denominator = (long long) pow(2, (double)operand);
                registerValues[A] = numerator / denominator;
                break;
            }
            case bxl:
                registerValues[B] ^= operand;
                break;
            case bst:
                registerValues[B] = operand % 8;
                break;
            case jnz:
                if (registerValues[A] != 0) {
                    i = operand - 2;
                }
                break;
            case bxc:
                registerValues[B] ^= registerValues[C];
                break;
            case out :
                output += std::to_string(operand % 8) + ",";
                break;
            case bdv: {
                long long numerator = registerValues[A];
                auto denominator = (long long) pow(2, (double)operand);
                registerValues[B] = numerator / denominator;
                break;
            }
            case cdv: {
                long long numerator = registerValues[A];
                auto denominator = (long long) pow(2, (double)operand);
                registerValues[C] = numerator / denominator;
                break;
            }
        }
    }
    return output;
}

bool foundInstruction(std::vector<long long> instructions, int i, long long min, long long max, long long& respond){
    if(i < 0) return true;
    for(long long v = min; v <= max; ++v){
        if(((v%8)^(long long)(v>>((v%8)^7)))%8 == instructions[i]){
            if(i == 0){
                respond = v;
                return true;
            } else if(foundInstruction(instructions, i-1, v*8, (v+1)*8-1, respond)){
                return true;
            }
        }
    }
    return false;
}

/*  Part 1 :
#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>

enum opcode {
    adv = 0,
    bxl = 1,
    bst = 2,
    jnz = 3,
    bxc = 4,
    out = 5,
    bdv = 6,
    cdv = 7
};

enum registerName {
    A = 0,
    B = 1,
    C = 2
};

void readFile(std::ifstream &file, long long registerValues[], std::vector<long long> &instructions, std::string &program);

std::string execute(std::vector<long long> &instructions, long long registerValues[]);

int main() {
    //std::ifstream file("./../example.txt");
    std::ifstream file("./../input.txt");
    long long registerValues[3];
    std::vector<long long> instructions;
    std::string program;
    readFile(file, registerValues, instructions, program);

    std::string output = execute(instructions, registerValues);

    std::cout << output;
    return 0;
}

void readFile(std::ifstream &file, long long registerValue[], std::vector<long long> &instructions, std::string &program) {
    std::string line;
    for (long long i = 0; i < 3; i++) {
        std::getline(file, line);
        std::regex regex(R"(\d+)");
        std::smatch match;
        std::regex_search(line, match, regex);
        registerValue[i] = std::stoi(match.str());
    }
    std::getline(file, line);
    std::getline(file, line);
    program = line.substr(9);
    std::regex regex(R"(\d+)");
    std::smatch match;
    while (std::regex_search(line, match, regex)) {
        instructions.push_back(std::stoi(match.str()));
        line = match.suffix();
    }
}

std::string execute(std::vector<long long> &instructions, long long registerValues[]) {
    std::string output;
    for (long long i = 0; i < instructions.size(); i += 2) {
        auto instruction = (opcode) instructions[i];

        long long operand = instructions[i + 1];
        if (4 <= operand && operand <= 6) operand = registerValues[operand - 4];

        switch (instruction) {
            case adv: {
                long long numerator = registerValues[A];
                auto denominator = (long long) pow(2, operand);
                registerValues[A] = numerator / denominator;
                break;
            }
            case bxl:
                registerValues[B] ^= operand;
                break;
            case bst:
                registerValues[B] = operand % 8;
                break;
            case jnz:
                if (registerValues[A] != 0) {
                    i = operand - 2;
                }
                break;
            case bxc:
                registerValues[B] ^= registerValues[C];
                break;
            case out :
                output += std::to_string(operand % 8) + ",";
                break;
            case bdv: {
                long long numerator = registerValues[A];
                auto denominator = (long long) pow(2, operand);
                registerValues[B] = numerator / denominator;
                break;
            }
            case cdv: {
                long long numerator = registerValues[A];
                auto denominator = (long long) pow(2, operand);
                registerValues[C] = numerator / denominator;
                break;
            }
        }
    }
    return output;
}
*/