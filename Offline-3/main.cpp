#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

struct edge
{
    int u;
    int v;
    double wt;
    edge(int first, int second, double weight)
    {
        u = first;
        v = second;
        wt = weight;
    }
};

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

class Graph
{

private:
    int numVertices;
    vector<vector<double>> adjacencyMatrix;
    vector<edge> edgeList;

public:
    Graph(int vertices) : numVertices(vertices), adjacencyMatrix(vertices + 1, vector<double>(vertices + 1, 0.0)) {}

    void addEdge(int u, int v, double wt)
    {
        if (u >= 1 && u <= numVertices && v >= 1 && v <= numVertices)
        {
            adjacencyMatrix[u][v] = wt;
            adjacencyMatrix[v][u] = wt;
            edgeList.emplace_back(u, v, wt);
        }
        else
        {
            cout << "Invalid vertices for edge." << endl;
        }
    }

    double getWmin()
    {
        double minWeight = INT_MAX;
        for (const auto &e : edgeList)
        {
            minWeight = min(minWeight, e.wt);
        }
        return minWeight;
    }

    double getWmax()
    {
        double maxWeight = INT_MIN;
        for (const auto &e : edgeList)
        {
            maxWeight = max(maxWeight, e.wt);
        }
        return maxWeight;
    }
    vector<pair<int, int>> getRCL_e(double mu)
    {
        vector<pair<int, int>> rcl;
        for (const auto &e : edgeList)
        {
            if (e.wt >= mu)
            {
                rcl.emplace_back(e.u, e.v);
            }
        }
        return rcl;
    }
    set<int> unionSets(const set<int> &X, const set<int> &Y)
    {
        set<int> unionSet;
        unionSet.insert(X.begin(), X.end());
        unionSet.insert(Y.begin(), Y.end());

        return unionSet;
    }

    MaxCutResult semiGreedy()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        double alpha = static_cast<double>(rand()) / RAND_MAX;
        int Wmin = getWmin();
        int Wmax = getWmax();
        double mu = Wmin + alpha * (Wmax - Wmin);

        vector<pair<int, int>> rcl_e = getRCL_e(mu);
        int randomIndex = rand() % rcl_e.size();
        pair<int, int> selectedEdge = rcl_e[randomIndex];

        set<int> X;
        set<int> Y;
        X.insert(selectedEdge.first);
        Y.insert(selectedEdge.second);

        set<int> V;
        for (const auto &e : edgeList)
        {
            V.insert(e.u);
            V.insert(e.v);
        }

        while (!(unionSets(X, Y) == V))
        {
            set<int> V_prime;
            set_difference(V.begin(), V.end(), unionSets(X, Y).begin(), unionSets(X, Y).end(), inserter(V_prime, V_prime.end()));
            int sigma_x_min = INT_MAX, sigma_y_min = INT_MIN, sigma_x_max = INT_MAX, sigma_y_max = INT_MIN;
            map<int, int> sigma_x_map;
            map<int, int> sigma_y_map;
            for (auto vertex : V_prime)
            {
                
            }
        }
        MaxCutResult m;
        return m;
    }
};

int main()
{
}