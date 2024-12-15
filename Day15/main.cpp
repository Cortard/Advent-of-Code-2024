#include <iostream>
#include <fstream>
#include <vector>

typedef struct {
    int x;
    int y;
} Point;

bool moveBox(Point position1, int direction, std::vector<std::string> &grid){
    Point position2 = {position1.x, position1.y};
    if(grid[position1.x][position1.y] == '[') position2.y++;
    else position1.y--;

    Point newPosition1 = {position1.x + direction, position1.y};
    Point newPosition2 = {position2.x + direction, position2.y};

    if(grid[newPosition1.x][newPosition1.y] == '#' || grid[newPosition2.x][newPosition2.y] == '#') return false;

    std::vector<std::string> newGrid = grid;
    bool valid1 = newGrid[newPosition1.x][newPosition1.y] == '.' || moveBox(newPosition1, direction, newGrid);
    bool valid2 = newGrid[newPosition2.x][newPosition2.y] == '.' || moveBox(newPosition2, direction, newGrid);
    if(valid1 && valid2){
        grid=newGrid;
        grid[newPosition1.x][newPosition1.y] = grid[position1.x][position1.y];
        grid[position1.x][position1.y] = '.';
        grid[newPosition2.x][newPosition2.y] = grid[position2.x][position2.y];
        grid[position2.x][position2.y] = '.';
        return true;
    }
    return false;
}

bool moveRobot(char move, Point &position, std::vector<std::string> &grid){
    int direction[2] = {0,0};
    switch (move) {
        case '^' :
            direction[0] = -1;
            break;
        case 'v' :
            direction[0] = 1;
            break;
        case '<' :
            direction[1] = -1;
            break;
        case '>' :
            direction[1] = 1;
            break;
    }

    if(direction[1]!=0) {
        Point newPosition = {position.x + direction[0], position.y + direction[1]};
        while (grid[newPosition.x][newPosition.y] != '#' && grid[newPosition.x][newPosition.y] != '.') {
            newPosition.x += direction[0];
            newPosition.y += direction[1];
        }
        if (grid[newPosition.x][newPosition.y] == '#') return false;
        while (newPosition.x != position.x || newPosition.y != position.y) {
            grid[newPosition.x][newPosition.y] = grid[newPosition.x - direction[0]][newPosition.y - direction[1]];
            newPosition.x -= direction[0];
            newPosition.y -= direction[1];
        }

        grid[position.x][position.y] = '.';
        position.x += direction[0];
        position.y += direction[1];
        return true;
    } else {
        Point newPosition = {position.x + direction[0], position.y + direction[1]};
        if(grid[newPosition.x][newPosition.y] == '#') return false;
        if(grid[newPosition.x][newPosition.y] == '.' || moveBox(newPosition, direction[0], grid)){
            grid[newPosition.x][newPosition.y] = grid[position.x][position.y];
            grid[position.x][position.y] = '.';
            position.x += direction[0];
            position.y += direction[1];
            return true;
        }
        return false;
    }
}

int main() {
    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<std::string> grid;
    std::string line;
    while(std::getline(inputFile, line)) {
        if(line.empty()) break;
        std::string newLine;
        for(auto c : line){
            if(c=='#') newLine += "##";
            else if(c=='O') newLine += "[]";
            else if(c=='@') newLine += "@.";
            else newLine += "..";
        }
        grid.push_back(newLine);
    }

    Point position = {0, 0};
    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[i].size(); j++){
            if(grid[i][j] == '@') {
                position = {i, j};
                break;
            }
        }
    }

    std::string moves;
    while(std::getline(inputFile,line)) {
        moves += line;
    }

    for(char move : moves){
        moveRobot(move, position, grid);
    }

    for(auto& row : grid) std::cout << row << std::endl; std::cout << std::endl;

    unsigned long long sum=0;
    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[i].size(); j++){
            if(grid[i][j] == '[') sum+=100*i+j;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}

/* Part 1
#include <iostream>
#include <fstream>
#include <vector>

typedef struct {
    int x;
    int y;
} Point;

bool moveRobot(char move, Point &position, std::vector<std::string> &grid){
    int direction[2] = {0,0};
    switch (move) {
        case '^' :
            direction[0] = -1;
            break;
        case 'v' :
            direction[0] = 1;
            break;
        case '<' :
            direction[1] = -1;
            break;
        case '>' :
            direction[1] = 1;
            break;
    }

    Point newPosition = {position.x + direction[0], position.y + direction[1]};
    while(grid[newPosition.x][newPosition.y] != '#' && grid[newPosition.x][newPosition.y] != '.'){
        newPosition.x += direction[0];
        newPosition.y += direction[1];
    }
    if(grid[newPosition.x][newPosition.y] == '#') return false;
    while(newPosition.x != position.x || newPosition.y != position.y){
        grid[newPosition.x][newPosition.y] = grid[newPosition.x - direction[0]][newPosition.y - direction[1]];
        newPosition.x -= direction[0];
        newPosition.y -= direction[1];
    }

    grid[position.x][position.y] = '.';
    position.x += direction[0];
    position.y += direction[1];
    return true;
}

int main() {
    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<std::string> grid;
    Point position = {0, 0};

    std::string line;
    bool foundStart = false;
    while(std::getline(inputFile, line)) {
        if(line.empty()) break;
        grid.push_back(line);
        if(!foundStart){
            position.y=0;
            for(char c : line){
                if(c == '@') {
                    foundStart = true;
                    break;
                }
                position.y++;
            }
            if(!foundStart) position.x++;
        }
    }

    std::string moves;
    while(std::getline(inputFile,line)) {
        moves += line;
    }

    for(char move : moves){
        moveRobot(move, position, grid);
    }

    unsigned long long sum=0;
    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[i].size(); j++){
            if(grid[i][j] == 'O') sum+=100*i+j;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
 */