#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <ostream>
#include <random>
#include <vector>
#include <unordered_map>

#define PRINT(x) std::cout << x.at(0) << " " << x.at(1) << std::endl;

namespace SolutionBruteForce {
    std::vector<int> twoSum(std::vector<int> nums, int target)
    {
        int numsSize = nums.size();

        for(int pIndex = 0; pIndex < numsSize; pIndex++)
        {
            for(int nIndex = pIndex + 1; nIndex < numsSize; nIndex++)
            {
                if(nums.at(pIndex) + nums.at(nIndex) == target)
                    return {pIndex, nIndex};
            }
        }

        return {-1, -1};
    }
};

namespace SolutionTwoPointer {
    std::vector<int> twoSum(std::vector<int> nums, int target)
    {
        std::sort(nums.begin(), nums.end());

        auto pIter  = nums.begin();
        auto nIter  = std::prev(nums.end(), 1) ;

        while(pIter < nIter)
        {
            int sum = *pIter + *nIter;

            if(sum < target)         std::advance(pIter, 1);
            else if (target < sum)   std::advance(nIter, -1);

            else
            {
                int smallIndex      = std::distance(nums.begin(), pIter);
                int bigIndex        = std::distance(nums.begin(), nIter);
                return {smallIndex, bigIndex};
            }
        }
        return {-1, -1};
    }
};

namespace SolutionMap {
    std::vector<int> twoSum(std::vector<int> nums, int target)
    {
        std::unordered_map<int, int>    map;
        std::vector<int>                result = {-1, -1};

        auto FindTwoSum = [&, i = 0] (int num) mutable {
            if(map.find(num) != map.end())
            {
                result = {map.at(num), i};
                return true;
            }
            map[target - num] = i++;
            return false;
        };

        std::find_if(nums.begin(), nums.end(), FindTwoSum);

        return result;
    }
};

int main()
{
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    {
        auto result = SolutionBruteForce::twoSum(nums, target);
        PRINT(result)
    }

    {
        auto result = SolutionTwoPointer::twoSum(nums, target);
        PRINT(result)
    }

    {
        auto result = SolutionMap::twoSum(nums, target);
        PRINT(result)
    }
}
