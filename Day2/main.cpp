#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool checkData(std::vector<int>& data){
    bool sign = data[0] < data[1];
    for(int i=0; i<data.size()-1; i++)
        if( (data[i] < data[i+1]) != sign
            || data[i] == data[i+1]
            || abs(data[i] - data[i+1]) > 3 ) return false;
    return true;
}

bool checkAllData(std::vector<int>& data){
    if (checkData(data)) return true;

    for(int i=0; i<data.size(); i++){
        std::vector<int> cp = data;
        cp.erase(cp.begin()+i);
        if (checkData(cp)) return true;
    }

    return false;
}

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::string line;
    std::vector<int> data;
    int safe = 0;
    while (getline (inputFile, line)) {
        std::stringstream stream(line);
        int v;
        while (stream >> v) data.push_back(v);

        safe+= checkAllData(data);

        data.clear();
    }

    inputFile.close();

    std::cout << safe << std::endl;

    return 0;
}

//354