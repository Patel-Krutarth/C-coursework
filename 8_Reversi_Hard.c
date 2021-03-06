/*
    This program implements an alorithm to generate a 1-player reversi game.
    This algorithm choses the move which will minimize the opponents score and also choses the most beneficial locations first. 
*/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void initialBoard(char board[][26], int n)
{
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            board[i][j] = 'U';

            if(i == (n / 2) - 1 && j == (n / 2) - 1)
                board[i][j] = 'W';

            if(i == (n / 2) - 1 && j == (n / 2))
                board[i][j] = 'B';

            if(i == (n / 2) && j == (n / 2) - 1)
                board[i][j] = 'B';

            if(i == (n / 2) && j == (n / 2))
                board[i][j] = 'W';
        }
    }
}

void printBoard(char board[][26], int n)
{
    for(int i = -1; i < n; i++) {
        for(int j = -1; j < n; j++) {

            if(i == -1 && j == -1)
                printf("  "); // top left space
            else if(i == -1)  // coloumns letterings
                printf("%c", 'a' + j);
            else if(j == -1) // row letterings
                printf("%c ", 'a' + i);

            if(i >= 0 && j >= 0)
                printf("%c", board[i][j]);
        }
        printf("\n");
    }
}
bool positionInBounds(int n, int row, int col)
{
    return ((row >= 0 && row < n) && (col >= 0 && col < n));
}
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    int i = row + deltaRow, j = col + deltaCol;
    while(positionInBounds(n, i, j) && (board[i][j] != 'U' && board[i][j] != colour)) {

        if(board[i + deltaRow][j + deltaCol] == colour && positionInBounds(n, i + deltaRow, j + deltaCol))
            return true;

        i = i + deltaRow;
        j = j + deltaCol;
    }

    return false;
}

bool checkValid(char board[][26], int n, int b, int c, char a)
{
    if(positionInBounds(n, b, c) && (board[b][c] == 'U')) {
        return (checkLegalInDirection(board, n, b, c, a, 0, -1) || checkLegalInDirection(board, n, b, c, a, 1, -1) ||
            checkLegalInDirection(board, n, b, c, a, 1, 0) || checkLegalInDirection(board, n, b, c, a, 1, 1) ||
            checkLegalInDirection(board, n, b, c, a, 0, 1) || checkLegalInDirection(board, n, b, c, a, -1, 1) ||
            checkLegalInDirection(board, n, b, c, a, -1, 0) || checkLegalInDirection(board, n, b, c, a, -1, -1));
    } else
        return false;
}

bool availableMoves(char board[][26], int n, char colour)
{
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(checkValid(board, n, i, j, colour))
                return true;
        }
    }
    return false;
}

int countFlip(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    int score = 0;
    int i = row + deltaRow, j = col + deltaCol;
    while(positionInBounds(n, i, j) && board[i][j] != colour) {

        score++;

        i = i + deltaRow;
        j = j + deltaCol;
    }

    return score;
}
int countScore(char board[][26], int n, int i, int j, char colour)
{
    int score = 0;
    if(checkLegalInDirection(board, n, i, j, colour, 0, -1)) // west
        score += countFlip(board, n, i, j, colour, 0, -1);
    if(checkLegalInDirection(board, n, i, j, colour, 1, -1)) // southwest
        score += countFlip(board, n, i, j, colour, 1, -1);
    if(checkLegalInDirection(board, n, i, j, colour, 1, 0)) // south
        score += countFlip(board, n, i, j, colour, 1, 0);
    if(checkLegalInDirection(board, n, i, j, colour, 1, 1)) // southeast
        score += countFlip(board, n, i, j, colour, 1, 1);
    if(checkLegalInDirection(board, n, i, j, colour, 0, 1)) // east
        score += countFlip(board, n, i, j, colour, 0, 1);
    if(checkLegalInDirection(board, n, i, j, colour, -1, 1)) // northeast
        score += countFlip(board, n, i, j, colour, -1, 1);
    if(checkLegalInDirection(board, n, i, j, colour, -1, 0)) // north
        score += countFlip(board, n, i, j, colour, -1, 0);
    if(checkLegalInDirection(board, n, i, j, colour, -1, -1)) // northwest
        score += countFlip(board, n, i, j, colour, -1, -1);

    return score;
}
void flipTiles(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    board[row][col] = colour;
    int i = row + deltaRow, j = col + deltaCol;
    while(positionInBounds(n, i, j) && board[i][j] != colour) {

        board[i][j] = colour;

        i = i + deltaRow;
        j = j + deltaCol;
    }
}

