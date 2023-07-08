#include <bits/stdc++.h>
class Board {
private:
    std::vector<std::vector<int>> pits;
    std::vector<int> stores;
    int additionalMoveEarned0 ;
    int additionalMoveEarned1 ;
    int stonesCaptured0;
    int stonesCaptured1;


public:
    int currentPlayer;
    Board() {
        pits = std::vector<std::vector<int>>(2, std::vector<int>(6, 4));
        stores = std::vector<int>(2, 0);
        additionalMoveEarned0=0 ;
        additionalMoveEarned1=0 ;
        stonesCaptured0=0;
        stonesCaptured1=0;
    }

    Board(const Board& board) : pits(board.pits), stores(board.stores),currentPlayer(board.currentPlayer),additionalMoveEarned0(board.additionalMoveEarned0),additionalMoveEarned1(board.additionalMoveEarned1),stonesCaptured0(board.stonesCaptured0), stonesCaptured1(board.stonesCaptured1) {}

    std::vector<std::vector<int>> getPits() const {
        return pits;
    }

    std::vector<int> getStores() const {
        return stores;
    }

    int getAdditionalMoveEarned0() const{
    return additionalMoveEarned0;
    }
    int getAdditionalMoveEarned1() const{
    return additionalMoveEarned1;
    }
    int getStonesCaptured0() const{
    return stonesCaptured0;
    }
    int getStonesCaptured1() const{
    return stonesCaptured1;
    }
    void setPits(const std::vector<std::vector<int>>& pits) {
        this->pits = pits;
    }

    void setStores(const std::vector<int>& stores) {
        this->stores = stores;
    }

    void cleanup(){
        bool flag0 = true;
        bool flag1 = true;

        for (int i = 0; i < 6; i++) {
            if (pits[0][i] != 0) {
                flag0 = false;
            }
        }
        if (flag0) { //0 player pit empty
           int sum=0;
           for(int i=0;i<6;i++){
             sum+=pits[1][i];
             pits[1][i]=0;
           }
           stores[1]+=sum;
           return;
        }


        for (int i = 0; i < 6; i++) {
            if (pits[1][i] != 0) {
                flag1 = false;
            }
        }
        if (flag1) { //1 player pit empty
           int sum=0;
           for(int i=0;i<6;i++){
             sum+=pits[0][i];
             pits[0][i]=0;
           }
           stores[0]+=sum;
           return;
        }
    }
    bool gameIsOver() const {
        // Case 1: If no player has any beads left
        if (stores[0] + stores[1] == 48) {
            return true;
        }

        // Case 2: If player #0 has no beads left
        bool flag0 = true;
        bool flag1 = true;
        for (int i = 0; i < 6; i++) {
            if (pits[0][i] != 0) {
                flag0 = false;
            }
        }
        if (flag0) {
            return true;
        }

        // Case 3: If player #1 has no beads left
        for (int i = 0; i < 6; i++) {
            if (pits[1][i] != 0) {
                flag1 = false;
            }
        }
        if (flag1) {
            return true;
        }

        return false;
    }

    int makeMove(int player, int position) {
        int availableBeads = pits[player][position];
        pits[player][position] = 0;
        int currentIndex = position;

        if (player == 1) {
            int opponentId = (1 - player);
            int i = 1;
            int nextPlayer = opponentId;
            bool lastIsStore = false;
            while (availableBeads > 0) {
                if (i == 1) {
                    currentIndex = currentIndex + 1;
                    if (currentIndex > 5) {
                        stores[1]++;
                        i = 0;
                        lastIsStore = true;
                        availableBeads--;
                        continue;
                    }
                    lastIsStore = false;
                    pits[i][currentIndex]++;
                } else {
                    currentIndex = currentIndex - 1;
                    if (currentIndex < 0) {
                        i = 1;
                        lastIsStore = false;
                        continue;
                    }
                    lastIsStore = false;
                    pits[i][currentIndex]++;
                }
                availableBeads--;
            }
            if (lastIsStore) {
                additionalMoveEarned1++;
                currentPlayer=1;
                return 1;
            }
            if (i == 1 && pits[1][currentIndex] == 1 && pits[0][currentIndex] > 0) {
                stores[1] += pits[0][currentIndex] + pits[1][currentIndex];
                stonesCaptured1+=pits[0][currentIndex];
                pits[0][currentIndex] = 0;
                pits[1][currentIndex] = 0;
            }
            currentPlayer=0;
            return 0;
        } else {
            int opponentId = (1 - player);
            int i = 0;
            int nextPlayer = opponentId;
            bool lastIsStore = false;
            while (availableBeads > 0) {
                if (i == 1) {
                    currentIndex = currentIndex + 1;
                    if (currentIndex > 5) {
                        i = 0;
                        lastIsStore = false;
                        continue;
                    }
                    lastIsStore = false;
                    pits[i][currentIndex]++;
                } else {
                    currentIndex = currentIndex - 1;
                    if (currentIndex < 0) {
                        stores[0]++;
                        i = 1;
                        lastIsStore = true;
                        availableBeads--;
                        continue;
                    }
                    lastIsStore = false;
                    pits[i][currentIndex]++;
                }
                availableBeads--;
            }
            if (lastIsStore) {
                additionalMoveEarned0++;
                currentPlayer=0;
                return 0;
            }
            if (i == 0 && pits[0][currentIndex] == 1 && pits[1][currentIndex] > 0) {
                stores[0] += pits[1][currentIndex] + pits[0][currentIndex];
                stonesCaptured0+=pits[1][currentIndex];
                pits[1][currentIndex] = 0;
                pits[0][currentIndex] = 0;
            }
            currentPlayer=1;
            return 1;
        }
    }

    int getWinner() const {
        if (stores[0] > stores[1]) {
            return 0;
        } else if (stores[1] > stores[0]) {
            return 1;
        } else {
            return -1;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Board& board) {
        os << "\t";
        for (int i = 0; i < 6; i++) {
            os << board.pits[0][i] << " ";
        }
        os << "\n";
        os << board.stores[0] << "\t\t\t\t\t" << board.stores[1] << "\n";
        os << "\t";
        for (int i = 0; i < 6; i++) {
            os << board.pits[1][i] << " ";
        }
        return os;
    }
};