#include <stdio.h>
#include <string.h>

// bool type
#define TRUE        1
#define FALSE       0
typedef int bool;

// board size
#define SIZE      8

// grid definition
#define GRID_EMPTY  0
#define GRID_X      1
#define GRID_O      2
#define GRID_THINK  6

// winning number
#define WIN_LENGTH  4

// input string size
#define INPUT_LEN   20

bool debug = FALSE;

int board_[SIZE][SIZE];
char input_[INPUT_LEN];

bool firstMove_ = FALSE;

/**
* Help Function Declarations
*/
int getInput(char *input);
void makeMove(int x, int y, int grid, int board[SIZE][SIZE]);
bool isLegal(int x, int y, int board[SIZE][SIZE]);
void printBoard(int board[SIZE][SIZE]);

/**
 * Core Function Declarations
 */
void markGridThink(int board[SIZE][SIZE]);
int findNextMove(int board[SIZE][SIZE], int *moveI, int *moveJ, int depth);
int scoreBoard(int board[SIZE][SIZE]);

/**
* Main Function
*/
int main() {

    printBoard(board_);

    int moveI;
    int moveJ;
    int count = 0;
    bool run = TRUE;

    while (run) {

        debug = FALSE;
        int move = getInput(input_);
        moveI = move / 10;
        moveJ = move % 10;
//        moveI = 3;
//        moveJ = 3;

        makeMove(moveI, moveJ, GRID_O, board_);



        markGridThink(board_);

        printf("final score = %d\n", findNextMove(board_, &moveI, &moveJ, 1));

        makeMove(moveI, moveJ, GRID_X, board_);

        printBoard(board_);
        debug = TRUE;
        printf("score of the board = %d\n", scoreBoard(board_));

        printf("Done %d round\n", ++count);
    }

    if (run == FALSE) {
//        makeMove(0, 1, GRID_O, board_);
//        makeMove(0, 3, GRID_O, board_);
//        makeMove(0, 4, GRID_O, board_);
//        makeMove(0, 6, GRID_X, board_);
//        makeMove(0, 7, GRID_X, board_);
//
//        makeMove(1, 0, GRID_O, board_);
//        makeMove(3, 0, GRID_O, board_);
//        makeMove(4, 0, GRID_O, board_);
//        makeMove(6, 0, GRID_X, board_);
//        makeMove(7, 0, GRID_X, board_);

//        makeMove(2, 3, GRID_O, board_);
//        makeMove(3, 3, GRID_O, board_);
//        makeMove(4, 3, GRID_X, board_);
//        makeMove(3, 4, GRID_X, board_);
//        makeMove(1, 2, GRID_THINK, board_);
//        makeMove(2, 2, GRID_THINK, board_);
//        makeMove(3, 2, GRID_THINK, board_);
//        makeMove(4, 2, GRID_THINK, board_);
//        makeMove(1, 3, GRID_THINK, board_);
//        makeMove(1, 4, GRID_THINK, board_);
//        makeMove(2, 4, GRID_THINK, board_);
//        makeMove(2, 5, GRID_THINK, board_);
//        makeMove(3, 5, GRID_THINK, board_);
//        makeMove(4, 5, GRID_THINK, board_);
//        makeMove(4, 4, GRID_THINK, board_);

        makeMove(3, 4, GRID_O, board_);
        makeMove(4, 3, GRID_X, board_);
        makeMove(2, 3, GRID_THINK, board_);
        makeMove(3, 3, GRID_THINK, board_);
        makeMove(2, 4, GRID_THINK, board_);
        makeMove(2, 5, GRID_THINK, board_);
        makeMove(3, 5, GRID_THINK, board_);
        makeMove(4, 5, GRID_THINK, board_);
        makeMove(4, 4, GRID_THINK, board_);


        printBoard(board_);
        printf("score of the board = %d\n", scoreBoard(board_));
    }

    return 0;
}

