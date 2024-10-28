#include <iostream>
#include <limits>

using namespace std;

char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char player = 'X', ai = 'O';

void displayBoard() {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];
    
    bool tie = true;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') tie = false;
    
    return tie ? 'T' : ' ';
}

int minimax(bool isMaximizing) {
    char winner = checkWinner();
    if (winner == ai) return 10;
    if (winner == player) return -10;
    if (winner == 'T') return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = ai;
                    bestScore = max(bestScore, minimax(false));
                    board[i][j] = backup;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = player;
                    bestScore = min(bestScore, minimax(true));
                    board[i][j] = backup;
                }
            }
        }
        return bestScore;
    }
}

void aiMove() {
    int bestScore = numeric_limits<int>::min();
    int moveRow, moveCol;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char backup = board[i][j];
                board[i][j] = ai;
                int score = minimax(false);
                board[i][j] = backup;
                if (score > bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }
    board[moveRow][moveCol] = ai;
}

void playerMove() {
    int choice;
    cout << "Enter the number of the cell where you want to place your mark (1-9): ";
    cin >> choice;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (choice >= 1 && choice <= 9 && board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = player;
    } else {
        cout << "Invalid move! Try again.\n";
        playerMove();
    }
}

void playGame() {
    while (true) {
        displayBoard();
        playerMove();

        if (checkWinner() != ' ') break;

        aiMove();

        if (checkWinner() != ' ') break;
    }

    displayBoard();
    char result = checkWinner();
    if (result == 'T') cout << "It's a tie!\n";
    else cout << "Winner: " << result << "!\n";
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    playGame();
    return 0;
}
