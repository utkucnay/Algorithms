#include <algorithm>
#include <array>
#include <fstream>
#include <numeric>
#include <utility>
#include <vector>
#include <alloca.h>
#include <iostream>
#include <limits.h>
#include <ostream>
#include <sstream>
#include <string>

//part 1
int FindRequariedBox(int l, int w, int h)
{
    std::array<int, 3> arr;
    arr[0] = l * w;
    arr[1] = w * h;
    arr[2] = h * l;
    return 2 * std::accumulate(arr.begin(), arr.end(), 0)
                                + *std::min_element(arr.begin(), arr.end());
}

//part2
int SumTwoMin(std::array<int, 3> arr)
{
    std::array<int, 3> sums;
    for(int ip = 0; ip < arr.size(); ip++)
        for(int in = ip + 1; in < arr.size(); in++)
        {
            sums[ip + in - 1] = arr[ip] + arr[in];
        }
    return *std::min_element(sums.begin(), sums.end());
}

int Product(std::array<int, 3> arr)
{
    int prod = 1;
    for(int i = 0; i < arr.size(); i++)
    {
        prod *= arr[i];
    }
    return prod;
}

int FindFeetOfRibbon(int l, int w, int h)
{
    std::array<int, 3> arr;
    arr[0] = l;
    arr[1] = w;
    arr[2] = h;
    return 2 * SumTwoMin(arr) + Product(arr);
}

int main ()
{
    std::ifstream inputfile;
    inputfile.open("input.txt");

    long long sumRequariedBox = 0;
    long long sumFeetOfRibbon = 0;

    std::array<int, 3> inputs;

    for(std::string line; std::getline(inputfile, line);)
    {
        std::stringstream ssInputLine(line);
        int i = 0;

        for(std::string num; std::getline(ssInputLine, num, 'x');)
        {
            inputs[i++] = std::stoi(num);
        }

        sumRequariedBox += FindRequariedBox(inputs[0], inputs[1], inputs[2]);
        sumFeetOfRibbon += FindFeetOfRibbon(inputs[0], inputs[1], inputs[2]);
    }

    inputfile.close();

    std::cout << "Requarie Box: "  <<  std::to_string(sumRequariedBox) << std::endl;
    std::cout << "Feet of Ribbon: " << std::to_string(sumFeetOfRibbon) << std::endl;
    return 0;
}
