public class Player {
    private int playerID;
    private int depth =10; // Maximum depth for the minimax algorithm
    private int heuristic;
    class IntWrapper
    {
        public int value;

        public IntWrapper(int value)
        {
            this.value = value;
        }
    }

    public Player(int id, int heuristic) {
        playerID = id;
        this.heuristic = heuristic;
    }

    public void setDepth(int depth) {
        this.depth = depth;
    }

    public int makeMove(Board board, int pid) {
        // Find the best move using minimax with alpha-beta pruning
        Pair<Integer, Integer> res=new Pair<>();
        if(pid==0){
            res = minimax(board,  pid, depth, true, (Integer.MIN_VALUE), (Integer.MAX_VALUE));
        }
        else
        {
            res = minimax(board,  pid, depth, false,  (Integer.MIN_VALUE), (Integer.MAX_VALUE));
        }

        return res.second;
    }
    private Pair<Integer, Integer> minimax(Board board, int pid, int depth, boolean isMax, int alpha, int beta) {
        if (depth == 0 || board.gameIsOver()) {
            Pair<Integer, Integer> p = new Pair<>(board.heuristicFunction(heuristic, pid), -1);
            return p;
        }
        if (pid == 0) {
            Pair<Integer, Integer> best = new Pair<>(Integer.MIN_VALUE, -1);
            for (int i = 5; i >= 0; i--) {
                if (board.getPits()[pid][i] == 0) continue;

                Board tempBoard = new Board(board);


                Pair<Integer, Integer> pr=new Pair<>();
                if(tempBoard.makeMove(pid, i)){
                    pr=minimax(tempBoard,  pid, depth - 1, true, alpha, beta);
                }
                else{
                    pr=minimax(tempBoard,  1-pid, depth - 1, false, alpha, beta);
                }

                if (pr.first > best.first) {
                    best.first = pr.first;
                    best.second = i;
                }

                alpha = Math.max(alpha, pr.first);

                if (beta <= alpha)
                    break;
            }
            return best;
        } else {
            Pair<Integer, Integer> best = new Pair<>(Integer.MAX_VALUE, -1);
            for (int i = 0; i < 6; i++) {
                if (board.getPits()[pid][i] == 0) continue;

                Board tempBoard = new Board(board);

                Pair<Integer, Integer> pr=new Pair<>();
                if(tempBoard.makeMove(pid, i)){
                    pr=minimax(tempBoard, pid, depth - 1, false, alpha, beta);
                }
                else{
                    pr=minimax(tempBoard, 1-pid, depth - 1, true, alpha, beta);
                }
                if (pr.first < best.first) {
                    best.first = pr.first;
                    best.second = i;
                }
                beta = Math.min(beta, pr.first);

                if (beta <= alpha)
                    break;
            }
            return best;
        }

    }
}
