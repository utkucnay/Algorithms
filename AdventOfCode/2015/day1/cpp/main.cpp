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

    {
        //part one
        long long sum = 0;
        for(char ch : input)
        {
            sum += 1 * (ch == '(') + -1 * (ch == ')');
        }
        std::cout << std::to_string(sum) << std::endl;
    }
    {
        //part two
        long long sum = 0;
        long long firstBasementPos = -1;
        for(long long i = 0; i < input.size(); i++)
        {
            sum += 1 * (input.at(i) == '(') + -1 * (input.at(i) == ')');
            firstBasementPos += (i + 2) *
                                (sum == -1) *
                                (firstBasementPos == -1);
        }
        std::cout << std::to_string(firstBasementPos) << std::endl;
    }
}
