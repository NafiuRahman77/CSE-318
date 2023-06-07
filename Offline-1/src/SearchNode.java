import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;

public class SearchNode {
    public int k; // size of the board
    public int[][] board;
    private SearchNode prevNode;
    int cost;

    public SearchNode(int k, int[][] board, SearchNode prevNode) {
        this.k = k;
        this.board = board;
        this.prevNode = prevNode;
        if(this.prevNode==null){
            this.cost=0;
        }
        else{
            this.cost=prevNode.cost+1;
        }
    }

    int manhattanHeuristic(){
       int heuristicCost=0;
       int actualRow=-1, actualColumn=-1;
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                if(board[i][j]!=0  ){
                    actualRow= ((int) Math.ceil((double)board[i][j]/k))-1;
                    if(board[i][j]%k==0){
                        actualColumn=k-1;
                    }
                    else{
                        actualColumn=(board[i][j]%k)-1;
                    }
                    heuristicCost+=Math.abs(actualRow-i)+Math.abs(actualColumn-j);
                }
            }
        }

       return heuristicCost;
    }

    int hammingHeuristic(){
        int heuristicCost=0;
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                if(board[i][j]!=0 && board[i][j]!=this.k*i+j+1 ){
                    heuristicCost++;
                }
            }
        }
        return heuristicCost;
    }
    int[][] swap(int i1, int j1, int i2, int j2){
        int[][] res=new int[k][k];
        int temp;
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                res[i][j]=board[i][j];
            }
        }

        temp=res[i1][j1];
        res[i1][j1]=res[i2][j2];
        res[i2][j2]=temp;

        return res;
    }

    ArrayList<SearchNode> getNeighbors(){
        ArrayList<SearchNode> list=new ArrayList<>();

        //find the zero row and column
        int zeroRow=-1;
        int zeroCol=-1;
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                if(board[i][j]==0){
                    zeroRow=i;
                    zeroCol=j;
                }
            }
        }

        if(zeroCol!=k-1) {
            int[][] res1=swap(zeroRow,zeroCol,zeroRow,zeroCol+1);
            SearchNode s1 = new SearchNode(k, res1, this);
            list.add(s1);
        }
        if(zeroCol!=0) {
            int[][] res2=swap(zeroRow,zeroCol,zeroRow,zeroCol-1);
            SearchNode s2 = new SearchNode(k, res2, this);
            list.add(s2);
        }
        if(zeroRow!=k-1) {
            int[][] res3=swap(zeroRow,zeroCol,zeroRow+1,zeroCol);
            SearchNode s3 = new SearchNode(k, res3, this);
            list.add(s3);
        }
        if(zeroRow!=0) {
            int[][] res4=swap(zeroRow,zeroCol,zeroRow-1,zeroCol);
            SearchNode s4 = new SearchNode(k, res4, this);
            list.add(s4);
        }

        return list;
    }
    boolean isGoalBoard(){
        int[][] goalBoard=new int[k][k];
        int temp=1;
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                goalBoard[i][j]=temp;
                temp++;
            }
        }
        goalBoard[k-1][k-1]=0;
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                if(board[i][j]!=goalBoard[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    void printBoard(){
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                System.out.print(board[i][j]+" ");
            }
            System.out.println();
        }
        System.out.println();

    }

    public SearchNode getPrevNode() {
        return prevNode;
    }



}
