import java.util.Scanner;

public class Main {
    public static void HumanVsAi(){

        Board board = new Board();
        Player player0 = new Player(0, 2);
        //player0.setDepth(4);
        Player player1 = new Player(1, 2);
        // player1.setDepth(1);

        int turn = 0;
        int move = 1;
        Scanner sc=new Scanner(System.in);

        System.out.println(board);
        while (true) {
            if(board.gameIsOver()){
                System.out.println(board);
                break;
            }
            if (turn == 0) {
               // move = player0.makeMove(new Board(board), turn);
                System.out.println("Enter player 0 move");
                move=sc.nextInt();
                System.out.println("Player 0 chooses move " + move);
                boolean b=board.makeMove(turn, move);
                System.out.println(board);
                if (b) {
                    continue;
                }
                turn = 1;
            } else {
                move = player1.makeMove(new Board(board), turn);
//                System.out.println("Enter player 1 move");
//                move=sc.nextInt();
                System.out.println("Player 1 chooses move " + move);
                boolean b=board.makeMove(turn, move);
                System.out.println(board);
                if (b) {
                    continue;
                }
                turn = 0;
            }


        }

        int winner = board.getWinner();
        if (winner == -1) {
            System.out.println("Draw");
        } else {
            System.out.println("Winner " + winner);
        }
    }
    public static void AiVsVi(){

        Board board = new Board();
        Player player0 = new Player(0, 1);
        //player0.setDepth(4);
        Player player1 = new Player(1, 1);
        // player1.setDepth(1);

        int turn = 0;
        int move = 1;
        Scanner sc=new Scanner(System.in);

        System.out.println(board);
        while (true) {
            if(board.gameIsOver()){
                System.out.println(board);
                break;
            }
            if (turn == 0) {
                move = player0.makeMove(new Board(board), turn);
//                System.out.println("Enter player 0 move");
//                move=sc.nextInt();
                System.out.println("Player 0 chooses move " + move);
                boolean b=board.makeMove(turn, move);
                System.out.println(board);
                if (b) {
                    continue;
                }
                turn = 1;
            } else {
                move = player1.makeMove(new Board(board), turn);
//                System.out.println("Enter player 1 move");
//                move=sc.nextInt();
                System.out.println("Player 1 chooses move " + move);
                boolean b=board.makeMove(turn, move);
                System.out.println(board);
                if (b) {
                    continue;
                }
                turn = 0;
            }


        }

        int winner = board.getWinner();
        if (winner == -1) {
            System.out.println("Draw");
        } else {
            System.out.println("Winner " + winner);
        }
    }
    public static void main(String[] args) {

        System.out.println("Select your choice 1.Player vs Ai 2. Ai vs Ai");
        Scanner sc=new Scanner(System.in);
        int a=sc.nextInt();
        if(a==1){
           HumanVsAi();
        }
        else{
            AiVsVi();
        }
    }
}