/**
* Help Function Definitions
*/
int getInput(char *input) {
    // loop until gets valid input
    while (1) {
        printf("Please make your move: ");
        scanf("%20s", input);

        if (input[1] > '0' && input[1] < '9') {
            if (input[0] >= 'a' && input[0] <= 'h') {
                return (input[0] - 'a') * 10 + input[1] - '1';
            } else if (input[0] >= 'A' && input[0] <= 'H') {
                return (input[0] - 'A') * 10 + input[1] - '1';
            }
        }

        printf("Input invalid!\n");

    }
}

void makeMove(int i, int j, int grid, int board[SIZE][SIZE]) {
    if (isLegal(i, j, board))
        board[i][j] = grid;
    else
        printf("*[WAR]* makeXMove: illegal [%d,%d]=%d\n", i, j, board[i][j]);
}

bool isPlayer(int i, int j, int board[SIZE][SIZE]) {
    // NOT out of board
    // NOT possessed
    return ((i >= 0 && i < SIZE && j >= 0 && j < SIZE)
            && (board[i][j] == GRID_O || board[i][j] == GRID_X));
}

bool isThink(int i, int j, int board[SIZE][SIZE]) {
    // NOT out of board
    // NOT possessed
    return ((i >= 0 && i < SIZE && j >= 0 && j < SIZE)
            && (board[i][j] == GRID_THINK));
}
bool isEmpty(int i, int j, int board[SIZE][SIZE]) {
    // NOT out of board
    // NOT possessed
    return ((i >= 0 && i < SIZE && j >= 0 && j < SIZE)
            && (board[i][j] == GRID_EMPTY));
}

bool isLegal(int i, int j, int board[SIZE][SIZE]) {
    // NOT out of board
    // NOT possessed
    return ((i >= 0 && i < SIZE && j >= 0 && j < SIZE)
            && (board[i][j] == GRID_EMPTY || board[i][j] == GRID_THINK));
}

void printBoard(int board[SIZE][SIZE]) {
    // caption row
    printf("  1 2 3 4 5 6 7 8\n");
    char cap = 'A';
    for (int i = 0; i < SIZE; ++i) {
        printf("%c ", cap++);
        for (int j = 0; j < SIZE; ++j) {
            switch (board[i][j]) {
                case GRID_EMPTY:
                    printf(" ");
                    break;
                case GRID_X:
                    printf("X");
                    break;
                case GRID_O:
                    printf("O");
                    break;
                case GRID_THINK:
                    printf("-");
                    break;
                default:
                    break;
            }
            printf(" ");
        }
        printf("\n");
    }
}


/**
 * Core Function Definitions
 */
// TODO: using a very naive way to calculate
// TODO: and currently only consider 1 layer
void markAround(int i, int j, int board[SIZE][SIZE]) {
    for (int x = i - 1; x <= i + 1; ++x)
        for (int y = j - 1; y <= j + 1; ++ y) {
            if (isEmpty(x, y, board))
                board[x][y] = GRID_THINK;
        }
}

void markGridThink(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (isPlayer(i, j, board)) {
                markAround(i, j, board);
            }
        }
    }
}

