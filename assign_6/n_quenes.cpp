#include <iostream>
#include <vector>
#include <chrono>
#include <windows.h>
#include <thread>
using namespace std;

// Print the board with queens
void printSolution(vector<vector<int>>& board, int N, int solutionCount) {
    cout << "\nSolution " << solutionCount << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] == 1 ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

// Check if placing queen is safe
bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
    for (int i = 0; i < row; i++)
        if (board[i][col] == 1) return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1) return false;

    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j] == 1) return false;

    return true;
}

// Recursive utility to solve N-Queens
void solveNQueensUtil(vector<vector<int>>& board, int row, int N, int &solutionCount, bool stepByStep) {
    if (row >= N) {
        solutionCount++;
        printSolution(board, N, solutionCount);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1;

            if (stepByStep) {
                cout << "Placing queen at (" << row << ", " << col << ")\n";
                printSolution(board, N, solutionCount + 1);
                Sleep(500); // pause for visualization
                }

            solveNQueensUtil(board, row + 1, N, solutionCount, stepByStep);

            board[row][col] = 0; // backtrack
        }
    }
}

// Solve N-Queens with timing + visualization
void solveNQueens(int N, bool stepByStep = false) {
    vector<vector<int>> board(N, vector<int>(N, 0));
    int solutionCount = 0;

    auto start = chrono::high_resolution_clock::now();
    solveNQueensUtil(board, 0, N, solutionCount, stepByStep);
    auto end = chrono::high_resolution_clock::now();

    if (solutionCount == 0)
        cout << "No solutions exist for N = " << N << endl;
    else
        cout << "\n✅ Total solutions for N = " << N << ": " << solutionCount << endl;

    chrono::duration<double> elapsed = end - start;
    cout << "⏱ Execution time: " << elapsed.count() << " seconds\n";
}

int main() {
    int N;
    char choice;

    cout << "Enter the size of the chessboard (N): ";
    cin >> N;

    cout << "Do you want step-by-step visualization? (y/n): ";
    cin >> choice;

    bool stepByStep = (choice == 'y' || choice == 'Y');
    solveNQueens(N, stepByStep);

    return 0;
}
