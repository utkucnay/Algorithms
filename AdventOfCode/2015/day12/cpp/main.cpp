#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> GetAllNumbers(const std::string& input);
void RemoveReds(std::string& input);

int main()
{
    std::string input;
    std::ifstream inputfile;

    inputfile.open("input.txt");
    inputfile >> input;
    inputfile.close();

    RemoveReds(input);
    std::cout << input << std::endl;
    auto results = GetAllNumbers(input);
    std::cout << std::accumulate(results.begin(), results.end(), 0) << std::endl;
}

std::vector<int> GetAllNumbers(const std::string& input)
{
    std::vector<int> result;
    std::stringstream ss;

    for(char c : input)
    {
        if(std::isdigit(c) || c == '-')
        {
            ss << c;
        }

        else if(ss.str() != "")
        {
            result.push_back(std::stoi(ss.str()));
            ss.str("");
        }
    }

    return result;
}

void RemoveReds(std::string& input)
{
    int fIndex = input.find(":\"red");
    int bIndex = 0;
    int eIndex = 0;

    while(input.npos != fIndex)
    {
        int count = 1;

        for(int i = fIndex; i > 0; i--)
        {
            count += input.at(i) == '}';
            count -= input.at(i) == '{';
            if(input.at(i) == '{' &&  count == 0)
            {
                bIndex = i;
                break;
            }
        }

        count = 1;
        for(int i = fIndex; i < input.size(); i++)
        {
            count += input.at(i) == '{';
            count -= input.at(i) == '}';
            if(input.at(i) == '}' && count == 0)
            {
                eIndex = i;
                break;
            }
        }
        input.erase(bIndex, eIndex - bIndex + 1);
        fIndex = input.find(":\"red");
    }
}
