
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include "Player.h"
using namespace std;


int main() {
    Board board;
    Player player0(0, 4);
    Player player1(1, 4);

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


    std::cout<<"Cleaning up..."<<std::endl;
    board.cleanup();
    std::cout << board << std::endl;
    int winner = board.getWinner();
    if (winner == -1) {
        std::cout << "Draw" << std::endl;
    } else {
        std::cout << "Winner " << winner << std::endl;
    }

    return 0;
}






