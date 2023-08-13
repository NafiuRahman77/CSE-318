#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <algorithm>
using namespace std;
int main() {
    // Seed the random number generator
    set<int> X;
    X.insert(1);
    X.insert(2);
    X.insert(3);
    set<int> Y;
    Y.insert(1);

    set<int> V_prime;
    set_difference(X.begin(), X.end(), Y.begin(), Y.end(), inserter(V_prime, V_prime.end()));

    for(auto x: V_prime)
    {
       cout << x << endl;
    }

    return 0;
}