void flipboard(char board[][26], int n, int i, int j, char colour)
{
    if(checkLegalInDirection(board, n, i, j, colour, 0, -1)) // west
        flipTiles(board, n, i, j, colour, 0, -1);
    if(checkLegalInDirection(board, n, i, j, colour, 1, -1)) // southwest
        flipTiles(board, n, i, j, colour, 1, -1);
    if(checkLegalInDirection(board, n, i, j, colour, 1, 0)) // south
        flipTiles(board, n, i, j, colour, 1, 0);
    if(checkLegalInDirection(board, n, i, j, colour, 1, 1)) // southeast
        flipTiles(board, n, i, j, colour, 1, 1);
    if(checkLegalInDirection(board, n, i, j, colour, 0, 1)) // east
        flipTiles(board, n, i, j, colour, 0, 1);
    if(checkLegalInDirection(board, n, i, j, colour, -1, 1)) // northeast
        flipTiles(board, n, i, j, colour, -1, 1);
    if(checkLegalInDirection(board, n, i, j, colour, -1, 0)) // north
        flipTiles(board, n, i, j, colour, -1, 0);
    if(checkLegalInDirection(board, n, i, j, colour, -1, -1)) // northwest
        flipTiles(board, n, i, j, colour, -1, -1);
}
void copyBoard(char board[][26], char boardCopy[][26], int n)
{
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            boardCopy[i][j] = board[i][j];
        }
    }
}

int maxScore(char board[][26], int n, char colour, int* maxRow, int* maxCol)
{
    int score = 0, max = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(checkValid(board, n, i, j, colour)) {
                score = countScore(board, n, i, j, colour);
                if(max < score) {
                    max = score;
                    *maxRow = i;
                    *maxCol = j;
                }
            }
        }
    }
    return max;
}

