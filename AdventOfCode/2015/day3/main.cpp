#include <fstream>
#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

struct Vector2D
{
    int x;
    int y;

    Vector2D() : x(0), y(0) {}
    Vector2D(int x, int y) : x(x), y(y) {}
    Vector2D(const Vector2D& vector) : x(vector.x), y(vector.y) {}
    bool operator==(const Vector2D& Vector2D)
    {
        return x == Vector2D.x && y == Vector2D.y;
    }
};

std::string Vector2DToString(const Vector2D& Vector2D)
{
    std::stringstream ss;
    ss << "x: " << Vector2D.x << " y: " << Vector2D.y;
    return ss.str();
}

Vector2D Vector2DMove(const Vector2D& cvector, int dx, int dy)
{
    Vector2D vector(cvector);
    vector.x += dx;
    vector.y += dy;
    return vector;
}

int main()
{
    std::string input;
    std::ifstream inputfile;

    inputfile.open("input.txt");
    inputfile >> input;
    inputfile.close();

    std::unordered_map<char, std::function<Vector2D(const Vector2D&)>> map;
    map['<'] = std::bind(Vector2DMove, std::placeholders::_1, -1, 0);
    map['>'] = std::bind(Vector2DMove, std::placeholders::_1, 1, 0);
    map['^'] = std::bind(Vector2DMove, std::placeholders::_1, 0, 1);
    map['v'] = std::bind(Vector2DMove, std::placeholders::_1, 0, -1);

    {
        //part one
        std::vector<Vector2D> houses;
        houses.push_back(Vector2D());

        for(char i : input)
        {
            houses.push_back(map[i](houses.back()));
        }

        std::unordered_set<std::string> uniqueHouses;

        for(Vector2D housePos : houses)
        {
            auto housePosString = Vector2DToString(housePos);
            uniqueHouses.insert(housePosString);
        }
        std::cout << "Unique House: " << uniqueHouses.size() << std::endl;
    }

    {
        //part two
        std::vector<Vector2D> housesSanta;
        std::vector<Vector2D> housesRobot;

        housesSanta.push_back(Vector2D());
        housesRobot.push_back(Vector2D());

        int i = 0;
        for(char chr : input)
        {
            if(i % 2 == 0)
            {
                housesSanta.push_back(map[chr](housesSanta.back()));
            }
            else
            {
                housesRobot.push_back(map[chr](housesRobot.back()));
            }
            i++;
        }

        std::unordered_set<std::string> uniqueHouses;

        for(Vector2D housePos : housesSanta)
        {
            auto housePosString = Vector2DToString(housePos);
            uniqueHouses.insert(housePosString);
        }

        for(Vector2D housePos : housesRobot)
        {
            auto housePosString = Vector2DToString(housePos);
            uniqueHouses.insert(housePosString);
        }

        std::cout << "Unique House Part 2: " << uniqueHouses.size() << std::endl;
    }

    return 0;
}
