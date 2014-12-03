#include <stdio.h>

// bool type
#define TRUE        1
#define FALSE       0
typedef int bool;

// board size
#define LENGTH      8

// grid definition
#define GRID_EMPTY  0
#define GRID_X      1
#define GRID_O      2


// winning number
#define WIN_LENGTH  4

// input string size
#define INPUT_LEN   20

int board_[LENGTH][LENGTH];
char input_[INPUT_LEN];

/**
* Help Function Declarations
*/
int getInput(char *input);
void makeMove(int x, int y, int grid);
bool isLegal(int x, int y);
void printBoard();

/**
 * Core Function Declarations
 */
int scoreBoard();


/**
* Main Function
*/
int main() {

//    printBoard();
//
//    while (1) {
//
//        int move = getInput(input_);
//        int moveX = move / 10;
//        int moveY = move % 10;
//
//        makeXMove(moveX, moveY);

    makeMove(0, 1, GRID_O);
    makeMove(0, 3, GRID_O);
    makeMove(0, 4, GRID_O);
    makeMove(0, 6, GRID_X);
    makeMove(0, 7, GRID_X);


        printBoard();
        scoreBoard();
//    }

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

void makeMove(int x, int y, int grid) {
    if (isLegal(x, y))
        board_[x][y] = grid;
    else
        printf("*[WAR]* makeXMove: illegal\n");
}


bool isLegal(int x, int y) {
    // NOT out of board
    // NOT possessed
    return ((x >= 0 && x < LENGTH && y >= 0 && y < LENGTH)
            && (board_[x][y] == GRID_EMPTY));
}

void printBoard() {
    // caption row
    printf("  1 2 3 4 5 6 7 8\n");
    char cap = 'A';
    for (int i = 0; i < LENGTH; ++i) {
        printf("%c ", cap++);
        for (int j = 0; j < LENGTH; ++j) {
            switch (board_[i][j]) {
                case GRID_EMPTY:
                    printf("-");
                    break;
                case GRID_X:
                    printf("X");
                    break;
                case GRID_O:
                    printf("O");
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
int scoreBoard() {
    int totalScoreX = 0;
    int totalScoreO = 0;
    // row by row
    for (int i = 0; i < LENGTH; ++i) {
        int spaceEmpty = 0;
        int spaceX = 0;
        int spaceO = 0;
        int continuousX = 0;
        int continuousO = 0;
        int previousGrid = GRID_EMPTY;
        int dominantGrid = GRID_EMPTY;
        int scoreX = 0;
        int scoreO = 0;
        for (int j = 0; j < LENGTH; ++j) {
            switch (board_[i][j]) {
                case GRID_EMPTY:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
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
                            spaceX += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_X:
                            if (previousGrid == GRID_EMPTY)
                                spaceEmpty = 0;
                            break;
                        case GRID_O:    // checkpoint
                            if (spaceO >= WIN_LENGTH) 
                                scoreO += continuousO;
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
                    break;
                case GRID_O:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
                            spaceO += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_X:    // checkpoint
                            if (spaceX >= WIN_LENGTH)
                                scoreX += continuousX;
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
                default:
                    break;
            }   // end of switch (board_[i][j]

            previousGrid = board_[i][j];

        }   // end of for-j

        // checkpoint
        if (spaceX >= WIN_LENGTH)
            scoreX += continuousX;
        if (spaceO >= WIN_LENGTH)
            scoreO += continuousO;

        totalScoreX += scoreX;
        totalScoreO += scoreO;
        printf("row %d: scoreX=%d, scoreO=%d\n", i, scoreX, scoreO);
    }   // end of for-i

    // column by column
    for (int j = 0; j < LENGTH; ++j) {
        int spaceEmpty = 0;
        int spaceX = 0;
        int spaceO = 0;
        int continuousX = 0;
        int continuousO = 0;
        int previousGrid = GRID_EMPTY;
        int dominantGrid = GRID_EMPTY;
        int scoreX = 0;
        int scoreO = 0;
        for (int i = 0; i < LENGTH; ++i) {
            switch (board_[i][j]) {
                case GRID_EMPTY:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
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
                            spaceX += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_X:
                            if (previousGrid == GRID_EMPTY)
                                spaceEmpty = 0;
                            break;
                        case GRID_O:    // checkpoint
                            if (spaceO >= WIN_LENGTH)
                                scoreO += continuousO;
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
                    break;
                case GRID_O:
                    switch (dominantGrid) {
                        case GRID_EMPTY:
                            spaceO += spaceEmpty;
                            spaceEmpty = 0;
                            break;
                        case GRID_X:    // checkpoint
                            if (spaceX >= WIN_LENGTH)
                                scoreX += continuousX;
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
                default:
                    break;
            }   // end of switch (board_[i][j]

            previousGrid = board_[i][j];

        }   // end of for-j

        // checkpoint
        if (spaceX >= WIN_LENGTH)
            scoreX += continuousX;
        if (spaceO >= WIN_LENGTH)
            scoreO += continuousO;

        totalScoreX += scoreX;
        totalScoreO += scoreO;
        printf("column %d: scoreX=%d, scoreO=%d\n", j, scoreX, scoreO);
    }   // end of for-i

    return totalScoreX - totalScoreO;
}