int findNextMove(int board[SIZE][SIZE], int *moveI, int *moveJ, int depth) {
    int finalScore = -50000;

    // all possible moves for X
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (isThink(i, j, board)) {
                // generate new board for X
                int boardX[SIZE][SIZE];
                memcpy((void *) boardX, (void const *)board, sizeof(int) * SIZE * SIZE);

                // make move
                makeMove(i, j, GRID_X, boardX);

                // generate next possible moves for O
                markAround(i, j, boardX);


                int scoreX = 50000;
                int bestOI = -1;
                int bestOJ = -1;

                // all possible moves for O
                for (int x = 0; x < SIZE; ++x) {
                    for (int y = 0; y < SIZE; ++y) {
                        if (isThink(x, y, boardX)) {
                            // generate new board for O
                            int boardO[SIZE][SIZE];
                            memcpy((void *) boardO, (void const *)boardX, sizeof(int) * SIZE * SIZE);

                            // make move
                            makeMove(x, y, GRID_O, boardO);

                            // generate next possible moves for X
                            markAround(x, y, boardO);

                            int scoreO = -50000;
                            int bestXI = -1;
                            int bestXJ = -1;

                            // all possible moves for X
                            for (int m = 0; m < SIZE; ++m) {
                                for (int n = 0; n < SIZE; ++n) {
                                    if (isThink(m, n, boardO)) {
                                        // generate new board for X
                                        int boardLeaf[SIZE][SIZE];
                                        memcpy((void *) boardLeaf, (void const *)boardO, sizeof(int) * SIZE * SIZE);

                                        // if this is the last layer
                                        // generate score and find the best one
                                        int score;
                                        if (depth == 1) {
                                            // make move
                                            makeMove(m, n, GRID_X, boardLeaf);

                                            // generate next possible moves for O
                                            markAround(m, n, boardLeaf);

                                            score = scoreBoard(boardLeaf);
                                        } else {
                                            int a, b;
                                            score = findNextMove(boardLeaf, &a, &b, depth - 1);
                                            printf("");
                                        }
                                        if (score > scoreO) {
                                            scoreO = score;
//                                            bestXI = m;
//                                            bestXJ = n;
                                        }
                                    }
                                }
                            }   // all possible moves for X

                            if (scoreO < scoreX) {
                                scoreX = scoreO;
//                                bestOI = bestXI;
//                                bestOJ = bestXJ;
                            }
                        }
                    }
                }   // all possible moves for O

                if (scoreX > finalScore) {
                    finalScore = scoreX;
                    *moveI = i;
                    *moveJ = j;
                }
//                printf("score=%d at %d,%d\n", scoreX, i, j);
            }
        }

    }   // end of the big loop

    return finalScore;
}

int contScore(int contValue, bool firstMove) {
    int score = contValue * contValue + firstMove;

    if (contValue < 3) {    // when continuous value is less than 3
        score = contValue * (firstMove ? contValue : 1);
    }

    return score;
}

void updateNakedBoard(int nakedBoard[SIZE][SIZE], int nakedCandidate[SIZE], int maxIdx) {
    if (maxIdx > 1)
        for (int idx = 0; idx < maxIdx; ++idx) {
            int i = nakedCandidate[idx] / 10;
            int j = nakedCandidate[idx] % 10;
            nakedBoard[i][j] += 1;
        }
}

