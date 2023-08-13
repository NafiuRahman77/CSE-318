#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
class MaxCutResult
{
public:
    set<int> s;
    set<int> s_prime;
    int maxCutValue;

    MaxCutResult() : maxCutValue(0) {}

    MaxCutResult(const set<int> &s_, const set<int> &s_prime_, int maxCutValue_)
        : s(s_), s_prime(s_prime_), maxCutValue(maxCutValue_) {}
};
int main()
{
    // Seed the random number generator
    set<int> X;
    X.insert(1);
    X.insert(1);
    X.insert(2);
    X.insert(3);
    set<int> Y;
    Y.insert(1);
    Y.insert(5);
    MaxCutResult result;
    MaxCutResult m1(X,Y,1);
    result=m1;
    // set<int> V_prime;
    // set_difference(X.begin(), X.end(), Y.begin(), Y.end(), inserter(V_prime, V_prime.end()));
    // bool flag = (X == Y);
    // set<int> unionSet;
    // unionSet.insert(X.begin(), X.end());
    // unionSet.insert(Y.begin(), Y.end());

    // for (auto it : unionSet)
    // {
    //     cout << it << endl;
    // }
    // int vertex = 1, sigma_x = 5, sigma_y = 6;
    // map<int, int> sigma_x_map;
    // map<int, int> sigma_y_map;
    // sigma_x_map[vertex] = sigma_x;
    // sigma_y_map[vertex] = sigma_y;
    // auto sigma_x_it = sigma_x_map.find(vertex);
    // auto sigma_y_it = sigma_y_map.find(vertex);

    // if (sigma_x_it != sigma_x_map.end() && sigma_y_it != sigma_y_map.end())
    // {
    //      cout << sigma_x_it->second << " " << sigma_y_it->second << endl;
    // }

    return 0;
}