import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static void runGameAndGenerateReport() {
        List<String[]> results = new ArrayList<>();

        for (int heuristic1 = 1; heuristic1 <= 4; heuristic1++) {
            for (int depth1 = 1; depth1 <= 10; depth1++) {
                for (int heuristic2 = 1; heuristic2 <= 4; heuristic2++) {
                    for (int depth2 = 1; depth2 <= 10; depth2++) {
                        // Initialize players with current heuristics and depths
                        Player player0 = new Player(0, heuristic1);
                        player0.setDepth(depth1);
                        Player player1 = new Player(1, heuristic2);
                        player1.setDepth(depth2);

                        int turn = 0;
                        int move = 1;
                        Board board = new Board();

                        while (true) {
                            if (board.gameIsOver()) {
                                int winner = board.getWinner();
                                String[] result = {Integer.toString(heuristic1), Integer.toString(depth1),
                                        Integer.toString(heuristic2), Integer.toString(depth2),
                                        (winner == -1) ? "Draw" : Integer.toString(winner)};
                                results.add(result);
                                break;
                            }

                            if (turn == 0) {
                                move = player0.makeMove(new Board(board), turn);
                                boolean b = board.makeMove(turn, move);
                                if (b) {
                                    continue;
                                }
                                turn = 1;
                            } else {
                                move = player1.makeMove(new Board(board), turn);
                                boolean b = board.makeMove(turn, move);
                                if (b) {
                                    continue;
                                }
                                turn = 0;
                            }
                        }
                    }
                }
            }
        }

        // Generate CSV report
        try {
            FileWriter csvWriter = new FileWriter("report.csv");
            csvWriter.append("Heuristic1,Depth1,Heuristic2,Depth2,Winner\n");
            for (String[] result : results) {
                csvWriter.append(String.join(",", result));
                csvWriter.append("\n");
            }
            csvWriter.flush();
            csvWriter.close();
            System.out.println("Report generated successfully!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void HumanVsAi(){

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

//        System.out.println("Select your choice 1.Player vs Ai 2. Ai vs Ai");
//        Scanner sc=new Scanner(System.in);
//        int a=sc.nextInt();
//        if(a==1){
//           HumanVsAi();
//        }
//        else{
//            AiVsVi();
//        }
        runGameAndGenerateReport();
    }
}
