
#include <iostream>
#include <vector>
#include <cmath>
#include<bits/stdc++.h>

using namespace std;

struct BoardHash {
    std::size_t operator()(const std::vector<std::vector<int>>& board) const {
        std::size_t seed = board.size();
        for (const auto& row : board) {
            for (const auto& value : row) {
                seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};


int manhattanHeuristic(vector<vector<int>> board,int k) {

        int heuristicCost = 0;
        int actualRow = -1, actualColumn = -1;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (board[i][j] != 0) {
                    actualRow = (board[i][j] - 1) / k;
                    actualColumn = ((board[i][j] - 1) % k);
                    heuristicCost += abs(actualRow - i) + abs(actualColumn - j);
                }
            }
        }
        return heuristicCost;
    }

int hammingHeuristic(vector<vector<int>> board,int k) {
        int heuristicCost = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (board[i][j] != 0 && board[i][j] != k * i + j + 1) {
                    heuristicCost++;
                }
            }
        }
        return heuristicCost;
}

class SearchNode {
public:
    int k; // size of the board
    vector<vector<int>> board;
    SearchNode* prevNode;
    int cost;

    SearchNode(int k, const vector<vector<int>>& board, SearchNode* prevNode)
        : k(k), board(board), prevNode(prevNode) {
        if (prevNode == nullptr) {
            cost = 0;
        } else {
            cost = prevNode->cost + 1;
        }
    }

    int getK() const {
        return k;
    }

    vector<vector<int>> getBoard() const {
        return board;
    }

    void setPrevNode(SearchNode* prevNode) {
        this->prevNode = prevNode;
    }

    int getCost() const {
        return cost;
    }

    void setCost(int cost) {
        this->cost = cost;
    }

    SearchNode* getPrevNode() const {
        return prevNode;
    }

    vector<vector<int>> swap(int i1, int j1, int i2, int j2) {
        vector<vector<int>> res = board;
        int temp = res[i1][j1];
        res[i1][j1] = res[i2][j2];
        res[i2][j2] = temp;
        return res;
    }

