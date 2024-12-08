#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>

struct Point{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

// 0->Y
// |
// v
// X

bool isInLimit(Point& p, Point& limit) {
    return p.x >= 0 && p.x < limit.x && p.y >= 0 && p.y < limit.y;
}

int main() {

    std::ifstream inputFile("./../input.txt");
    //std::ifstream inputFile("./../example.txt");

    std::map<char, std::vector<Point>> allPoints;
    Point limit;

    std::string line;
    {
        int i=0;
        int j;
        while (getline(inputFile, line)) {
            j=0;
            for (char c : line) {
                if (c != '.') {
                    Point p;
                    p.x = i;
                    p.y = j;
                    if(allPoints.find(c) == allPoints.end()) {
                        std::vector<Point> points;
                        points.push_back(p);
                        allPoints.insert(std::pair<char, std::vector<Point>>(c, points));
                    } else {
                        allPoints[c].push_back(p);
                    }
                }
                j++;
            }
            i++;
        }
        limit = Point(i, j);
    }

    std::cout << "limit.x : " << limit.x << ", limit.y : " << limit.y << std::endl;

    std::vector<std::string> grid(limit.x, std::string(limit.y, '.'));

    int nb = 0;

    for (auto const& [key, val] : allPoints) {
        for (auto p1 = val.begin(); p1 != val.end(); ++p1) {
            for (auto p2 = p1 + 1; p2 != val.end(); ++p2) {
                Point delta(p2->x - p1->x, p2->y - p1->y);
                Point current(*p1);
                while(isInLimit(current, limit)){
                    if(grid[current.x][current.y] == '.')
                        ++nb;
                    grid[current.x][current.y] = '@';
                    current.x -= delta.x;
                    current.y -= delta.y;
                }
                current = *p2;
                while(isInLimit(current, limit)){
                    if(grid[current.x][current.y] == '.')
                        ++nb;
                    grid[current.x][current.y] = '@';
                    current.x += delta.x;
                    current.y += delta.y;
                }
            }
        }
        std::cout << std::endl;
    }

    for (std::string line : grid) {
        std::cout << line << std::endl;
    }

    std::cout << "nb : " << nb << std::endl;

    return 0;
}

/*Part 1 : 1339
                Point delta(p2->x - p1->x, p2->y - p1->y);
                Point nodes[2] = {Point(p1->x-delta.x, p1->y-delta.y), Point(p2->x+delta.x, p2->y+delta.y)};
                for (Point& node : nodes) {
                    if(isInLimit(node, limit)){
                        if(grid[node.x][node.y] == '.')
                            ++nb;
                        grid[node.x][node.y] = '@';
                    }
                }
*/