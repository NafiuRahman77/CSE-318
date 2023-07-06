
#include <iostream>
#include <vector>
#include <algorithm>

class Board {
private:
    std::vector<std::vector<int>> pits;
    std::vector<int> stores;

public:
    Board() {
        pits = std::vector<std::vector<int>>(2, std::vector<int>(6, 4));
        stores = std::vector<int>(2, 0);
    }

    Board(const Board& board) : pits(board.pits), stores(board.stores) {}

    std::vector<std::vector<int>> getPits() const {
        return pits;
    }

    std::vector<int> getStores() const {
        return stores;
    }

    void setPits(const std::vector<std::vector<int>>& pits) {
        this->pits = pits;
    }

    void setStores(const std::vector<int>& stores) {
        this->stores = stores;
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
                return 1;
            }
            if (i == 1 && pits[1][currentIndex] == 1 && pits[0][currentIndex] > 0) {
                stores[1] += pits[0][currentIndex] + pits[1][currentIndex];
                pits[0][currentIndex] = 0;
                pits[1][currentIndex] = 0;
            }
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
                return 0;
            }
            if (i == 0 && pits[0][currentIndex] == 1 && pits[1][currentIndex] > 0) {
                stores[0] += pits[1][currentIndex] + pits[0][currentIndex];
                pits[1][currentIndex] = 0;
                pits[0][currentIndex] = 0;
            }
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

class Player {
private:
    int id;
    int heuristic;
    int extraMoves;
    static constexpr int DEPTH = 7;
    static constexpr int W1 = 5;
    static constexpr int W2 = 1;
    static constexpr int W3 = 10;
    static constexpr int W4 = 1;

public:
    Player(int id, int heuristic) : id(id), heuristic(heuristic), extraMoves(0) {}

    int chooseMove(Board& board) {
        extraMoves = 0;
        int move = minimaxAlgo(board, board, true, DEPTH, INT_MIN, INT_MAX);
        return move;
    }

private:
    int minimaxAlgo(Board& board, const Board& oldBoard, bool isMax, int depth, int alpha, int beta) {
        if (depth == 0 || board.gameIsOver()) {
            return evaluate(board, oldBoard, heuristic);
        }

        if (isMax) {
            Board boardCopy(board);
            int bestValue = INT_MIN;
            int move = -1;
            for (int i = 0; i < 6; i++) {
                if (board.getPits()[id][i] == 0) {
                    continue;
                }
                int nextPlayer = board.makeMove(id, i);
                int currentVal = 1;
                if (nextPlayer == id) {
                    extraMoves++;
                    currentVal = minimaxAlgo(board, boardCopy, true, depth - 1, alpha, beta);
                    extraMoves--;
                } else {
                    currentVal = minimaxAlgo(board, boardCopy, false, depth - 1, alpha, beta);
                }
                if (currentVal > bestValue) {
                    bestValue = currentVal;
                    move = i;
                }
                alpha = std::max(alpha, bestValue);
                if (beta <= alpha) {
                    break;
                }
                board.setPits(boardCopy.getPits());
                board.setStores(boardCopy.getStores());
            }
            return (depth == DEPTH) ? move : bestValue;
        } else {
            Board boardCopy(board);
            int bestValue = INT_MAX;
            int move = -1;
            for (int i = 0; i < 6; i++) {
                if (board.getPits()[1 - id][i] == 0) {
                    continue;
                }
                int nextPlayer = board.makeMove(1 - id, i);
                int currentVal = 1;
                if (nextPlayer == 1 - id) {
                    extraMoves++;
                    currentVal = minimaxAlgo(board, boardCopy, false, depth - 1, alpha, beta);
                    extraMoves--;
                } else {
                    currentVal = minimaxAlgo(board, boardCopy, true, depth - 1, alpha, beta);
                }
                if (currentVal < bestValue) {
                    bestValue = currentVal;
                }
                beta = std::min(beta, bestValue);
                if (beta <= alpha) {
                    break;
                }
                board.setPits(boardCopy.getPits());
                board.setStores(boardCopy.getStores());
            }
            return bestValue;
        }
    }

    int evaluate(const Board& board, const Board& oldBoard, int heuristic) {
        if (heuristic == 1) {
            return board.getStores()[id] - board.getStores()[1 - id];
        } else if (heuristic == 2) {
            const auto& a = board.getPits();
            int firstPit = 0, secondPit = 0;
            for (int i = 0; i < 6; i++) {
                firstPit += a[id][i];
            }
            for (int i = 0; i < 6; i++) {
                secondPit += a[1 - id][i];
            }
            return W1 * (board.getStores()[id] - board.getStores()[1 - id]) + W2 * (firstPit - secondPit);
        } else if (heuristic == 3) {
            const auto& a = board.getPits();
            int firstPit = 0, secondPit = 0;
            for (int i = 0; i < 6; i++) {
                firstPit += a[id][i];
            }
            for (int i = 0; i < 6; i++) {
                secondPit += a[1 - id][i];
            }
            return W1 * (board.getStores()[id] - board.getStores()[1 - id]) + W2 * (firstPit - secondPit) + W3 * extraMoves;
        } else if (heuristic == 4) {
            const auto& a = board.getPits();
            int firstPit = 0, secondPit = 0;
            for (int i = 0; i < 6; i++) {
                firstPit += a[id][i];
            }
            for (int i = 0; i < 6; i++) {
                secondPit += a[1 - id][i];
            }

            int captured = 0;

            for (int i = 0; i < 6; i++) {
                int oldPitValue = oldBoard.getPits()[id][i];
                int currentPitValue = board.getPits()[id][i];
                int oppositePitValue = oldBoard.getPits()[1 - id][5 - i];
                int oppositeCurrentPitValue = board.getPits()[1 - id][5 - i];

                if (oldPitValue == 0 && currentPitValue == 0 && oppositePitValue != 0 && oppositeCurrentPitValue == 0) {
                    captured += oppositePitValue;
                }
            }
            return W1 * (board.getStores()[id] - board.getStores()[1 - id]) + W2 * (firstPit - secondPit) + W3 * extraMoves + W4 * captured;
        } else {
            return -1;
        }
    }
};

int main() {
    Board board;
    Player player0(0, 3);
    Player player1(1, 3);

    int turn = 0, prevTurn = -1;
    int move = 1;

    std::cout << board << std::endl;
    while (!board.gameIsOver()) {
        if (turn == 0) {
            move = player0.chooseMove(board);
            std::cout << "Player 0 chooses move " << move << std::endl;

        } else {
            move = player1.chooseMove(board);
            std::cout << "Player 1 chooses move " << move << std::endl;
        }

        turn = board.makeMove(turn, move);
        std::cout << board << std::endl;
    }

    int winner = board.getWinner();
    if (winner == -1) {
        std::cout << "Draw" << std::endl;
    } else {
        std::cout << "Winner " << winner << std::endl;
    }

    return 0;
}







