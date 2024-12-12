#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef struct{
    int x;
    int y;
}Point;

enum Direction{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

typedef struct{
    Point position;
    Direction direction;
}Wall;

unsigned long long foundNumberOfWall(std::vector<std::string> &grid, std::vector<Point> &members){
    std::vector<Wall> walls;
    for(Point member : members){
        if(member.x - 1 < 0 || grid[member.x - 1][member.y] != grid[member.x][member.y]){
            walls.push_back({member, UP});
        }
        if(member.y + 1 >= grid[member.x].size() || grid[member.x][member.y + 1] != grid[member.x][member.y]){
            walls.push_back({member, RIGHT});
        }
        if(member.x + 1 >= grid.size() || grid[member.x + 1][member.y] != grid[member.x][member.y]){
            walls.push_back({member, DOWN});
        }
        if(member.y - 1 < 0 || grid[member.x][member.y - 1] != grid[member.x][member.y]){
            walls.push_back({member, LEFT});
        }
    }
    //sort walls by direction and position
    sort(walls.begin(), walls.end(), [](Wall &a, Wall &b){
        if(a.direction == b.direction) {
            switch (a.direction){
                case UP:
                    if(a.position.x != b.position.x) return a.position.x < b.position.x;
                    return a.position.y < b.position.y;
                case RIGHT:
                    if(a.position.y != b.position.y) return a.position.y < b.position.y;
                    return a.position.x < b.position.x;
                case DOWN:
                    if(a.position.x != b.position.x) return a.position.x < b.position.x;
                    return a.position.y < b.position.y;
                case LEFT:
                    if(a.position.y != b.position.y) return a.position.y < b.position.y;
                    return a.position.x < b.position.x;
            }
        }
        return a.direction < b.direction;
    });
    int nbOfWall = 0;
    for(int i = 0; i < walls.size(); i++){
        if(i == 0){
            nbOfWall++;
        }else{
            switch (walls[i].direction){
                case UP:
                    if(walls[i - 1].direction != UP) { nbOfWall++; break;}
                    if(walls[i - 1].position.x != walls[i].position.x) { nbOfWall++; break;}
                    if(walls[i - 1].position.y != walls[i].position.y - 1) { nbOfWall++; break;}
                    break;
                case RIGHT:
                    if(walls[i - 1].direction != RIGHT) { nbOfWall++; break;}
                    if(walls[i - 1].position.y != walls[i].position.y) { nbOfWall++; break;}
                    if(walls[i - 1].position.x != walls[i].position.x - 1) { nbOfWall++; break;}
                    break;
                case DOWN:
                    if(walls[i - 1].direction != DOWN) { nbOfWall++; break;}
                    if(walls[i - 1].position.x != walls[i].position.x) { nbOfWall++; break;}
                    if(walls[i - 1].position.y != walls[i].position.y - 1) { nbOfWall++; break;}
                    break;
                case LEFT:
                    if(walls[i - 1].direction != LEFT) { nbOfWall++; break;}
                    if(walls[i - 1].position.y != walls[i].position.y) { nbOfWall++; break;}
                    if(walls[i - 1].position.x != walls[i].position.x - 1) { nbOfWall++; break;}
                    break;
            }
        }
    }

    return nbOfWall;
}

unsigned long long foundArea(std::vector<std::string> &grid, std::vector<std::vector<bool>> &visited, int i, int j, char sign, std::vector<Point> &members){
    if(i < 0 || i >= grid.size()) return 0;
    if(j < 0 || j >= grid[i].size()) return 0;
    if(visited[i][j]) return 0;
    if(grid[i][j] != sign) return 0;
    visited[i][j] = true;
    members.push_back({i, j});
    return 1 + foundArea(grid, visited, i - 1, j, sign, members) + foundArea(grid, visited, i, j + 1, sign, members) + foundArea(grid, visited, i + 1, j, sign, members) + foundArea(grid, visited, i, j - 1, sign, members);
}

unsigned long long foundArea(std::vector<std::string> &grid, std::vector<std::vector<bool>> &visited, int i, int j, std::vector<Point> &members){
    return foundArea(grid, visited, i, j, grid[i][j], members);
}

int main() {
    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<std::string> grid;

    std::string line;
    while(getline(inputFile, line)){
        grid.push_back(line);
    }

    unsigned long long sum = 0;
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(!visited[i][j]){
                std::vector<Point> members;
                unsigned long long area = foundArea(grid, visited, i, j, members);
                unsigned long long nbOfWall = foundNumberOfWall(grid, members);
                sum+= area * nbOfWall;
                std::cout << grid[i][j] << " : Area: " << area << " nbOfWall: " << nbOfWall << std::endl;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}

/* Part 1
#include <iostream>
#include <fstream>
#include <vector>

typedef struct{
    int x;
    int y;
}Point;

unsigned long long foundPerimeter(std::vector<std::string> &grid, std::vector<Point> &members){
    int perimeter = 0;
    for(Point member : members){
        if(member.x - 1 < 0 || grid[member.x - 1][member.y] != grid[member.x][member.y]){
            perimeter++;
        }
        if(member.y + 1 >= grid[member.x].size() || grid[member.x][member.y + 1] != grid[member.x][member.y]){
            perimeter++;
        }
        if(member.x + 1 >= grid.size() || grid[member.x + 1][member.y] != grid[member.x][member.y]){
            perimeter++;
        }
        if(member.y - 1 < 0 || grid[member.x][member.y - 1] != grid[member.x][member.y]){
            perimeter++;
        }
    }
    return perimeter;
}

unsigned long long foundArea(std::vector<std::string> &grid, std::vector<std::vector<bool>> &visited, int i, int j, char sign, std::vector<Point> &members){
    if(i < 0 || i >= grid.size()) return 0;
    if(j < 0 || j >= grid[i].size()) return 0;
    if(visited[i][j]) return 0;
    if(grid[i][j] != sign) return 0;
    visited[i][j] = true;
    members.push_back({i, j});
    return 1 + foundArea(grid, visited, i - 1, j, sign, members) + foundArea(grid, visited, i, j + 1, sign, members) + foundArea(grid, visited, i + 1, j, sign, members) + foundArea(grid, visited, i, j - 1, sign, members);
}

unsigned long long foundArea(std::vector<std::string> &grid, std::vector<std::vector<bool>> &visited, int i, int j, std::vector<Point> &members){
    return foundArea(grid, visited, i, j, grid[i][j], members);
}

int main() {
    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<std::string> grid;

    std::string line;
    while(getline(inputFile, line)){
        grid.push_back(line);
    }

    unsigned long long sum = 0;
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(!visited[i][j]){
                std::vector<Point> members;
                unsigned long long area = foundArea(grid, visited, i, j, members);
                unsigned long long perimeter = foundNumberOfWall(grid, members);
                sum+= area * perimeter;
                std::cout << grid[i][j] << " : Area: " << area << " Perimeter: " << perimeter << std::endl;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
*/