    vector<SearchNode*> getNeighbors() {
        vector<SearchNode*> list;

        // Find the zero row and column
        int zeroRow = -1;
        int zeroCol = -1;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (board[i][j] == 0) {
                    zeroRow = i;
                    zeroCol = j;
                }
            }
        }

        if (zeroCol != k - 1) {
            vector<vector<int>> res1 = swap(zeroRow, zeroCol, zeroRow, zeroCol + 1);
            SearchNode* s1 = new SearchNode(k, res1, this);
            list.push_back(s1);
        }
        if (zeroCol != 0) {
            vector<vector<int>> res2 = swap(zeroRow, zeroCol, zeroRow, zeroCol - 1);
            SearchNode* s2 = new SearchNode(k, res2, this);
            list.push_back(s2);
        }
        if (zeroRow != k - 1) {
            vector<vector<int>> res3 = swap(zeroRow, zeroCol, zeroRow + 1, zeroCol);
            SearchNode* s3 = new SearchNode(k, res3, this);
            list.push_back(s3);
        }
        if (zeroRow != 0) {
            vector<vector<int>> res4 = swap(zeroRow, zeroCol, zeroRow - 1, zeroCol);
            SearchNode* s4 = new SearchNode(k, res4, this);
            list.push_back(s4);
        }

        return list;
    }

    bool isGoalBoard() {
        vector<vector<int>> goalBoard(k, vector<int>(k));
        int temp = 1;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                goalBoard[i][j] = temp;
                temp++;
            }
        }
        goalBoard[k - 1][k - 1] = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (board[i][j] != goalBoard[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    void printBoard() {
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

struct ManhattanComparator {
    bool operator()( SearchNode* o1,  SearchNode* o2) {
        return (o1->cost + manhattanHeuristic(o1->getBoard(),o1->getK())) > (o2->cost + manhattanHeuristic(o2->getBoard(),o2->getK()));
    }
};

struct HammingComparator {
    bool operator()( SearchNode* o1,  SearchNode* o2) {
        return (o1->cost + hammingHeuristic(o1->getBoard(),o1->getK())) > (o2->cost + hammingHeuristic(o2->getBoard(),o2->getK()));
    }
};

bool isSolvable(const vector<vector<int>>& board, int k) {
    vector<int> array;
    for (const auto& row : board) {
        array.insert(array.end(), row.begin(), row.end());
    }

    int inversionCount = 0;
    for (int i = 0; i < k * k; i++) {
        for (int j = i + 1; j < k * k; j++) {
            if (array[j] < array[i] && array[j] != 0) {
                inversionCount++;
            }
        }
    }

    int blankRow = -1;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (board[i][j] == 0) {
                blankRow = i;
            }
        }
    }

    if (k % 2 == 0) {
        if (inversionCount % 2 != 0 && blankRow % 2 == 0) {
            return true;
        }
        if (inversionCount % 2 == 0 && blankRow % 2 != 0) {
            return true;
        }
    } else {
        if (inversionCount % 2 == 0) {
            return true;
        }
    }

    return false;
}



void solveManhattan(int k, const vector<vector<int>>& board, const ManhattanComparator& cmp) {
    string method;

    method = "Manhattan heuristic";

    int cnt = 0;
    priority_queue<SearchNode*, vector<SearchNode*>, ManhattanComparator> pq(cmp);
    SearchNode* initialNode = new SearchNode(k, board, nullptr);
    pq.push(initialNode);
    int exploredNodes = 0, expandedNodes = 1;
    SearchNode* sn = initialNode;
    vector<SearchNode*> closedList;

    unordered_set<vector<vector<int>>, BoardHash> visitedStates;
    while (!pq.empty()) {
        cout << cnt << endl;
        cnt++;
        sn = pq.top();
        pq.pop();
        exploredNodes++;

        if (sn->isGoalBoard()) {
            break;
        }
        else {
           if (visitedStates.find(sn->board) == visitedStates.end()) {
                visitedStates.insert(sn->board);

                vector<SearchNode*> list = sn->getNeighbors();
                for (int i = 0; i < list.size(); i++) {
                    SearchNode* temp = list[i];
                    if (visitedStates.find(temp->board) == visitedStates.end()) {
                        pq.push(temp);
                        expandedNodes++;
                    }
                }
            }
        }
    }

    cout << "Solved in " << method << endl;
    cout << "Total moves: " << sn->cost << endl;
    cout << "Explored node: " << exploredNodes << endl;
    cout << "Expanded node: " << expandedNodes << endl;

    stack<SearchNode*> nodeStack;
    while (sn != nullptr) {
        nodeStack.push(sn);
        sn = sn->prevNode;
    }

    while (!nodeStack.empty()) {
        SearchNode* s = nodeStack.top();
        nodeStack.pop();
        s->printBoard();
    }
}


void solveHamming(int k, const vector<vector<int>>& board, const HammingComparator& cmp) {
    string method;

    method = "Hamming heuristic";

    int cnt = 0;
    priority_queue<SearchNode*, vector<SearchNode*>, HammingComparator> pq(cmp);
    SearchNode* initialNode = new SearchNode(k, board, nullptr);
    pq.push(initialNode);
    int exploredNodes = 0, expandedNodes = 1;
    SearchNode* sn = initialNode;
    vector<SearchNode*> closedList;

    unordered_set<vector<vector<int>>, BoardHash> visitedStates;
    while (!pq.empty()) {
        cout << cnt << endl;
        cnt++;
        sn = pq.top();
        pq.pop();
        exploredNodes++;

        if (sn->isGoalBoard()) {
            break;
        }
        else {
           if (visitedStates.find(sn->board) == visitedStates.end()) {
                visitedStates.insert(sn->board);

                vector<SearchNode*> list = sn->getNeighbors();
                for (int i = 0; i < list.size(); i++) {
                    SearchNode* temp = list[i];
                    if (visitedStates.find(temp->board) == visitedStates.end()) {
                        pq.push(temp);
                        expandedNodes++;
                    }
                }
            }
        }
    }

    cout << "Solved in " << method << endl;
    cout << "Total moves: " << sn->cost << endl;
    cout << "Explored node: " << exploredNodes << endl;
    cout << "Expanded node: " << expandedNodes << endl;

    stack<SearchNode*> nodeStack;
    while (sn != nullptr) {
        nodeStack.push(sn);
        sn = sn->prevNode;
    }

    while (!nodeStack.empty()) {
        SearchNode* s = nodeStack.top();
        nodeStack.pop();
        s->printBoard();
    }
}

int main() {
    int k;
    cin >> k; // number of rows and columns

    vector<vector<int>> board(k, vector<int>(k));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            cin >> board[i][j];
        }
    }

    if (isSolvable(board, k)) {
        cout<<"Enter your choice 1.Manhattan 2.Hamming"<<endl;
        int choice;
        cin>>choice;
        if(choice==1){
            ManhattanComparator cmp;
            solveManhattan(k, board, cmp);
        }
        else{
            HammingComparator cmp;
            solveHamming(k, board, cmp);
        }
    } else {
        cout << "The puzzle is unsolvable" << endl;
    }

    return 0;
}
