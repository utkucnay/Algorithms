#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

bool ContainsVowels(const std::string& input, const std::vector<char>& vowels)
{
    int count = 0;
    for(char vowel : vowels)
    {
        count += std::count(input.begin(), input.end(), vowel);
    }
    return count >= 3;
}

bool IsUnique(const std::string& input)
{
    std::string tInput(input);
    auto last = std::unique(tInput.begin(),tInput.end());
    return last == tInput.end();
}

bool IsContainStrings(const std::string& input, std::vector<std::string> strings)
{
    bool result = true;
    for(std::string str : strings)
    {
        if(input.find(str) != std::string::npos) result = false;
    }
    return result;
}

bool IsContainsPairOfTwoLetters(const std::string& input)
{
    std::unordered_map<std::string, int> map;
    bool result = false;

    for(int i = 1; i < input.size(); i++)
    {
        std::string substr = input.substr(i - 1, 2);
        if(map.find(substr) != map.end())
        {
            if(i - map[substr] > 1)
                result = true;
        }
        else
            map[substr] = i;
    }

    return result;
}

bool IsSameTwoLetter(const std::string& input)
{
    bool result = false;

    for (int i = 2; i < input.size(); i++)
    {
        if(input.at(i) == input.at(i - 2)) result = true;
    }

    return result;
}

int main()
{
    {
        //part one
        std::ifstream inputfile;
        inputfile.open("input.txt");

        long long sumOfNice = 0;
        for(std::string input; std::getline(inputfile, input);)
        {
            bool result = true;

            result *= ContainsVowels(input, {'a','e','i','o', 'u'});
            result *= !IsUnique(input);
            result *= IsContainStrings(input, {"ab","cd","pq","xy"});

            sumOfNice += result;
        }

        inputfile.close();

        std::cout << "Sum Of Nice Words: " << sumOfNice << std::endl;
    }

    {
        //part two
        std::ifstream inputfile;
        inputfile.open("input.txt");

        long long sumOfNice = 0;
        for(std::string input; std::getline(inputfile, input);)
        {
            bool result = true;
            result *= IsContainsPairOfTwoLetters(input);
            result *= IsSameTwoLetter(input);
            sumOfNice += result;
        }

        inputfile.close();

        std::cout << "Sum Of Nice Words Part 2: " << sumOfNice << std::endl;
    }
}
