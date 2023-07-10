#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>

std::string LookAndSay(const std::string& input);

int main()
{
    std::string input = "3113322113";

    //Part 1 = 40
    //Part 2 = 50
    for(int i = 0; i < 50; i++)
    {
        input = std::move(LookAndSay(input));
    }

    std::cout << input.size() << std::endl;
}

std::string LookAndSay(const std::string& input)
{
    std::stringstream result;

    auto bPtr = input.begin();

    for(auto lPtr = input.begin(); lPtr != input.end(); std::advance(lPtr, 1))
    {
        if(*bPtr != *lPtr)
        {
            result << (int)std::distance(bPtr, lPtr);
            result << *bPtr;
            bPtr = lPtr;
        }
    }

    result << (int)std::distance(bPtr, input.end());
    result << *bPtr;

    return result.str();
}
