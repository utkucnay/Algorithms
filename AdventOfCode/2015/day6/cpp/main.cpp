#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <array>
#include <cstddef>
#include <iostream>
#include <limits>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

template <typename Td, std::size_t Y, std::size_t X>
struct Grid
{
    std::array<Td, Y * X> GridData;
    const int maxY = Y;
    const int maxX = X;

    inline Td& GetItem(int x, int y)
    {
        if(x > maxX) assert("x bigger than maxX");
        if(y > maxY) assert("y bigger than maxY");
        return GridData[y * maxX + x];
    }
    void ApplyOP(int x0, int x1, int y0, int y1, std::function<Td(Td)> op);

    inline int GetOpenLightCount()
    {
        return std::accumulate(GridData.begin(), GridData.end(), 0);
    }

    Grid()
    {
        memset(GridData.data(), 0, maxX * maxY);
    }
};

std::vector<std::string> SplitString(const std::string& inputs, char token);
inline bool TurnOnBool  (bool x)    { return true;   }
inline bool TurnOffBool (bool x)    { return false;  }
inline bool ToggleBool  (bool x)    { return !x;     }

inline int  TurnOnInt   (int x)     { return ++x;         }
inline int  TurnOffInt  (int x)     { return std::clamp(--x, 0, std::numeric_limits<int>::max());}
inline int  ToggleInt   (int x)     { return x += 2;      }

int main()
{
    {
        //part1
        Grid<bool, 1000, 1000> grid;

        using OP =  std::function<bool(bool)>;

        int x0 = 0, x1 = 0, y0 = 0, y1 = 0;

        std::ifstream inputfile;
        inputfile.open("input.txt");

        for(std::string input; std::getline(inputfile, input);)
        {
            std::vector<std::string> splitInput = SplitString(input, ' ');

            auto StartPoints    = SplitString(splitInput.at(splitInput.size() - 3), ',');
            auto EndPoints      = SplitString(splitInput.at(splitInput.size() - 1), ',');

            x0 = std::stoi(StartPoints.at(0));
            y0 = std::stoi(StartPoints.at(1));

            x1 = std::stoi(EndPoints.at(0));
            y1 = std::stoi(EndPoints.at(1));

            OP op;

            if(splitInput.size() == 4)
            {
                op = ToggleBool;
            }
            else if (splitInput.at(1) == "on")
            {
                op = TurnOnBool;
            }
            else
            {
                op = TurnOffBool;
            }

            grid.ApplyOP(x0, x1, y0, y1, op);
        }
        inputfile.close();

        std::cout << grid.GetOpenLightCount() << std::endl;
    }

    {
        //part2

        Grid<int, 1000, 1000>* grid = new Grid<int, 1000, 1000>;

        using OP =  std::function<int(int)>;

        int x0 = 0, x1 = 0, y0 = 0, y1 = 0;

        std::ifstream inputfile;
        inputfile.open("input.txt");

        for(std::string input; std::getline(inputfile, input);)
        {
            std::vector<std::string> splitInput = SplitString(input, ' ');

            auto StartPoints    = SplitString(splitInput.at(splitInput.size() - 3), ',');
            auto EndPoints      = SplitString(splitInput.at(splitInput.size() - 1), ',');

            x0 = std::stoi(StartPoints.at(0));
            y0 = std::stoi(StartPoints.at(1));

            x1 = std::stoi(EndPoints.at(0));
            y1 = std::stoi(EndPoints.at(1));

            OP op;

            if(splitInput.size() == 4)
            {
                op = ToggleInt;
            }
            else if (splitInput.at(1) == "on")
            {
                op = TurnOnInt;
            }
            else
            {
                op = TurnOffInt;
            }

            grid->ApplyOP(x0, x1, y0, y1, op);
        }
        inputfile.close();

        std::cout << grid->GetOpenLightCount() << std::endl;
    }
}


std::vector<std::string> SplitString(const std::string& inputs, char token)
{
    std::vector<std::string> result;
    std::stringstream ss;

    for(char input : inputs)
    {
        if(input != token)
            ss << input;
        else
        {
            result.push_back(ss.str());
            ss.str("");
        }
    }

    result.push_back(ss.str());
    return result;
}

template <typename Td, std::size_t Y, std::size_t X>
void Grid<Td, Y, X>::ApplyOP(int x0, int x1, int y0, int y1, std::function<Td(Td)> op)
{
    for(int y = y0; y <= y1; y++)
        for(int x = x0; x <= x1; x++)
            GetItem(x, y) = op(GetItem(x, y));
}