int scoreBoard(int board[SIZE][SIZE]) {
    int totalScoreX = 0;
    int totalScoreO = 0;

    int nakedBoardX[SIZE][SIZE];
    int nakedBoardO[SIZE][SIZE];
    memset((void *)nakedBoardX, 0, sizeof(int) * SIZE * SIZE);
    memset((void *)nakedBoardO, 0, sizeof(int) * SIZE * SIZE);

    // row by row
    for (int i = 0; i < SIZE; ++i) {
        int spaceEmpty = 0;
        int spaceX = 0;
        int spaceO = 0;
        int continuousX = 0;
        int continuousO = 0;
        int previousGrid = GRID_EMPTY;
        int dominantGrid = GRID_EMPTY;
        int scoreX = 0;
        int scoreO = 0;
        bool isNaked = FALSE;
        int nakedCandidate[SIZE];
        int nakedCandidateIdx = 0;
        memset((void *) nakedCandidate, 0, sizeof(int) * SIZE);
        for (int j = 0; j < SIZE; ++j) {
            switch (board[i][j]) {
                case GRID_EMPTY:
                case GRID_THINK:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
                        case GRID_THINK:
                            //++spaceEmpty;
                            break;
                        case GRID_X:
                            ++spaceX;
                            break;
                        case GRID_O:
                            ++spaceO;
                            break;
                        default:
                            break;
                    }
                    ++spaceEmpty;
                    break;
                case GRID_X:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
                        case GRID_THINK:
                            spaceX += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_X:
                            if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK)
                                spaceEmpty = 0;
                            break;
                        case GRID_O:    // checkpoint
                            if (isNaked) {
                                if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK) { // naked confirmed
                                    updateNakedBoard(nakedBoardO, nakedCandidate, nakedCandidateIdx);
                                }
                                memset((void *)nakedCandidate, 0, sizeof(int) * SIZE);
                                nakedCandidateIdx = 0;
                                isNaked = FALSE;
                            }

                            if (spaceO >= WIN_LENGTH) 
                                scoreO += contScore(continuousO, 1 - firstMove_);
                            continuousO = 0;
                            spaceO = 0;
                            spaceX += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        default:
                            break;
                    }
                    ++spaceX;
                    ++continuousX;
                    dominantGrid = GRID_X;
                    if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK)
                        isNaked = TRUE;
                    if (isNaked) {
                        nakedCandidate[nakedCandidateIdx] = i * 10 + j;
                        ++nakedCandidateIdx;
                    }
                    break;
                case GRID_O:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
                        case GRID_THINK:
                            spaceO += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_X:    // checkpoint
                            if (isNaked) {
                                if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK) { // naked confirmed
                                    updateNakedBoard(nakedBoardX, nakedCandidate, nakedCandidateIdx);
                                }
                                memset((void *)nakedCandidate, 0, sizeof(int) * SIZE);
                                nakedCandidateIdx = 0;
                                isNaked = FALSE;
                            }

                            if (spaceX >= WIN_LENGTH)
                                scoreX += contScore(continuousX, firstMove_);
                            continuousX = 0;
                            spaceX = 0;
                            spaceO += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_O:
                            if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK)
                                spaceEmpty = 0;
                            break;
                        default:
                            break;
                    }
                    ++spaceO;
                    ++continuousO;
                    dominantGrid = GRID_O;
                    if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK)
                        isNaked = TRUE;
                    if (isNaked) {
                        nakedCandidate[nakedCandidateIdx] = i * 10 + j;
                        ++nakedCandidateIdx;
                    }
                default:
                    break;
            }   // end of switch (board[i][j]

            previousGrid = board[i][j];

        }   // end of for-j

        // checkpoint
        if (dominantGrid == GRID_O)
            if (isNaked) {
                if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK) { // naked confirmed
                    updateNakedBoard(nakedBoardO, nakedCandidate, nakedCandidateIdx);
                }
                isNaked = FALSE;
            }
        if (dominantGrid == GRID_X)
            if (isNaked) {
                if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK) { // naked confirmed
                    updateNakedBoard(nakedBoardX, nakedCandidate, nakedCandidateIdx);
                }
                isNaked = FALSE;
            }

        if (spaceX >= WIN_LENGTH)
            scoreX += contScore(continuousX, firstMove_);    // TODO: need to increase this weight
        if (spaceO >= WIN_LENGTH)
            scoreO += contScore(continuousO, 1 - firstMove_);

        totalScoreX += scoreX;
        totalScoreO += scoreO;

        if (debug)
            printf("row %d: scoreX=%d[%d], scoreO=%d[%d]\n", i, scoreX, spaceX, scoreO, spaceO);
    }   // end of for-i

    // column by column
    for (int j = 0; j < SIZE; ++j) {
        int spaceEmpty = 0;
        int spaceX = 0;
        int spaceO = 0;
        int continuousX = 0;
        int continuousO = 0;
        int previousGrid = GRID_EMPTY;
        int dominantGrid = GRID_EMPTY;
        int scoreX = 0;
        int scoreO = 0;
        bool isNaked = FALSE;
        int nakedCandidate[SIZE];
        int nakedCandidateIdx = 0;
        memset((void *) nakedCandidate, 0, sizeof(int) * SIZE);
        for (int i = 0; i < SIZE; ++i) {
            switch (board[i][j]) {
                case GRID_EMPTY:
                case GRID_THINK:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
                        case GRID_THINK:
                            //++spaceEmpty;
                            break;
                        case GRID_X:
                            ++spaceX;
                            break;
                        case GRID_O:
                            ++spaceO;
                            break;
                        default:
                            break;
                    }
                    ++spaceEmpty;
                    break;
                case GRID_X:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
                        case GRID_THINK:
                            spaceX += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_X:
                            if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK)
                                spaceEmpty = 0;
                            break;
                        case GRID_O:    // checkpoint
                            if (isNaked) {
                                if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK) { // naked confirmed
                                    updateNakedBoard(nakedBoardX, nakedCandidate, nakedCandidateIdx);
                                }
                                memset((void *)nakedCandidate, 0, sizeof(int) * SIZE);
                                nakedCandidateIdx = 0;
                                isNaked = FALSE;
                            }

                            if (spaceO >= WIN_LENGTH)
                                scoreO += contScore(continuousO, 1 - firstMove_);
                            continuousO = 0;
                            spaceO = 0;
                            spaceX += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        default:
                            break;
                    }
                    ++spaceX;
                    ++continuousX;
                    dominantGrid = GRID_X;
                    if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK)
                        isNaked = TRUE;
                    if (isNaked) {
                        nakedCandidate[nakedCandidateIdx] = i * 10 + j;
                        ++nakedCandidateIdx;
                    }
                    break;
                case GRID_O:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
                        case GRID_THINK:
                            spaceO += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_X:    // checkpoint
                            if (isNaked) {
                                if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK) { // naked confirmed
                                    updateNakedBoard(nakedBoardO, nakedCandidate, nakedCandidateIdx);
                                }
                                memset((void *)nakedCandidate, 0, sizeof(int) * SIZE);
                                nakedCandidateIdx = 0;
                                isNaked = FALSE;
                            }

                            if (spaceX >= WIN_LENGTH)
                                scoreX += contScore(continuousX, firstMove_);
                            continuousX = 0;
                            spaceX = 0;
                            spaceO += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_O:
                            if (previousGrid == GRID_O)
                                spaceEmpty = 0;
                            break;
                        default:
                            break;
                    }
                    ++spaceO;
                    ++continuousO;
                    dominantGrid = GRID_O;
                    if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK)
                        isNaked = TRUE;
                    if (isNaked) {
                        nakedCandidate[nakedCandidateIdx] = i * 10 + j;
                        ++nakedCandidateIdx;
                    }
                default:
                    break;
            }   // end of switch (board[i][j]

            previousGrid = board[i][j];

            if (isNaked) {
                nakedCandidate[nakedCandidateIdx] = i * 10 + j;
                ++nakedCandidateIdx;
            }
        }   // end of for-i

        // checkpoint
        if (dominantGrid == GRID_O)
            if (isNaked) {
                if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK) { // naked confirmed
                    updateNakedBoard(nakedBoardO, nakedCandidate, nakedCandidateIdx);
                }
                isNaked = FALSE;
            }
        if (dominantGrid == GRID_X)
            if (isNaked) {
                if (previousGrid == GRID_EMPTY || previousGrid == GRID_THINK) { // naked confirmed
                    updateNakedBoard(nakedBoardX, nakedCandidate, nakedCandidateIdx);
                }
                isNaked = FALSE;
            }

        if (spaceX >= WIN_LENGTH)
            scoreX += contScore(continuousX, firstMove_);    // TODO: need to increase this weight
        if (spaceO >= WIN_LENGTH)
            scoreO += contScore(continuousO, 1 - firstMove_);

        totalScoreX += scoreX;
        totalScoreO += scoreO;

        if (debug)
            printf("column %d: scoreX=%d[%d], scoreO=%d[%d]\n", j, scoreX, spaceX, scoreO, spaceO);
    }   // end of for-j


    // scan for cross shape naked
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            if (nakedBoardX[i][j] > 1) {
                totalScoreX += 5;

                if (debug)
                    printf("naked cross for X at %d,%d\n", i, j);
            }
            if (nakedBoardO[i][j] > 1) {
                totalScoreO += 5;

                if (debug)
                    printf("naked cross for O at %d,%d\n", i, j);
            }
        }

    return totalScoreX - totalScoreO;
}


