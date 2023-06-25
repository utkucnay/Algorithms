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

namespace SolutionTwoPointer {
    std::vector<int> twoSum(std::vector<int> nums, int target) {
        std::sort(nums.begin(), nums.end());

        auto pIter = nums.begin();
        auto nIter   = std::prev(nums.end(), 1) ;

        while(pIter < nIter)
        {
            int sum = *pIter + *nIter;

            if(sum < target) std::advance(pIter, 1);
            else if (target < sum) std::advance(nIter, -1);

            else
            {
                int smallIndex =    std::distance(nums.begin(), pIter);
                int bigIndex =      std::distance(nums.begin(), nIter);
                return {smallIndex, bigIndex};
            }
        }
        return {-1, -1};
    }
};

namespace SolutionMap {
    std::vector<int> twoSum(std::vector<int> nums, int target) {
        std::unordered_map<int, int>    map;
        std::vector<int>                result = {-1, -1};

        auto FindTwoSum =  [&, i = 0] (int num) mutable {
            if(map.find(num) != map.end()){
                result = {map.at(num), i};
                return true;
            }
            map[target - num] = i;
            ++i;
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
        auto result = SolutionTwoPointer::twoSum(nums, target);
        std::cout << result.at(0) << " " << result.at(1) << std::endl;
    }

    {
        auto result = SolutionMap::twoSum(nums, target);
        std::cout << result.at(0) << " " << result.at(1) << std::endl;
    }
}
