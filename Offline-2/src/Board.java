import java.util.Arrays;

class Board {
    private int[][] pits;
    private int[] stores;
    private int W1 = 1;
    private int W2 = 2;
    private int W3 = 3;
    private int W4 = 4;

    private int additionalMoves0;
    private int additionalMoves1;

    private int stonesCaptured0;
    private int stonesCaptured1;

    public int currentPlayer;

    public Board() {
        pits = new int[][]{{4, 4, 4, 4, 4, 4}, {4, 4, 4, 4, 4, 4}};
        stores = new int[]{0, 0};
    }
    public Board(Board b) {
        int[][] temp=new int[2][6];
        int[] temp1=new int[2];
        for(int i=0;i<6;i++){
            temp[0][i]=b.pits[0][i];
            temp[1][i]=b.pits[1][i];
        }
        temp1[0]=b.stores[0];
        temp1[1]=b.stores[1];
        this.pits = temp;
        this.stores = temp1;
        this.currentPlayer=b.currentPlayer;
        this.additionalMoves0=b.additionalMoves0;
        this.additionalMoves1=b.additionalMoves1;
        this.stonesCaptured0=b.stonesCaptured0;
        this.stonesCaptured1=b.stonesCaptured1;
    }


    public int[][] getPits() {
        return pits;
    }

    public int[] getStores() {
        return stores;
    }
    void swapPlayer() {
        currentPlayer = 1 -currentPlayer;
    }
    public boolean gameIsOver() {
        boolean flag0 = true;
        boolean flag1 = true;
        for (int i = 0; i < 6; i++) {
            if (pits[0][i] != 0) {
                flag0 = false;
            }
        }
        if (flag0) {
            int sum = 0;
            for (int i = 0; i < 6; i++) {
                sum += pits[1][i];
                pits[1][i] = 0;
            }
            stores[1] += sum;
            return true;
        }

        for (int i = 0; i < 6; i++) {
            if (pits[1][i] != 0) {
                flag1 = false;
            }
        }
        if (flag1) {
            int sum = 0;
            for (int i = 0; i < 6; i++) {
                sum += pits[0][i];
                pits[0][i] = 0;
            }
            stores[0] += sum;
            return true;
        }

        return false;
    }

    public boolean makeMove(int player, int position) {
        int availableBeads = pits[player][position];
        pits[player][position] = 0;
        int currentIndex = position;

        if (player == 1) {
            int opponentId = 1 - player;
            int i = 1;
            int nextPlayer = opponentId;
            boolean lastIsStore = false;
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
                currentPlayer = 1;
                additionalMoves1++;
                return true;
            }
            if (i == 1 && pits[1][currentIndex] == 1 && pits[0][currentIndex] > 0) {
                stonesCaptured1+=pits[0][currentIndex] + pits[1][currentIndex];
                stores[1] += pits[0][currentIndex] + pits[1][currentIndex];
                pits[0][currentIndex] = 0;
                pits[1][currentIndex] = 0;
            }
            currentPlayer = 0;
            return false;
        } else {
            int opponentId = 1 - player;
            int i = 0;
            int nextPlayer = opponentId;
            boolean lastIsStore = false;
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
                currentPlayer = 0;
                additionalMoves0++;
                return true;
            }
            if (i == 0 && pits[0][currentIndex] == 1 && pits[1][currentIndex] > 0) {
                stonesCaptured0+=pits[0][currentIndex] + pits[1][currentIndex];
                stores[0] += pits[1][currentIndex] + pits[0][currentIndex];
                pits[1][currentIndex] = 0;
                pits[0][currentIndex] = 0;
            }
            currentPlayer = 1;
            return false;
        }
    }

    public int getWinner() {
        if (stores[0] > stores[1]) {
            return 0;
        } else if (stores[1] > stores[0]) {
            return 1;
        } else {
            return -1;
        }
    }

    public int heuristicFunction(int heuristic, int playerId) {
        int sum0 = 0, sum1 = 0;
        for (int i = 0; i < 6; i++) {
            sum0 += pits[0][i];
            sum1 += pits[1][i];
        }

        if (heuristic == 1) {
             return stores[0] - stores[1];

        } else if (heuristic == 2) {
            return W1 * (stores[0] - stores[1]) + W2 * (sum0 - sum1);
        }
        else if (heuristic == 3) {
            return W1 * (stores[0] - stores[1]) + W2 * (sum0 - sum1)+W3*(additionalMoves0-additionalMoves1);
        }
        else if (heuristic == 4) {
            return W1 * (stores[0] - stores[1]) + W2 * (sum0 - sum1)+W3*(additionalMoves0-additionalMoves1)+W4*(stonesCaptured0-stonesCaptured1);
        }
        return 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("\t");
        for (int i = 0; i < 6; i++) {
            sb.append(pits[0][i]).append(" ");
        }
        sb.append("\n");
        sb.append(stores[0]).append("\t\t\t\t\t").append(stores[1]).append("\n");
        sb.append("\t");
        for (int i = 0; i < 6; i++) {
            sb.append(pits[1][i]).append(" ");
        }
        return sb.toString();
    }
}
