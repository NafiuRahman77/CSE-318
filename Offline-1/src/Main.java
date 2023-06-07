import java.util.*;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Main {
    public static boolean isSolvable(int[][] board,int k){
        int[] array = Stream.of(board).flatMapToInt(IntStream::of).toArray();

        int inversionCount=0;
        for(int i=0;i<k*k;i++){
            for(int j=i+1;j<k*k;j++){
                if(array[j]<array[i] && array[j]!=0){
                    inversionCount++;
                }
            }
        }
        int blankRow=-1;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if(board[i][j]==0) {
                    blankRow=i;
                }
            }
        }

        if (k%2==0) {
            if(inversionCount%2!=0 && blankRow%2==0){
                return true;
            }
            if(inversionCount%2==0 && blankRow%2!=0){
                return true;
            }
        }
        else{
            if (inversionCount%2==0) {
                return true;
            }

        }
        return false;

    }
    public static boolean equals(int[][] board1,int[][] board2, int k){
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
               if(board1[i][j]!=board2[i][j]){
                   return false;
               }
            }
        }
        return true;
    }
    public static boolean containsList(ArrayList<SearchNode> list, SearchNode s,int k) {
        int flag=0;
        for(int i=0;i<list.size();i++){
            if(equals(list.get(i).board,s.board,k)){
                return true;
            }
        }
        return false;
    }

    public static void solve(int k,int[][] board,Comparator<SearchNode> cmp){
        String method;
        if(cmp.getClass().getName()=="HammingComparator"){
            method="Hamming heuristic";
        }
        else{
            method="Manhattan heuristic";
        }
        PriorityQueue<SearchNode> pq=new PriorityQueue<>(cmp);
        SearchNode initialNode= new SearchNode(k, board, null);
        pq.add(initialNode);
        int exploredNodes=0,expandedNodes=1;
        SearchNode sn=initialNode;
        //HashSet<SearchNode> closedList= new HashSet<>();
        ArrayList<SearchNode> closedList=new ArrayList<>();
        while(!pq.isEmpty()){
            sn=pq.poll();
            exploredNodes++;
            if(sn.isGoalBoard()){
                System.out.println("Solved in "+method);
                System.out.println("Total moves: "+sn.cost);
                System.out.println("Explored node : "+exploredNodes);
                System.out.println("Expanded node : "+expandedNodes);
                break;
            }
            else {
                if(!containsList(closedList,sn,k)){
                    closedList.add(sn);
                }
                closedList.add(sn);
                ArrayList<SearchNode> list = sn.getNeighbors();
                for (int i = 0; i < list.size(); i++) {
                    SearchNode temp = list.get(i);
                    if(!containsList(closedList,temp,k)) {
                        pq.add(temp);
                        expandedNodes++;
                    }
                }
            }
        }
        Stack<SearchNode> nodeStack=new Stack<>();
        while(sn!=null){
            nodeStack.push(sn);
            sn=sn.getPrevNode();
        }
        while(!nodeStack.isEmpty()){
            SearchNode s=nodeStack.pop();
            s.printBoard();
        }

    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int k = sc.nextInt(); // number of rows and columns
        int[][] board = new int[k][k];
        for (int i=0; i<k; i++) {
            for (int j=0; j<k; j++) {
                board[i][j] = sc.nextInt();
            }
        }
        if(isSolvable(board,k)){
            solve(k,board,new ManhattanComparator());
        }
        else{
            System.out.println("The puzzle is unsolvable");
        }


    }
}
