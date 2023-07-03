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

//part 1
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

//part2
int SumTwoMin(int* arr, int size)
{
    int* sums = (int*)alloca(3 * sizeof(int));
    for(int ip = 0; ip < size; ip++)
        for(int in = ip + 1; in < size; in++)
        {
            sums[ip + in - 1] = arr[ip] + arr[in];
        }
    return Min(sums, 3);
}

int Product(int* arr, int size)
{
    int prod = 1;
    for(int i = 0; i < size; i++)
    {
        prod *= arr[i];
    }
    return prod;
}

int FindFeetOfRibbon(int l, int w, int h)
{
    int* arr = (int*)alloca(3 * sizeof(int));
    arr[0] = l;
    arr[1] = w;
    arr[2] = h;
    return 2 * SumTwoMin(arr, 3) + Product(arr, 3);
}

int main ()
{
    std::ifstream inputfile;
    inputfile.open("input.txt");

    long long sumRequariedBox = 0;
    long long sumFeetOfRibbon = 0;

    int* inputs = (int*)alloca(3 * sizeof(int));

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
