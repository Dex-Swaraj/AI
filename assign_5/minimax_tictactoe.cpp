#include <bits/stdc++.h>
using namespace std;

/*
 Minimax implementation for Tic-Tac-Toe (3x3)
 Two players: 'X' (maximizer) and 'O' (minimizer)
 This example includes alpha-beta pruning and simple board evaluation.
*/

const char PLAYER = 'X'; // Maximizer
const char OPPONENT = 'O'; // Minimizer
const char EMPTY = '_';

// Print board
void printBoard(const vector<vector<char>>& board) {
    for (auto &row : board) {
        for (char c : row) cout << c << ' ';
        cout << '\n';
    }
    cout << '\n';
}

// Check for win state
int evaluate(const vector<vector<char>>& b) {
    // Rows
    for (int row = 0; row < 3; ++row) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == PLAYER) return +10;
            else if (b[row][0] == OPPONENT) return -10;
        }
    }
    // Columns
    for (int col = 0; col < 3; ++col) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == PLAYER) return +10;
            else if (b[0][col] == OPPONENT) return -10;
        }
    }
    // Diagonals
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == PLAYER) return +10;
        else if (b[0][0] == OPPONENT) return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == PLAYER) return +10;
        else if (b[0][2] == OPPONENT) return -10;
    }
    // No winner
    return 0;
}

// Check if moves left
bool isMovesLeft(const vector<vector<char>>& board) {
    for (auto &row : board)
        for (char c : row)
            if (c == EMPTY) return true;
    return false;
}

// Minimax with alpha-beta pruning
int minimax(vector<vector<char>>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);

    // If Maximizer has won the game return evaluated score
    if (score == 10) return score - depth; // subtract depth to prefer faster wins
    // If Minimizer has won the game return evaluated score
    if (score == -10) return score + depth; // add depth to prefer slower losses
    // If no moves left and no winner then it is a tie
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = INT_MIN;
        // Traverse all cells
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    int val = minimax(board, depth + 1, false, alpha, beta);
                    board[i][j] = EMPTY;
                    best = max(best, val);
                    alpha = max(alpha, best);
                    if (beta <= alpha) return best; // Beta cut-off
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        // Traverse all cells
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = OPPONENT;
                    int val = minimax(board, depth + 1, true, alpha, beta);
                    board[i][j] = EMPTY;
                    best = min(best, val);
                    beta = min(beta, best);
                    if (beta <= alpha) return best; // Alpha cut-off
                }
            }
        }
        return best;
    }
}

// Find the best move for the current player (PLAYER - 'X')
pair<int,int> findBestMove(vector<vector<char>>& board) {
    int bestVal = INT_MIN;
    pair<int,int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER;
                int moveVal = minimax(board, 0, false, INT_MIN, INT_MAX);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Simple interactive game loop where human plays as 'O' and AI is 'X'
int main() {
    vector<vector<char>> board = {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

    cout << "Tic-Tac-Toe Minimax (AI = X, Human = O)\n";
    printBoard(board);

    // AI makes the first move (optional; you can change)
    while (true) {
        // AI move
        pair<int,int> best = findBestMove(board);
        if (best.first == -1) {
            cout << "No moves left. It's a draw!\n";
            break;
        }
        board[best.first][best.second] = PLAYER;
        cout << "AI moves to: (" << best.first << ", " << best.second << ")\n";
        printBoard(board);
        if (evaluate(board) == 10) { cout << "AI (X) wins!\n"; break; }
        if (!isMovesLeft(board)) { cout << "Draw!\n"; break; }

        // Human move
        int r, c;
        cout << "Enter your move (row and column: 0-based index): ";
        if (!(cin >> r >> c)) {
            cout << "Invalid input. Exiting.\n"; break;
        }
        if (r < 0 || r > 2 || c < 0 || c > 2 || board[r][c] != EMPTY) {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        board[r][c] = OPPONENT;
        printBoard(board);
        if (evaluate(board) == -10) { cout << "Human (O) wins!\n"; break; }
        if (!isMovesLeft(board)) { cout << "Draw!\n"; break; }
    }

    return 0;
}
