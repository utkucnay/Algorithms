#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> SplitString(const std::string& inputs, char token = '\n');
int GetStringSize(const std::string& string);
int GetStringCastSize(const std::string& string);
int GetStringCastSizePart2(const std::string& string);

int main()
{
    std::ifstream ifstr;
    ifstr.open("input.txt");
    std::string input(std::istreambuf_iterator<char>(ifstr), {});

    std::vector<std::string> sInput = SplitString(input);

    int sum = 0;
    int sumpart2 = 0;
    for(std::string& str : sInput)
    {
        int dsum = GetStringSize(str) - GetStringCastSize(str);
        int dsumpart2 = GetStringCastSizePart2(str) - GetStringSize(str);
        sum += dsum;
        sumpart2 += dsumpart2;
    }

    ifstr.close();

    std::cout << "Part 1: " << sum << " Part 2: "  << sumpart2 << std::endl;
}

int GetStringSize(const std::string& string)
{
    return string.size();
}

int GetStringCastSizePart2(const std::string& string)
{
    int size = 2;

    for(char chr : string)
    {
        if(chr == '"')
            size += 1;
        if(chr == '\\')
            size += 1;
        size++;
    }

    return size;
}

int GetStringCastSize(const std::string& string)
{
    int size = string.size() - 2;
    bool isSlashBefore = false;

    for(char chr : string)
    {
        if(isSlashBefore)
        {
            if(chr == '"')
                size -= 1;
            if(chr == 'x')
                size -= 3;
            if(chr == '\\')
                size -= 1;
            isSlashBefore = false;
        }
        else
            isSlashBefore = chr == '\\';
    }

    return size;
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