void notCorners(char board[][26],
    char boardCopy[][26],
    int n,
    char computer,
    char human,
    int* maxRow,
    int* maxCol,
    int* min)
{
    int count = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(checkValid(board, n, i, j, computer))
                count++;
        }
    }
    if(count == 1) {
        return;
    }

    else {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(checkValid(board, n, i, j, computer)) {
                    copyBoard(board, boardCopy, n);
                    flipboard(boardCopy, n, i, j, computer);
                    if((maxScore(boardCopy, n, human, maxRow, maxCol) < *min) &&
                        !(checkValid(boardCopy, n, 0, 0, human) || checkValid(boardCopy, n, 0, n - 1, human) ||
                            checkValid(boardCopy, n, n - 1, 0, human) ||
                            checkValid(boardCopy, n, n - 1, n - 1, human))) {
                        *min = maxScore(boardCopy, n, human, maxRow, maxCol);
                        *maxRow = i;
                        *maxCol = j;
                    }
                }
            }
        }
    }
}
void bestMove(char board[][26], int n, char computer, char human, int* maxRow, int* maxCol)
{
    int min = 677, row, col;
    char boardCopy[26][26] = { 0 };

    for(int i = 0; i <= n - 1; i++) {
        for(int j = 0; j <= n - 1; j++) {
            if((i == 0 || i == n - 1) && (j == 0 || j == n - 1)) {
                if(checkValid(board, n, i, j, computer)) {
                    copyBoard(board, boardCopy, n);
                    flipboard(boardCopy, n, i, j, computer);
                    if(maxScore(boardCopy, n, human, &row, &col) < min) {
                        min = maxScore(boardCopy, n, human, &row, &col);
                        *maxRow = i;
                        *maxCol = j;
                    }
                }
            }
        }
    }

    if(min == 677 && n > 4) {
        for(int j = 2; j <= n - 3; j++) {
            if((j == 2 || j == n - 3)) {
                if(checkValid(board, n, 0, j, computer)) {
                    copyBoard(board, boardCopy, n);
                    flipboard(boardCopy, n, 0, j, computer);
                    if(maxScore(boardCopy, n, human, &row, &col) < min) {
                        min = maxScore(boardCopy, n, human, &row, &col);
                        *maxRow = 0;
                        *maxCol = j;
                    }
                }
            }
        }
        for(int j = 0; j <= n - 1; j++) {
            if((j == 0 || j == n - 1)) {
                if(checkValid(board, n, 2, j, computer)) {
                    copyBoard(board, boardCopy, n);
                    flipboard(boardCopy, n, 2, j, computer);
                    if(maxScore(boardCopy, n, human, &row, &col) < min) {
                        min = maxScore(boardCopy, n, human, &row, &col);
                        *maxRow = 2;
                        *maxCol = j;
                    }
                }
            }
        }
        for(int j = 0; j <= n - 1; j++) {
            if((j == 0 || j == n - 1)) {
                if(checkValid(board, n, n - 3, j, computer)) {
                    copyBoard(board, boardCopy, n);
                    flipboard(boardCopy, n, n - 3, j, computer);
                    if(maxScore(boardCopy, n, human, &row, &col) < min) {
                        min = maxScore(boardCopy, n, human, &row, &col);
                        *maxRow = n - 3;
                        *maxCol = j;
                    }
                }
            }
        }
        for(int j = 2; j <= n - 3; j++) {
            if((j == 0 || j == n - 3)) {
                if(checkValid(board, n, n - 1, j, computer)) {
                    copyBoard(board, boardCopy, n);
                    flipboard(boardCopy, n, n - 1, j, computer);
                    if(maxScore(boardCopy, n, human, &row, &col) < min) {
                        min = maxScore(boardCopy, n, human, &row, &col);
                        *maxRow = n - 1;
                        *maxCol = j;
                    }
                }
            }
        }
        for(int j = 2; j <= n - 3; j++) { // inner top (3)
            if((j == 2 || j == n - 3)) {
                if(checkValid(board, n, 2, j, computer)) {
                    copyBoard(board, boardCopy, n);
                    flipboard(boardCopy, n, 2, j, computer);
                    if(maxScore(boardCopy, n, human, &row, &col) < min) {
                        min = maxScore(boardCopy, n, human, &row, &col);
                        *maxRow = 2;
                        *maxCol = j;
                    }
                }
            }
        }
        for(int j = 2; j <= n - 3; j++) { // inner bottom (3)
            if((j == 2 || j == n - 3)) {
                if(checkValid(board, n, n - 3, j, computer)) {
                    copyBoard(board, boardCopy, n);
                    flipboard(boardCopy, n, n - 3, j, computer);
                    if(maxScore(boardCopy, n, human, &row, &col) < min) {
                        min = maxScore(boardCopy, n, human, &row, &col);
                        *maxRow = n - 3;
                        *maxCol = j;
                    }
                }
            }
        }
    }

    if(min == 677 && n > 6) {
        for(int j = 3; j < n - 4; j++) {
            if(checkValid(board, n, 0, j, computer)) {
                copyBoard(board, boardCopy, n);
                flipboard(boardCopy, n, 0, j, computer);
                if(maxScore(boardCopy, n, human, &row, &col) < min) {
                    min = maxScore(boardCopy, n, human, &row, &col);
                    *maxRow = 0;
                    *maxCol = j;
                }
            }
        }
        for(int i = 3; i < n - 4; i++) {
            if(checkValid(board, n, i, 0, computer)) {
                copyBoard(board, boardCopy, n);
                flipboard(boardCopy, n, i, 0, computer);
                if(maxScore(boardCopy, n, human, &row, &col) < min) {
                    min = maxScore(boardCopy, n, human, &row, &col);
                    *maxRow = i;
                    *maxCol = 0;
                }
            }
        }
        for(int i = 3; i < n - 4; i++) {
            if(checkValid(board, n, i, n - 1, computer)) {
                copyBoard(board, boardCopy, n);
                flipboard(boardCopy, n, i, n - 1, computer);
                if(maxScore(boardCopy, n, human, &row, &col) < min) {
                    min = maxScore(boardCopy, n, human, &row, &col);
                    *maxRow = i;
                    *maxCol = n - 1;
                }
            }
        }
        for(int j = 3; j < n - 4; j++) {
            if(checkValid(board, n, n - 1, j, computer)) {
                copyBoard(board, boardCopy, n);
                flipboard(boardCopy, n, n - 1, j, computer);
                if(maxScore(boardCopy, n, human, &row, &col) < min) {
                    min = maxScore(boardCopy, n, human, &row, &col);
                    *maxRow = n - 1;
                    *maxCol = j;
                }
            }
        }
    }

    if(min == 677) { // not corners
        int count = 0;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(checkValid(board, n, i, j, computer))
                    count++;
            }
        }
        if(count != 1) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(checkValid(board, n, i, j, computer)) {
                        copyBoard(board, boardCopy, n);
                        flipboard(boardCopy, n, i, j, computer);
                        if((maxScore(boardCopy, n, human, &row, &col) < min) &&
                            !(checkValid(boardCopy, n, 0, 0, human) || checkValid(boardCopy, n, 0, n - 1, human) ||
                                checkValid(boardCopy, n, n - 1, 0, human) ||
                                checkValid(boardCopy, n, n - 1, n - 1, human))) {
                            min = maxScore(boardCopy, n, human, &row, &col);
                            *maxRow = i;
                            *maxCol = j;
                        }
                    }
                }
            }
        }
    }

    if(min == 677) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(checkValid(board, n, i, j, computer)) {
                    copyBoard(board, boardCopy, n);
                    flipboard(boardCopy, n, i, j, computer);
                    if(maxScore(boardCopy, n, human, &row, &col) < min) {
                        min = maxScore(boardCopy, n, human, &row, &col);
                        *maxRow = i;
                        *maxCol = j;
                    }
                }
            }
        }
    }
}
bool boardFull(char board[][26], int n)
{
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == 'U')
                return false;
        }
    }
    return true;
}
bool gameover(char board[][26], int n)
{
    bool boardfull = true;
    bool availableMove = false;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == 'U')
                boardfull = false;

            if((checkValid(board, n, i, j, 'W') || checkValid(board, n, i, j, 'B')))
                return (!(checkValid(board, n, i, j, 'W') || checkValid(board, n, i, j, 'B')));
        }
    }
    return (boardfull || !availableMove);
}
int winner(char board[][26], int n)
{
    int countW = 0, countB = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == 'W')
                countW++;
            if(board[i][j] == 'B')
                countB++;
        }
    }
    if(countW == countB)
        return 1;

    return ((countW > countB) ? 87 : 66);
}
int main(int argc, char** argv)
{
    int n, maxRow = -1, maxCol = -1;
    char human, computer, currentPlayer, rowMove, colMove;
    char board[26][26] = { 0 };

    printf("Enter the board dimension: ");
    scanf("%d", &n);

    printf("Computer plays (B/W): ");
    scanf(" %c", &computer);

    human = (computer == 'W' ? 'B' : 'W');

    currentPlayer = (human == 'B' ? human : computer);

    initialBoard(board, n);
    printBoard(board, n);

    while(gameover(board, n) == false) {

        if(!(availableMoves(board, n, currentPlayer))) {
            printf("%c player has no valid move.\n", currentPlayer);
            currentPlayer = (currentPlayer == human ? computer : human);
        }
        if(currentPlayer == computer) {
            bestMove(board, n, computer, human, &maxRow, &maxCol);
            printf("Computer places %c at %c%c.\n", computer, maxRow + 97, maxCol + 97);

            flipboard(board, n, maxRow, maxCol, computer);
        } else {
            printf("Enter move for colour %c (RowCol): ", human);
            scanf(" %c%c", &rowMove, &colMove);

            if(!(checkValid(board, n, rowMove - 97, colMove - 97, human))) {
                printf("Invalid move.\n");
                if(winner(board, n) == 87)
                    printf("W player wins.");
                else if(winner(board, n) == 66)
                    printf("B player wins.");
                else if(winner(board, n) == 1)
                    printf("Draw!");
                return 0;
            }

            flipboard(board, n, rowMove - 97, colMove - 97, human);
        }
        printBoard(board, n);

        currentPlayer = (currentPlayer == human ? computer : human);
    }
    if(!boardFull(board, n)) {
        if(!(availableMoves(board, n, currentPlayer))) {
            printf("%c player has no valid move.\n", currentPlayer);
            currentPlayer = (currentPlayer == human ? computer : human);
        }
        if(!(availableMoves(board, n, currentPlayer))) {
            printf("%c player has no valid move.\n", currentPlayer);
            currentPlayer = (currentPlayer == human ? computer : human);
        }
    }

    if(winner(board, n) == 87)
        printf("W player wins.");
    else if(winner(board, n) == 66)
        printf("B player wins.");
    else if(winner(board, n) == 1)
        printf("Draw!");

    return 0;
}
