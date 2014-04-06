#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/*
 * Scenario
 * count the number of string whinch its length is less than some threshold
 */

int common_count(const std::vector<std::string>& str_vec, size_t threshold)
{
    int count = 0;
    for (size_t i = 0; i < str_vec.size(); ++ i) {
        if (str_vec[i].length() < threshold) {
            ++ count;
        }
    }
    return count;
}

////////////////////////////////////////////////////

bool less_than_five(const std::string& str)
{
    return str.length() < 5;
}

int impl_less_than_five(const std::vector<std::string>& str_vec)
{
    return std::count_if(str_vec.begin(), str_vec.end(), less_than_five);
}

////////////////////////////////////////////////////

class LessThan
{
public:
    LessThan(int threshold): _threshold(threshold) {}
    bool operator() (const std::string& str) const
    {
        return str.length() < _threshold;
    }
private:
    const int _threshold;
};

int functor_count(const std::vector<std::string>& str_vec, size_t threshold)
{
    return std::count_if(str_vec.begin(), str_vec.end(), LessThan(threshold));
    // the code below is also ok
    //LessThan less_than(threshold);
    //return std::count_if(str_vec.begin(), str_vec.end(), less_than);
}

////////////////////////////////////////////////////

int main ()
{
    const char* str_arr[] = {"a string", "other string", "str", "str2"};
    std::vector<std::string> str_vec(str_arr, std::end(str_arr));
    const int threshold = 5;

    std::cout << common_count(str_vec, threshold) << std::endl;
    std::cout << impl_less_than_five(str_vec) << std::endl;       //use const threshold, oops
    std::cout << functor_count(str_vec, threshold) << std::endl;
    return 0;
}
