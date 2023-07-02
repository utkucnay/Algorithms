#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>
#include <alloca.h>
#include <iostream>
#include <limits.h>
#include <ostream>
#include <sstream>
#include <string>

int Min(int* arr, int size)
{
    int min = INT_MAX;
    for(int i = 0; i < size; i++)
    {
        bool isBig = min > arr[i];
        min = arr[i] * isBig + min * !isBig;
    }
    return min;
}


int Sum(int* arr, int size)
{
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int FindRequariedBox(int l, int w, int h)
{
    int* arr = (int*)alloca(3 * sizeof(int));
    arr[0] = l * w;
    arr[1] = w * h;
    arr[2] = h * l;
    return 2 * Sum(arr, 3) + Min(arr, 3);
}

int main ()
{
    std::ifstream inputfile;
    inputfile.open("input.txt");

    long long sum = 0;

    for(std::string line; std::getline(inputfile, line);)
    {
        std::vector<int> inputs;
        inputs.reserve(3);
        std::stringstream ssInputLine(line);

        for(std::string num; std::getline(ssInputLine, num, 'x');)
        {
            inputs.push_back(std::stoi(num));
        }
        sum += FindRequariedBox(inputs.at(0), inputs.at(1), inputs.at(2));
    }

    inputfile.close();

    std::cout << std::to_string(sum) << std::endl;

    return 0;
}
