#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

int main()
{
    std::string input;
    std::ifstream inputfile;

    inputfile.open("input.txt");
    inputfile >> input;
    inputfile.close();

    long long sum = 0;

    for(char ch : input)
    {
        sum += 1 * (ch == '(') + -1 * (ch == ')');
    }

    std::cout << std::to_string(sum) << std::endl;
}
