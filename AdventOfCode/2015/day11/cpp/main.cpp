#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


void CheckString(std::string& input, std::unordered_map<char, char>& increMemo);
bool IncreaseStraightThree(std::string& input);
bool IsOverlapping(std::string& input);

int main()
{
    std::unordered_map<char, char> increMemo;
    //part1: hxcaabcc
    std::string input("hxbxxzaa");

    for(char chr = 'a'; chr <= 'z'; chr++)
    {
        char result = chr + 1;
        result += result == 'i';
        result += result == 'o';
        result += result == 'l';
        increMemo[chr] = result;
    }

    bool isFinded = false;
    for(auto i = input.begin(); i < input.end(); std::advance(i, 1))
    {
        if(isFinded)
            *i = 'a';
        if(*i == 'i' || *i == 'o' || *i == 'l')
        {
            isFinded = true;
            *i = increMemo[*i];
        }
    }

    while(!(IncreaseStraightThree(input) && IsOverlapping(input)))
    {
        auto lastPtr = input.rbegin();
        *lastPtr = increMemo[*lastPtr];
        CheckString(input, increMemo);
    }

    std::cout << input << std::endl;
}

void CheckString(std::string& input, std::unordered_map<char, char>& increMemo)
{
    auto ptr = std::find(input.begin(), input.end(), '{');

    if(ptr == input.end())
        return;

    auto prevPtr = std::prev(ptr, 1);
    *prevPtr = increMemo[*prevPtr];

    *ptr = 'a';
    CheckString(input, increMemo);
}


bool IncreaseStraightThree(std::string& input)
{
    for(auto i = input.begin() + 2; i < input.end(); std::advance(i, 1))
    {
        auto ip = std::prev(i, 1);
        auto ipp = std::prev(i, 2);

        if(*i - *ip == 1 && *ip - *ipp == 1) return true;
    }
    return false;
}

bool IsOverlapping(std::string& input)
{
    int count = 0;
    std::unordered_set<char> set;
    for(auto i = std::next(input.begin(), 1); i != input.end(); std::advance(i, 1))
    {
        auto ip = std::prev(i, 1);

        if(*i == *ip && set.find(*i) == set.end())
        {
            count++;
            set.insert(*i);
        }
    }
    if(count >= 2) return true;
    return false;
}
