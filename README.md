# CSE 318 Artificial Intelligence Sessional

This repository contains the implementation of various Artificial Intelligence algorithms and methods for assignments in the CSE 318 Artificial Intelligence Sessional course. Each assignment covers a specific topic in AI, including search algorithms, adversarial search, optimization, and decision-tree learning.

---

## Assignments Overview

### **1. Offline-1: Solving the N-Puzzle Problem using A* Search Algorithm**

#### Objective
Solve the n-puzzle problem for a given grid size \( k \times k \), where \( n = k^2 - 1 \). Implement the A* search algorithm using the following heuristics:
1. Hamming Distance: The number of blocks out of place.
2. Manhattan Distance: The sum of the Manhattan distances of the blocks from their goal positions.

#### Tasks
1. Detect whether the given initial board state is solvable.
2. If solvable, output:
   - Optimal cost to reach the goal.
   - Steps to solve the puzzle, showing board states.
   - Number of explored and expanded nodes for both heuristics.

#### Input
- Grid size \( k \).
- Initial board state, with the blank represented as `*`.

#### Output
- Solvability of the input state.
- Optimal solution steps (if solvable).
- Comparison of the explored/expanded nodes for the two heuristics.

#### Files
- `AStarSearch.cpp`

---

### **2. Offline-2: Adversarial Search for Mancala**

#### Objective
Implement a game-playing agent for the two-player game Mancala using the **Minimax Algorithm** with **Alpha-Beta Pruning**. Experiment with heuristics and analyze their performance.

#### Tasks
1. Implement the basic Minimax algorithm with Alpha-Beta Pruning.
2. Experiment with different strategies such as iterative deepening and move-ordering.
3. Implement and evaluate the following heuristics:
   - **Heuristic 1**: Difference in stones between the player's and opponent's storage.
   - **Heuristic 2**: Weighted difference in storage stones and bin stones.
   - **Heuristic 3**: Weighted difference with additional moves earned.
   - **Heuristic 4**: Weighted difference with captured stones.
4. Run experiments with computer vs computer auto-play to find the best heuristic.

#### Files
- `Main.java`
- `Player.java`
- `Board.java`
- `Pair.java`

---

### **3. Offline-3: Solving the Max-Cut Problem using GRASP**

#### Objective
Solve the **Max-Cut Problem** on a given undirected graph using the **Greedy Randomized Adaptive Search Procedure (GRASP)**.

#### Tasks
1. Implement the following methods:
   - Simple Randomized
   - Simple Greedy
   - Semi-Greedy
   - Local Search
   - GRASP
2. Maximize the cut weight \( w(S, \bar{S}) \), where \( S \subseteq V \).

#### Input
- Graph \( G = (V, E) \), with vertex set \( V \), edge set \( E \), and edge weights \( w_{uv} \).

#### Files
- `main.cpp`
- Test cases in the `Test Cases` folder.

---

### **4. Offline-4: Decision Tree Learning for Car Evaluation**

#### Objective
Implement a **Decision Tree Learning Algorithm** to classify cars based on the provided dataset. Use **Information Gain** for attribute selection.

#### Tasks
1. Train a decision tree classifier using 80% of the data and test it on the remaining 20%.
2. Run 20 experiments and report:
   - Mean accuracy.
   - Standard deviation of accuracy.
3. Generate graphs for:
   - Partition size vs Mean Accuracy.
   - Partition size vs Standard Deviation.

#### Files
- `decision_tree.hpp`
- `decision_tree.cpp`
- `car.hpp`
- `car.cpp`
- `dataset.cpp`
- `dataset.hpp`
- Results in the `results` folder.

---

## Usage Instructions

### **Offline-1**
1. Compile: `g++ -o AStarSearch AStarSearch.cpp`
2. Run: `./AStarSearch`
3. Provide input as prompted for grid size and initial board state.

### **Offline-2**
1. Compile: `javac *.java`
2. Run: `java Main`
3. Play or observe auto-play using the implemented heuristics.

### **Offline-3**
1. Compile: `g++ -o maxcut main.cpp`
2. Run: `./maxcut`
3. Provide the graph input file from the `Test Cases` folder.

### **Offline-4**
1. Compile: `g++ -o decision_tree decision_tree.cpp car.cpp dataset.cpp`
2. Run: `./decision_tree`
3. View results and accuracy statistics in the `results` folder.

---

## Prerequisites
- **C++**: Required for Offlines 1, 3, and 4.
- **Java**: Required for Offline 2.
- **Graphing Tools**: Python/Matplotlib or Excel for plotting results (Offline 4).

---

## Results
### Offline-1: A* Search
- Hamming and Manhattan distance heuristics compared.
- Optimal solutions verified for solvable puzzles.

### Offline-2: Mancala
- Win-loss ratio determined for different heuristics.
- Alpha-Beta pruning reduced search space significantly.

### Offline-3: Max-Cut Problem
- GRASP outperformed other methods in most cases.

### Offline-4: Decision Tree Learning
| Partition | Mean Accuracy | Stdev     |
|-----------|---------------|-----------|
| 0.1       | 81.3239       | 2.36399   |
| 0.2       | 85.0072       | 1.77192   |
| 0.3       | 87.37         | 1.16669   |
| 0.4       | 88.7271       | 0.998851  |
| 0.5       | 89.6701       | 1.38012   |
| 0.6       | 91.0405       | 1.2279    |
| 0.7       | 92.5337       | 0.750889  |
| 0.8       | 92.5289       | 1.01886   |
| 0.9       | 94.2486       | 1.86836   |

---

## References
- **AIMA**: Artificial Intelligence: A Modern Approach by Stuart Russell and Peter Norvig.
- Mancala Rules: [The Spruce Crafts](https://www.thesprucecrafts.com/how-to-play-mancala-409424)
- Max-Cut Problem: Research articles and online resources.

---

Feel free to report issues or suggest improvements!

