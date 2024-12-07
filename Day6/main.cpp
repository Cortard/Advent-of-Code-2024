#include <iostream>
#include <fstream>
#include <vector>
#include <map>

struct Coordinates {
    int x;
    int y;
    Coordinates(int x, int y) : x(x), y(y) {}
    inline bool operator< (const Coordinates& co) const { return x < co.x || (x == co.x && y < co.y); }
};

bool nextIsInGrid(std::vector<std::string> &grid, Coordinates &coordinates, int direction) {
    switch (direction) {
        case 0:
            if (coordinates.x - 1 < 0) return false;
            break;
        case 1:
            if (coordinates.y + 1 >= grid[0].size()) return false;
            break;
        case 2:
            if (coordinates.x + 1 >= grid.size()) return false;
            break;
        case 3:
            if (coordinates.y - 1 < 0) return false;
            break;
    }
    return true;
}

Coordinates getNextCoordinates(Coordinates &coordinates, int direction) {
    switch (direction) {
        case 0:
            return {coordinates.x - 1, coordinates.y};
        case 1:
            return {coordinates.x, coordinates.y + 1};
        case 2:
            return {coordinates.x + 1, coordinates.y};
        case 3:
            return {coordinates.x, coordinates.y - 1};
    }
}

char getNextCase(std::vector<std::string> &grid, Coordinates &coordinates, int direction) {
    switch (direction) {
        case 0:
            return grid[coordinates.x-1][coordinates.y];
        case 1:
            return grid[coordinates.x][coordinates.y+1];
        case 2:
            return grid[coordinates.x+1][coordinates.y];
        case 3:
            return grid[coordinates.x][coordinates.y-1];
    }
}

bool compareCoordinates(Coordinates &c1, Coordinates &c2) {
    return c1.x == c2.x && c1.y == c2.y;
}

void move(std::vector<std::string> &grid, Coordinates &coordinates, int & direction, std::map<Coordinates,int*>& visited) {
    if(getNextCase(grid,coordinates,direction)=='#'){
        Coordinates nextCoordinates = getNextCoordinates(coordinates,direction);
        if(visited.find(nextCoordinates)==visited.end()){
            int* values = new int[4];
            for (int i = 0; i < 4; ++i) values[i]=0;
            visited.insert({nextCoordinates,values});
            values[direction]=1;
        }
        direction = (direction+1)%4;
        return;
    }
    switch (direction) {
        case 0:
            --coordinates.x;
            break;
        case 1:
            ++coordinates.y;
            break;
        case 2:
            ++coordinates.x;
            break;
        case 3:
            --coordinates.y;
            break;
    }
}

bool makeALoop(std::vector<std::string> &grid, Coordinates& coordinate, std::pair<Coordinates,int*> vst, int direction){
    switch (direction) {
        case 0 :
            if(!vst.second[(0+1)%4]) break;
            if(coordinate.x == vst.first.x && coordinate.y < vst.first.y){
                bool nothingBetween = true;
                for(int i = coordinate.y+1; i<vst.first.y; ++i){
                    if(grid[coordinate.x][i]=='#'){
                        nothingBetween = false;
                        break;
                    }
                }
                return nothingBetween;
            }
            break;
        case 1 :
            if(!vst.second[(1+1)%4]) break;
            if(coordinate.y == vst.first.y && coordinate.x < vst.first.x){
                bool nothingBetween = true;
                for(int i = vst.first.x+1; i<coordinate.x; ++i){
                    if(grid[i][coordinate.y]=='#'){
                        nothingBetween = false;
                        break;
                    }
                }
                return nothingBetween;
            }
            break;
        case 2 :
            if(!vst.second[(2+1)%4]) break;
            if(coordinate.x == vst.first.x && coordinate.y > vst.first.y){
                bool nothingBetween = true;
                for(int i = vst.first.y+1; i<coordinate.y; ++i){
                    if(grid[coordinate.x][i]=='#'){
                        nothingBetween = false;
                        break;
                    }
                }
                return nothingBetween;
            }
            break;
        case 3 :
            if(!vst.second[(3+1)%4]) break;
            if(coordinate.y == vst.first.y && coordinate.x > vst.first.x){
                bool nothingBetween = true;
                for(int i = coordinate.x+1; i<vst.first.x; ++i){
                    if(grid[i][coordinate.y]=='#'){
                        nothingBetween = false;
                        break;
                    }
                }
                return nothingBetween;
            }
            break;
    }
    return false;
}

int main() {

    //std::ifstream inputFile("./../input.txt");
    std::ifstream inputFile("./../example.txt");

    std::vector<std::string> grid;
    Coordinates coordinate(0,0);
    char starter='.';

    std::string line;
    while(getline(inputFile,line)){
        grid.emplace_back(line);
        if(starter=='.') {
            coordinate.x ++;
            coordinate.y= 0;
            for (char car: line) {
                if (car == '^' || car == 'v' || car == '<' || car == '>') {
                    starter = car;
                    break;
                }
                coordinate.y++;
            }
        }
    }

    std::cout<<coordinate.x<<" "<<coordinate.y<<std::endl;
    std::cout<<std::endl;

    int direction;
    switch (starter) {
        case '^' :
            direction = 0;
            break;
        case '>' :
            direction = 1;
            break;
        case 'v' :
            direction = 2;
            break;
        case '<' :
            direction = 3;
            break;
    }

    std::map<Coordinates,int*> visited={};

    int sum=0;
    while(nextIsInGrid(grid,coordinate,direction)){
        Coordinates nextCoordinate = getNextCoordinates(coordinate,direction);
        if(grid[nextCoordinate.x][nextCoordinate.y]=='.' || grid[nextCoordinate.x][nextCoordinate.y]=='^' || grid[nextCoordinate.x][nextCoordinate.y]=='v' || grid[nextCoordinate.x][nextCoordinate.y]=='<' || grid[nextCoordinate.x][nextCoordinate.y]=='>'){
            for(auto &vst: visited){
                if(makeALoop(grid,coordinate,vst,direction)){
                    grid[nextCoordinate.x][nextCoordinate.y]='O';
                    ++sum;
                }
            }
        }

        move(grid,coordinate,direction, visited);
    }

    for(auto &vst: visited){
        delete[] vst.second;
    }

    for(auto &row: grid){
        std::cout << row << std::endl;
    }

    std::cout << sum << std::endl;

    return 0;
}

/* Part 1 :
    int sum=0;
    while(nextIsInGrid(grid,coordinate,direction)){
        if(grid[coordinate.x][coordinate.y]!='X'){
            grid[coordinate.x][coordinate.y]='X';
            ++sum;
        }
        move(grid,coordinate,direction);
    }

    std::cout << sum << std::endl;
*/