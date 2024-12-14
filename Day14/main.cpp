#include <iostream>
#include <fstream>
#include <regex>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point position;
    Point velocity;
} Robot;

void move(Robot& robot, Point& grid) {
    robot.position.x += robot.velocity.x;
    robot.position.y += robot.velocity.y;
    robot.position.x = (robot.position.x + grid.x) % grid.x;
    robot.position.y = (robot.position.y + grid.y) % grid.y;
}

bool findCluster(std::vector<Robot>& robots) {
    for(auto& robot : robots) {
        bool found[8]={false};
        for(auto& other : robots) {
            if(robot.position.x == other.position.x && robot.position.y == other.position.y) continue;
            if(robot.position.x == other.position.x && robot.position.y == other.position.y + 1) found[0] = true;
            if(robot.position.x == other.position.x && robot.position.y == other.position.y - 1) found[1] = true;
            if(robot.position.x == other.position.x + 1 && robot.position.y == other.position.y) found[2] = true;
            if(robot.position.x == other.position.x - 1 && robot.position.y == other.position.y) found[3] = true;
            if(robot.position.x == other.position.x + 1 && robot.position.y == other.position.y + 1) found[4] = true;
            if(robot.position.x == other.position.x - 1 && robot.position.y == other.position.y - 1) found[5] = true;
            if(robot.position.x == other.position.x + 1 && robot.position.y == other.position.y - 1) found[6] = true;
            if(robot.position.x == other.position.x - 1 && robot.position.y == other.position.y + 1) found[7] = true;
        }
        if(found[0] && found[1] && found[2] && found[3] && found[4] && found[5] && found[6] && found[7]) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::vector<Robot> robots;
    Point grid{101, 103};
    //Point grid{11, 7};

    std::string line;
    while(std::getline(inputFile, line)) {
        Robot robot;
        std::regex regex(R"(-?\d+)");
        std::regex_iterator<std::string::iterator> iterator(line.begin(), line.end(), regex);
        robot.position.x = std::stoi(iterator->str());
        robot.position.y = std::stoi((++iterator)->str());
        robot.velocity.x = std::stoi((++iterator)->str());
        robot.velocity.y = std::stoi((++iterator)->str());
        robots.push_back(robot);
    }

    int i = 0;
    while(!findCluster(robots)) {
        for(auto& robot : robots) {
            move(robot, grid);
        }
        i++;
    }

    //draw grid
    for(int y = 0; y < grid.y; y++) {
        for(int x = 0; x < grid.x; x++) {
            bool found = false;
            for(auto& robot : robots) {
                if(robot.position.x == x && robot.position.y == y) {
                    found = true;
                    break;
                }
            }
            if(found) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    std::cout << i << std::endl;

    return 0;
}

/* Part 1
for(auto& robot : robots) {
    for(int i = 0; i < 100; i++) {
        move(robot, grid);
    }
}

Point middle{grid.x / 2, grid.y / 2};
int quadrants[4] = {0, 0, 0, 0};
for(auto& robot : robots) {
    if(robot.position.x == middle.x || robot.position.y == middle.y) continue;
    if(robot.position.x < middle.x && robot.position.y < middle.y) quadrants[0]++;
    if(robot.position.x > middle.x && robot.position.y < middle.y) quadrants[1]++;
    if(robot.position.x > middle.x && robot.position.y > middle.y) quadrants[2]++;
    if(robot.position.x < middle.x && robot.position.y > middle.y) quadrants[3]++;
}

std::cout << quadrants[0]*quadrants[1]*quadrants[2]*quadrants[3] << std::endl;
 */