#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int FindGridSize(int stringLength);
std::vector<std::string> SplitString(const std::string& inputs, char token = '\n');
inline int FindIndex(int x, int y, int gridSize) { return y * gridSize + x; }
void PrintGrid(const std::vector<int>& grid, int gridsize);
std::vector<std::vector<int>> FindAllWay(int gridSize);
void FindAllPermUntil(std::vector<std::vector<int>>& results, std::vector<int>& perms, int p, int n);

int main()
{
    std::ifstream ifstr;
    ifstr.open("input.txt");
    std::string input(std::istreambuf_iterator<char>(ifstr), {});

    std::vector<std::string> sInput = SplitString(input);
    int gridsize = FindGridSize(sInput.size());

    std::vector<int> grid(gridsize * gridsize);
    for (int& a : grid)
    {
        a = std::numeric_limits<int>::infinity();
    }

    std::unordered_map<std::string, int> CityIndex;
    int index = 0;

    for (std::string& in : sInput)
    {
        auto eni = SplitString(in, ' ');
        if(CityIndex.find(eni.at(0)) == CityIndex.end())
            CityIndex[eni.at(0)] = index++;
        if(CityIndex.find(eni.at(2)) == CityIndex.end())
            CityIndex[eni.at(2)] = index++;

        grid.at(FindIndex(CityIndex[eni.at(0)],CityIndex[eni.at(2)], gridsize)) = std::stoi(eni.at(4));
        grid.at(FindIndex(CityIndex[eni.at(2)],CityIndex[eni.at(0)], gridsize)) = std::stoi(eni.at(4));
    }

    auto perms = FindAllWay(gridsize);
    std::vector<int> allPathSums;

    for(std::vector<int>& perm : perms)
    {
        int sum = 0;
        for(int i = 0; i < gridsize - 1; i++)
        {
            sum += grid[FindIndex(perm.at(i), perm.at(i + 1), gridsize)];
        }
        allPathSums.push_back(sum);
    }

    auto min = std::min_element(allPathSums.begin(), allPathSums.end());
    auto max = std::max_element(allPathSums.begin(), allPathSums.end());

    std::cout << "Min Distance: " << *min << std::endl;
    std::cout << "Max Distance: " << *max << std::endl;
}

std::vector<std::vector<int>> FindAllWay(int gridSize)
{
    std::vector<std::vector<int>> results;
    std::vector<int> perms;
    for(int i = 0; i < gridSize; i++)
        perms.push_back(i);

    FindAllPermUntil(results, perms, 0, gridSize);

    return results;
}

void FindAllPermUntil(std::vector<std::vector<int>>& results, std::vector<int>& perms, int p, int n)
{
    if(p == n)
        results.push_back(perms);

    for(int i = p; i < n; i++)
    {
        std::swap(perms[i], perms[p]);
        FindAllPermUntil(results, perms, p + 1, n);
        std::swap(perms[p], perms[i]);
    }
}

void PrintGrid(const std::vector<int>& grid, int gridsize)
{
    for(int y = 0; y < gridsize; y++)
    {
        for(int x = 0; x < gridsize; x++)
        {
            std::cout << grid.at(FindIndex(x, y, gridsize)) << ' ';
        }
        std::cout << std::endl;
    }
}

int FindGridSize(int stringLength)
{
    return ((-1 + std::sqrt(8 * stringLength + 1)) / 2) + 1;
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
    if(ss.str() != "")
        result.push_back(ss.str());
    return result;
}
