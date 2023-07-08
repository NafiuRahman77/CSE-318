#include <bits/stdc++.h>
#include "Board.h"
class Player {
private:
    int id;
    int heuristic;
    int extraMoves;
    static constexpr int DEPTH = 8;
    static constexpr int W1 = 1;
    static constexpr int W2 = 1;
    static constexpr int W3 = 1;
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
                    currentVal = minimaxAlgo(board, boardCopy, true, depth - 1, alpha, beta);

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
                    currentVal = minimaxAlgo(board, boardCopy, false, depth - 1, alpha, beta);
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
            int addmoves;
            if(board.currentPlayer==0){
                addmoves=board.getAdditionalMoveEarned0();
            }
            else{
                addmoves=board.getAdditionalMoveEarned1();
            }
            return W1 * (board.getStores()[id] - board.getStores()[1 - id]) + W2 * (firstPit - secondPit) + W3 * addmoves;
        } else if (heuristic == 4) {
            const auto& a = board.getPits();
            int firstPit = 0, secondPit = 0;
            for (int i = 0; i < 6; i++) {
                firstPit += a[id][i];
            }
            for (int i = 0; i < 6; i++) {
                secondPit += a[1 - id][i];
            }

            int captured;

             int addmoves;
                if(board.currentPlayer==0){
                addmoves=board.getAdditionalMoveEarned0();
                }
                else{
                addmoves=board.getAdditionalMoveEarned1();
                }
                if(board.currentPlayer==0){
                captured=board.getStonesCaptured0();
                }
                else{
                captured=board.getStonesCaptured1();
                }
            return W1 * (board.getStores()[id] - board.getStores()[1 - id]) + W2 * (firstPit - secondPit) + W3 * addmoves + W4 * captured;
        } else {
            return -1;
        }
    }
};