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
    vector<int> getRCL_v(const map<int, int> &sigma_x_map, const map<int, int> &sigma_y_map, int mu, const set<int> &v_prime)
    {
        vector<int> rcl;
        for (auto vertex : v_prime)
        {
            auto sigma_x_it = sigma_x_map.find(vertex);
            auto sigma_y_it = sigma_y_map.find(vertex);

            if (sigma_x_it != sigma_x_map.end() && sigma_y_it != sigma_y_map.end())
            {
                if (max(sigma_x_it->second, sigma_y_it->second) > mu)
                {
                    rcl.emplace_back(vertex);
                }
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

    MaxCutResult GRASP()
    {
        int w_star = INT_MIN;
        MaxCutResult result;
        for (int i = 0; i < 10; i++)
        {
            MaxCutResult m1 ;
            m1 = SemiGreedyMaxCut();
            MaxCutResult m2 ;
            m2 = LocalSearch(m1.s, m1.s_prime);
            if (m2.maxCutValue > w_star)
            {
                result = m2;
            }
        }
        return result;
    }

    int sigmaCalculator(const set<int> &S, int vertex)
    {
        int sum = 0;
        for (const auto &e : edgeList)
        {
            if (e.v == vertex)
            {
                if (S.count(e.u) > 0)
                {
                    sum += e.wt;
                }
            }
            if (e.u == vertex)
            {
                if (S.count(e.v) > 0)
                {
                    sum += e.wt;
                }
            }
        }
        return sum;
    }

    MaxCutResult SemiGreedyMaxCut()
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
                int sigma_x = sigmaCalculator(Y, vertex);
                int sigma_y = sigmaCalculator(X, vertex);
                sigma_x_map[vertex] = sigma_x;
                sigma_y_map[vertex] = sigma_y;
                if (sigma_x < sigma_x_min)
                {
                    sigma_x_min = sigma_x;
                }
                if (sigma_y < sigma_y_min)
                {
                    sigma_y_min = sigma_y;
                }
                if (sigma_x > sigma_x_max)
                {
                    sigma_x_max = sigma_x;
                }
                if (sigma_y > sigma_y_max)
                {
                    sigma_y_max = sigma_y;
                }
            }
            Wmin = min(sigma_x_min, sigma_y_min);
            Wmax = max(sigma_x_max, sigma_y_max);
            mu = Wmin + alpha * (Wmax - Wmin);
            vector<int> rcl_v = getRCL_v(sigma_x_map, sigma_y_map, mu, V_prime);
            int selectedVertex = rcl_v[rand() % rcl_e.size()];
            auto sigma_x_it = sigma_x_map.find(selectedVertex);
            auto sigma_y_it = sigma_y_map.find(selectedVertex);

            if (sigma_x_it != sigma_x_map.end() && sigma_y_it != sigma_y_map.end())
            {
                if (sigma_x_it->second > sigma_y_it->second)
                {
                    X.insert(selectedVertex);
                }
                else
                {
                    Y.insert(selectedVertex);
                }
            }
        }
        set<int> s;
        s.insert(X.begin(), X.end());
        set<int> s_prime;
        s_prime.insert(Y.begin(), Y.end());
        double weight = 0;
        for (const auto &edge : edgeList)
        {
            if (s.count(edge.u) > 0 && s_prime.count(edge.v) > 0)
            {
                weight += edge.wt;
            }
            if (s.count(edge.v) > 0 && s_prime.count(edge.u) > 0)
            {
                weight += edge.wt;
            }
        }
        MaxCutResult m(s, s_prime, weight);
        return m;
    }
    MaxCutResult LocalSearch(const set<int> &s, set<int> &s_prime)
    {
        set<int> s_;
        s_.insert(s.begin(), s.end());
        set<int> s_prime_;
        s_prime_.insert(s_prime.begin(), s_prime.end());
        bool change = true;
        while (change)
        {
            change = false;
            for (int i = 1; i <= numVertices; i++)
            {
                if (change == true)
                {
                    break;
                }
                if ((sigmaCalculator(s_, i) > sigmaCalculator(s_prime_, i) && s_.count(i) > 0))
                {
                    s_.erase(i);
                    s_prime_.insert(i);
                    // S_prime.add(vertex);
                    change = true;
                }
                else
                {
                    if ((sigmaCalculator(s_prime_, i) > sigmaCalculator(s_, i) && s_prime_.count(i) > 0))
                    {
                        s_prime_.erase(i);
                        s_.insert(i);
                        change = true;
                    }
                }
            }
        }
        double weight = 0;
        for (const auto &edge : edgeList)
        {
            if (s_.count(edge.u) > 0 && s_prime_.count(edge.v) > 0)
            {
                weight += edge.wt;
            }
            if (s_.count(edge.v) > 0 && s_prime_.count(edge.u) > 0)
            {
                weight += edge.wt;
            }
        }
        MaxCutResult m(s_, s_prime_, weight);
        return m;
    }
};

int main()
{
    
}