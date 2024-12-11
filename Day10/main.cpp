#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

struct Point{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<std::vector<int>> grid;
    std::vector<Point> toDo;

    std::string line;
    int x = 0;
    while(getline(inputFile, line)){
        std::vector<int> lineInt;
        for(char c : line){
            lineInt.emplace_back(c-'0');
        }
        grid.emplace_back(lineInt);

        for(int y=0; y < line.size(); y++){
            if(line[y] == '0'){
                toDo.emplace_back(x, y);
            }
        }
        ++x;
    }

    unsigned long long count = 0;
    while(!toDo.empty()){

        Point p = toDo.back();
        toDo.pop_back();

        int value = grid[p.x][p.y];
        std::vector<Point> newEnds;
        if(p.x>0 && grid[p.x-1][p.y] == value + 1){
            if(value!=8) toDo.emplace_back(p.x-1, p.y);
            else ++count;
        }
        if(p.x<grid.size()-1 && grid[p.x+1][p.y] == value + 1){
            if(value!=8) toDo.emplace_back(p.x+1, p.y);
            else ++count;
        }
        if(p.y>0 && grid[p.x][p.y-1] == value + 1){
            if(value!=8) toDo.emplace_back(p.x, p.y-1);
            else ++count;
        }
        if(p.y<grid[0].size()-1 && grid[p.x][p.y+1] == value + 1){
            if(value!=8) toDo.emplace_back(p.x, p.y+1);
            else ++count;
        }

    }

    std::cout << count << std::endl;

    return 0;
}

/* Part 1:
struct Point{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

struct Task{
    Point position;
    Point origin;
    Task(Point position, Point origin) : position(position), origin(origin) {}
};

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<std::vector<int>> grid;
    std::vector<Task> toDo;

    std::string line;
    int x = 0;
    while(getline(inputFile, line)){
        std::vector<int> lineInt;
        for(char c : line){
            lineInt.emplace_back(c-'0');
        }
        grid.emplace_back(lineInt);

        for(int y=0; y < line.size(); y++){
            if(line[y] == '0'){
                toDo.emplace_back(Point(x, y), Point(x, y));
            }
        }
        ++x;
    }

    std::map<Point, std::vector<Point>> trailheads;

    unsigned long long count = 0;
    while(!toDo.empty()){
        Task t = toDo.back();
        toDo.pop_back();

        Point p = t.position;
        int value = grid[p.x][p.y];
        std::vector<Point> newEnds;
        if(p.x>0 && grid[p.x-1][p.y] == value + 1){
            if(value!=8) toDo.emplace_back(Point(p.x-1, p.y), t.origin);
            else newEnds.emplace_back(p.x-1, p.y);
        }
        if(p.x<grid.size()-1 && grid[p.x+1][p.y] == value + 1){
            if(value!=8) toDo.emplace_back(Point(p.x+1, p.y), t.origin);
            else newEnds.emplace_back(p.x+1, p.y);
        }
        if(p.y>0 && grid[p.x][p.y-1] == value + 1){
            if(value!=8) toDo.emplace_back(Point(p.x, p.y-1), t.origin);
            else newEnds.emplace_back(p.x, p.y-1);
        }
        if(p.y<grid[0].size()-1 && grid[p.x][p.y+1] == value + 1){
            if(value!=8) toDo.emplace_back(Point(p.x, p.y+1), t.origin);
            else newEnds.emplace_back(p.x, p.y+1);
        }

        for(Point end : newEnds){
            if(trailheads.find(t.origin) == trailheads.end()){
                trailheads.insert(std::pair<Point, std::vector<Point>>(t.origin, std::vector<Point>()));
                trailheads[t.origin].emplace_back(end);
                ++count;
            }else{
                if(std::find(trailheads[t.origin].begin(), trailheads[t.origin].end(), end) == trailheads[t.origin].end()) {
                    trailheads[t.origin].emplace_back(end);
                    ++count;
                }
            }
        }
    }

    std::cout << count << std::endl;
}
*/