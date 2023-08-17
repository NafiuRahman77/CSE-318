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
    int localSearchAvg;
    int localSearchiter;

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
    vector<int> getRCL_v(const vector<int> &sigma_x_vect, const vector<int> &sigma_y_vect, const vector<int> &sigma_vertex, int mu, const set<int> &v_prime)
    {
        vector<int> rcl;
        for (int i = 0; i < v_prime.size(); i++)
        {
            if (max(sigma_x_vect[i], sigma_y_vect[i]) >= mu)
            {
                rcl.emplace_back(sigma_vertex[i]);
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

    set<int> setDifference(const set<int> &setA, const set<int> &setB)
    {
        set<int> result;
        for (int element : setA)
        {
            if (setB.find(element) == setB.end())
            {
                result.insert(element);
            }
        }

        return result;
    }

    int sigmaCalculator(const set<int> &S, int vertex)
    {
        int sum = 0;
        for (auto i : S)
        {
            sum += adjacencyMatrix[vertex][i];
        }

        return sum;
    }

    void printSet(const set<int> &s)
    {
        for (auto it : s)
        {
            cout << it << " ";
        }
        cout << endl;
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
        set<int> XUY;
        X.insert(selectedEdge.first);
        XUY.insert(selectedEdge.first);
        Y.insert(selectedEdge.second);
        XUY.insert(selectedEdge.second);

        set<int> V;
        set<int> V_prime;

        for (int i = 1; i <= numVertices; i++)
        {
            V.insert(i);
            V_prime.insert(i);
        }
        V_prime.erase(selectedEdge.first);
        V_prime.erase(selectedEdge.second);

        while (!(XUY == V))
        {

            int sigma_x_min = INT_MAX, sigma_y_min = INT_MAX, sigma_x_max = INT_MIN, sigma_y_max = INT_MIN;

            vector<int> sigma_x_vect(numVertices + 1, 0);
            vector<int> sigma_y_vect(numVertices + 1, 0);
            vector<int> sigma_vertex;

            for (auto vertex : V_prime)
            {
                int sigma_x = sigmaCalculator(Y, vertex);
                int sigma_y = sigmaCalculator(X, vertex);

                // sigma_x_vect.push_back(sigma_x);
                // sigma_y_vect.push_back(sigma_y);
                sigma_x_vect[vertex] = sigma_x;
                sigma_y_vect[vertex] = sigma_y;
                sigma_vertex.push_back(vertex);
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
            // vector<int> rcl_v = getRCL_v(sigma_x_vect, sigma_y_vect, sigma_vertex, mu, V_prime);
            // int selectedVertex = rcl_v[rand() % rcl_v.size()];
            // for (int i : rcl_v)
            // {
            //     if (sigma_vertex[i] == selectedVertex)
            //     {
            //         selectedVertex = i;
            //         break;
            //     }
            // }
            vector<int> restricted_candidate_vertex_list;
            int selectedVertex;
            for (auto i : V_prime)
            {
                if (max(sigma_x_vect[i], sigma_y_vect[i]) >= Wmax)
                {
                    // cout<<"bop"<<endl;
                    restricted_candidate_vertex_list.push_back(i);
                }
            }

            int r = rand() % restricted_candidate_vertex_list.size();
            selectedVertex = restricted_candidate_vertex_list[r];

            if (sigma_x_vect[selectedVertex] > sigma_y_vect[selectedVertex])
            {
                X.insert(selectedVertex);
                XUY.insert(selectedVertex);
                V_prime.erase(selectedVertex);
            }
            else
            {
                Y.insert(selectedVertex);
                XUY.insert(selectedVertex);
                V_prime.erase(selectedVertex);
            }
        }

        double weight = 0;
        for (const auto &e : edgeList)
        {
            if (X.count(e.u) > 0 && Y.count(e.v) > 0)
            {
                weight += e.wt;
            }
            if (X.count(e.v) > 0 && Y.count(e.u) > 0)
            {
                weight += e.wt;
            }
        }
        MaxCutResult m(X, Y, weight);
        return m;
    }

    MaxCutResult GreedyMaxCut()
    {
        srand(1);

        int Wmax = getWmax();

        pair<int, int> selectedEdge;
        for (const auto &e : edgeList)
        {
            if (e.wt == Wmax)
            {
                selectedEdge.first = e.u;
                selectedEdge.second = e.v;
            }
        }
        // cout<<selectedEdge.first<<selectedEdge.second<<endl;

        set<int> X;
        set<int> Y;
        set<int> XUY;
        X.insert(selectedEdge.first);
        XUY.insert(selectedEdge.first);
        Y.insert(selectedEdge.second);
        XUY.insert(selectedEdge.second);

        set<int> V;
        set<int> V_prime;

        for (int i = 1; i <= numVertices; i++)
        {
            V.insert(i);
            V_prime.insert(i);
        }
        V_prime.erase(selectedEdge.first);
        V_prime.erase(selectedEdge.second);

        while (!(XUY == V))
        {

            int sigma_x_min = INT_MAX, sigma_y_min = INT_MAX, sigma_x_max = INT_MIN, sigma_y_max = INT_MIN;

            vector<int> sigma_x_vect(numVertices + 1, 0);
            vector<int> sigma_y_vect(numVertices + 1, 0);
            vector<int> sigma_vertex;

            for (auto vertex : V_prime)
            {
                int sigma_x = sigmaCalculator(Y, vertex);
                int sigma_y = sigmaCalculator(X, vertex);

                // sigma_x_vect.push_back(sigma_x);
                // sigma_y_vect.push_back(sigma_y);
                sigma_x_vect[vertex] = sigma_x;
                sigma_y_vect[vertex] = sigma_y;
                sigma_vertex.push_back(vertex);

                if (sigma_x > sigma_x_max)
                {
                    sigma_x_max = sigma_x;
                }
                if (sigma_y > sigma_y_max)
                {
                    sigma_y_max = sigma_y;
                }
            }

            Wmax = max(sigma_x_max, sigma_y_max);
            // cout<<Wmax<<endl;
            vector<int> restricted_candidate_vertex_list;
            int selectedVertex;
            for (auto i : V_prime)
            {
                if (max(sigma_x_vect[i], sigma_y_vect[i]) >= Wmax)
                {
                    // cout<<"bop"<<endl;
                    restricted_candidate_vertex_list.push_back(i);
                }
            }

            int r = rand() % restricted_candidate_vertex_list.size();
            selectedVertex = restricted_candidate_vertex_list[r];

            if (sigma_x_vect[selectedVertex] > sigma_y_vect[selectedVertex])
            {
                X.insert(selectedVertex);
                XUY.insert(selectedVertex);
                V_prime.erase(selectedVertex);
            }
            else
            {
                Y.insert(selectedVertex);
                XUY.insert(selectedVertex);
                V_prime.erase(selectedVertex);
            }
        }

        double weight = 0;

        for (const auto &e : edgeList)
        {
            if (X.count(e.u) > 0 && Y.count(e.v) > 0)
            {
                weight += e.wt;
            }
            if (X.count(e.v) > 0 && Y.count(e.u) > 0)
            {
                weight += e.wt;
            }
        }

        MaxCutResult m(X, Y, weight);
        return m;
    }

    MaxCutResult RandomizedMaxCut()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        double alpha = 0;
        int Wmin = getWmin();
        int Wmax = getWmax();
        double mu = Wmin + alpha * (Wmax - Wmin);

        vector<pair<int, int>> rcl_e = getRCL_e(mu);
        int randomIndex = rand() % rcl_e.size();

        pair<int, int> selectedEdge = rcl_e[randomIndex];

        set<int> X;
        set<int> Y;
        set<int> XUY;
        X.insert(selectedEdge.first);
        XUY.insert(selectedEdge.first);
        Y.insert(selectedEdge.second);
        XUY.insert(selectedEdge.second);

        set<int> V;
        set<int> V_prime;

        for (int i = 1; i <= numVertices; i++)
        {
            V.insert(i);
            V_prime.insert(i);
        }
        V_prime.erase(selectedEdge.first);
        V_prime.erase(selectedEdge.second);

        while (!(XUY == V))
        {

            int sigma_x_min = INT_MAX, sigma_y_min = INT_MAX, sigma_x_max = INT_MIN, sigma_y_max = INT_MIN;

            vector<int> sigma_x_vect(numVertices + 1, 0);
            vector<int> sigma_y_vect(numVertices + 1, 0);
            vector<int> sigma_vertex;

            for (auto vertex : V_prime)
            {
                int sigma_x = sigmaCalculator(Y, vertex);
                int sigma_y = sigmaCalculator(X, vertex);

                // sigma_x_vect.push_back(sigma_x);
                // sigma_y_vect.push_back(sigma_y);
                sigma_x_vect[vertex] = sigma_x;
                sigma_y_vect[vertex] = sigma_y;
                sigma_vertex.push_back(vertex);
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
           
            vector<int> restricted_candidate_vertex_list;
            int selectedVertex;
            for (auto i : V_prime)
            {
                if (max(sigma_x_vect[i], sigma_y_vect[i]) >= Wmax)
                {
                    // cout<<"bop"<<endl;
                    restricted_candidate_vertex_list.push_back(i);
                }
            }

            int r = rand() % restricted_candidate_vertex_list.size();
            selectedVertex = restricted_candidate_vertex_list[r];

            if (sigma_x_vect[selectedVertex] > sigma_y_vect[selectedVertex])
            {
                X.insert(selectedVertex);
                XUY.insert(selectedVertex);
                V_prime.erase(selectedVertex);
            }
            else
            {
                Y.insert(selectedVertex);
                XUY.insert(selectedVertex);
                V_prime.erase(selectedVertex);
            }
        }

        double weight = 0;
        for (const auto &e : edgeList)
        {
            if (X.count(e.u) > 0 && Y.count(e.v) > 0)
            {
                weight += e.wt;
            }
            if (X.count(e.v) > 0 && Y.count(e.u) > 0)
            {
                weight += e.wt;
            }
        }
        MaxCutResult m(X, Y, weight);
        return m;
    }
    MaxCutResult LocalSearch(const set<int> &s, const set<int> &s_prime)
    {
        set<int> s_ = s;
        // s_.insert(s.begin(), s.end());
        set<int> s_prime_ = s_prime;
        // s_prime_.insert(s_prime.begin(), s_prime.end());
        bool change = true;
        int iter = 0;
        while (change)
        {
            change = false;
            iter++;
            for (int i = 1; i <= numVertices; i++)
            {
                int sigma_s = sigmaCalculator(s_, i);
                int sigma_s_prime = sigmaCalculator(s_prime_, i);
                if (change == true)
                {
                    break;
                }
                if ((sigma_s > sigma_s_prime && s_.count(i) > 0))
                {
                    s_.erase(i);
                    s_prime_.insert(i);
                    change = true;
                }
                else
                {
                    if ((sigma_s_prime > sigma_s && s_prime_.count(i) > 0))
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
        m.localSearchiter = iter;
        return m;
    }

    MaxCutResult GRASP()
    {
        int w_star = INT_MIN;
        MaxCutResult result;
        int avgval = 0;
        int avgiter = 0;
        for (int i = 0; i < 50; i++)
        {
            MaxCutResult m1;
            m1 = SemiGreedyMaxCut();
            MaxCutResult m2;
            m2 = LocalSearch(m1.s, m1.s_prime);
            avgval += m2.maxCutValue;
            avgiter += m2.localSearchiter;
            if (m2.maxCutValue > w_star)
            {
                w_star=m2.maxCutValue;
                result = m2;
            }
        }
        avgval = avgval / 50;
        avgiter = avgiter / 50;
        result.localSearchAvg = avgval;
        result.localSearchiter = avgiter;
        return result;
    }
};

int main()
{

    int n, m; // Number of vertices and edges
    std::ifstream inputFile("a.rud");

    if (!inputFile)
    {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    inputFile >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; ++i)
    {
        int v1, v2;
        int wt;
        inputFile >> v1 >> v2 >> wt;
        g.addEdge(v1, v2, wt);
    }

    cout << g.GreedyMaxCut().maxCutValue << endl;
    int semiGreedyavg = 0;
    for (int i = 0; i < 10; i++)
    {
        semiGreedyavg += g.SemiGreedyMaxCut().maxCutValue;
    }
    cout << semiGreedyavg / 10 << endl;
    int randavg = 0;
    for (int i = 0; i < 10; i++)
    {
        randavg += g.RandomizedMaxCut().maxCutValue;
    }
    cout << randavg / 10 << endl;

    cout << (g.GRASP().maxCutValue) << " " << g.GRASP().localSearchAvg << " " << g.GRASP().localSearchiter << endl;
}