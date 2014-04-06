#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

/*
 * for_each
 */
void my_function(int i)
{
    std::cout << i << ' ';
}

class MyFunctor
{
public:
    MyFunctor(const int& i): _test_int(i) {}
    void operator() (int i)
    {
        if (i % _test_int == 0) { std::cout << i << ' '; }
    }
private:
    const int _test_int;
};

void test_for_each()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 100};
    for_each(v.begin(), v.end(), my_function);
    std::cout << std::endl;
    for_each(v.begin(), v.end(), MyFunctor(2));
    std::cout << std::endl;
}

/*
 * count_if
 */

class LessFunctor
{
public:
    bool operator() (int i)
    {
        return i % 2 == 0;
    }
};

bool less_function(int i)
{
    return i % 2 == 0;
}

void test_count_if()
{
    //c++ 11 standard
    //std::vector<int> int_vec = {1, 2, 3, 4, 5};
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> int_vec(arr, std::end(arr));
    std::cout << std::count_if(int_vec.begin(), int_vec.end(), less_function) << std::endl;
    std::cout << std::count_if(int_vec.begin(), int_vec.end(), LessFunctor()) << std::endl;
    std::cout << std::count_if(int_vec.begin(), int_vec.end(), [](const int& i){return i%2==0;}) << std::endl;
    //auto lambda_func = [] (const int& i) {return i%2==0;};
    //std::cout << std::count_if(int_vec.begin(), int_vec.end(), lambda_func) << std::endl;
}

/*
 * accumulate
 */

int sum_func(int x, int y) { return x + y; }
int minus_func(int x, int y) { return x - y; }
class SumFunctor
{
public:
    int operator() (int x, int y) { return x + 2*y; } 
};

void test_accumulate()
{
    int init = 0;
    //c++ 11
    std::vector<int> int_vec = {1, 2, 3, 4, 5};
    std::cout << std::accumulate(int_vec.begin(), int_vec.end(), init, sum_func) << std::endl;              //15
    std::cout << std::accumulate(int_vec.begin(), int_vec.end(), init, minus_func) << std::endl;            //-15
    std::cout << std::accumulate(int_vec.begin(), int_vec.end(), init, SumFunctor()) << std::endl;          //30
    std::cout << std::accumulate(int_vec.begin(), int_vec.end(), init, std::plus<int>()) << std::endl;      //15
    //lambda, c++ 11
    std::cout << std::accumulate(int_vec.begin(), int_vec.end(), init, [](int x, int y){return x+y;}) << std::endl; //15
}

int main ()
{
    test_for_each();
    test_count_if();
    test_accumulate();

    return 0;
}
