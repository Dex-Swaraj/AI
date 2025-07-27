#include <iostream>
#include <algorithm>
#include <queue> 
#include <set> 
#include <vector>

// Define the dimensions of the puzzle 
#define N 3 
using namespace std; 
// Structure to represent the state of the puzzle 
struct PuzzleState { 
    vector<vector<int>> board;  
    int x, y;   
    int depth;  
    PuzzleState* parent; // Pointer to parent state

    // Constructor 
    PuzzleState(vector<vector<int>> b, int i, int j, int d, PuzzleState* p = nullptr)
        : board(b), x(i), y(j), depth(d), parent(p) {}
};
// Possible moves: Left, Right, Up, Down 
int row[] = {0, 0, -1, 1}; 
int col[] = {-1, 1, 0, 0}; 
// Function to check if the current state is the goal state 
bool isGoalState(vector<vector<int>>& board) { 
vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}; 
return board == goal; 
} 
 
// Function to check if a move is valid 
bool isValid(int x, int y) { 
    return (x >= 0 && x < N && y >= 0 && y < N); 
} 
 
// Function to print the puzzle board 
void printBoard(vector<vector<int>>& board) { 
    for (auto& row : board) { 
        for (auto& num : row) 
            std::cout << num << " "; 
        std::cout << endl; 
    } 
    std::cout << "--------" << endl; 
} 
void printSolutionPath(PuzzleState* state) {
    vector<PuzzleState*> path;
    while (state != nullptr) {
        path.push_back(state);
        state = state->parent;
    }
    reverse(path.begin(), path.end());
    for (auto s : path) {
        cout << "Depth: " << s->depth << endl;
        printBoard(s->board);
    }
}

void solvePuzzleBFS(vector<vector<int>>& start, int x, int y) { 
    queue<PuzzleState*> q; 
    set<vector<vector<int>>> visited; 
    const int MAX_DEPTH = 50; // Set a reasonable depth limit
 
    // Enqueue initial state 
    PuzzleState* initial = new PuzzleState(start, x, y, 0, nullptr);
    q.push(initial); 
    visited.insert(start); 
 
    while (!q.empty()) { 
        PuzzleState* curr = q.front(); 
        q.pop(); 
 
        // Only print the current board state if you want to debug
        // cout << "Depth: " << curr->depth << endl; 
        // printBoard(curr->board); 
 
        // Check if goal state is reached 
        if (isGoalState(curr->board)) { 
            std::cout << "Goal state reached at depth " << curr->depth << endl; 
            printSolutionPath(curr);
            // Free memory
            delete curr;
            return; 
        } 

        // Check depth limit
        if (curr->depth >= MAX_DEPTH) {
            delete curr;
            continue;
        }
 
        // Explore all possible moves 
        for (int i = 0; i < 4; i++) { 
            int newX = curr->x + row[i]; 
            int newY = curr->y + col[i]; 
 
            if (isValid(newX, newY)) { 
                vector<vector<int>> newBoard = curr->board; 
                swap(newBoard[curr->x][curr->y], newBoard[newX][newY]); 
 
                // If this state has not been visited before, push to queue 
                if (visited.find(newBoard) == visited.end()) { 
                    visited.insert(newBoard); 
                    PuzzleState* next = new PuzzleState(newBoard, newX, newY, curr->depth + 1, curr);
                    q.push(next); 
                } 
            } 
        }
        // Don't forget to free memory for states not used anymore
        // But only after all children are processed, so here we don't delete curr
    } 
 
    std::cout << "No solution found (BFS Brute Force reached depth limit)" << endl; 
}

// Driver Code 
int main() { 
    vector<vector<int>> start = {{1, 2, 3}, {4, 0, 5}, {6, 7, 8}}; // Initial state 
    int x = 1, y = 1;  
 
    cout << "Initial State: " << endl; 
    printBoard(start); 
 
    solvePuzzleBFS(start, x, y); 
 
    return 0; 
}