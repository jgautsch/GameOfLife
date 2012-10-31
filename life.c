//
//  CSE20211
//  Prof. Thain
//
//  Created by Jon Gautsch
//  life.c
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BOARD_SIZE 40 //board size nxn

void printCharArray(char a[BOARD_SIZE][BOARD_SIZE]);
void initBoardArray(char board_array1[BOARD_SIZE][BOARD_SIZE], int size, char c);
void clearScreen(void);
int preGame(char board_array1[BOARD_SIZE][BOARD_SIZE], char board_array2[BOARD_SIZE][BOARD_SIZE]);
void playGameForever(char board_array1[BOARD_SIZE][BOARD_SIZE], char board_array2[BOARD_SIZE][BOARD_SIZE]);
void oneTic(char board_array1[BOARD_SIZE][BOARD_SIZE], char board_array2[BOARD_SIZE][BOARD_SIZE]);
void UInewCellAlive(char board_array1[BOARD_SIZE][BOARD_SIZE]);
void UIremoveCell(char board_array1[BOARD_SIZE][BOARD_SIZE]);
int surroundCount(char board_array1[BOARD_SIZE][BOARD_SIZE], int row, int col, int isItAlive);
void setFirstArrayEqualToSecond(char board_array1[BOARD_SIZE][BOARD_SIZE], char board_array2[BOARD_SIZE][BOARD_SIZE]);


int main(void){
    
	char board_array1[BOARD_SIZE][BOARD_SIZE];
    char board_array2[BOARD_SIZE][BOARD_SIZE];
    initBoardArray(board_array1, BOARD_SIZE, '.'); //initializes board full of '.'s
    initBoardArray(board_array2, BOARD_SIZE, '.');
    
    if (preGame(board_array1, board_array2) == -1) return 0;

	return 0;
}

/*************************     PRINT CHAR ARRAY       *****************************************/

//prints out the board array to the console
void printCharArray(char a[BOARD_SIZE][BOARD_SIZE]){ 
    int i;
    int j;
    
    printf("  ");
    for(i = 0; i < BOARD_SIZE; i++){
        printf("%3d", i);
    }
    printf("\n");
    for(i = 0; i < BOARD_SIZE; i++){ //two loops print all the elements of the 2D array
        printf("%2d", i);
        for(j = 0; j < BOARD_SIZE; j++){
            printf("%3c", a[i][j]);
        }
        printf("\n");
    }
}

/**************************   INITIALIZE BOARD ARRAY    ****************************************/

//initializes the board with all '.'s except the middle 4 pieces
void initBoardArray(char board_array1[BOARD_SIZE][BOARD_SIZE], int size, char c){
    int i;
    int j;
    
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            board_array1[i][j] = c;
        }
    }
}

/***********************    Clear Screen    **********************/

void clearScreen(void){
    //clear screen
    printf("\033[2J\033[H");
}

/********************** PreGame Commands   ************************/

int preGame(char board_array1[BOARD_SIZE][BOARD_SIZE], char board_array2[BOARD_SIZE][BOARD_SIZE]){
    int endLoop = 0;
    char c;
    
    while (endLoop == 0){
        
        //clear old board
        clearScreen();
        //print new board
        printCharArray(board_array1);
        
        /*if (c != '\n')*/ printf("\nPlease Enter:\na - enter a new cell\nr - remove a cell\nn - advance simulation 1 tic\nq - quit\np - play game forever\n\n--> ");
        scanf("%c", &c);
        
        
        if (c != '\n'){
            switch (c) {
                case 'a':
                    //new cell
                    UInewCellAlive(board_array1);
                    break;
                case 'r':
                    //remove cell
                    UIremoveCell(board_array1);
                    break;
                case 'n':
                    //advance simulation 1 tic
                    oneTic(board_array1, board_array2);
                    break;
                case 'p':
                    // play game forever
                    playGameForever(board_array1, board_array2);
                    break;
                case 'q':
                    //quit program
                    endLoop = -1;
                    return endLoop;
                default:
                    break;
            }
        }
    }
    return endLoop;
}

/************************   Play Game Forever   ********************/

void playGameForever(char board_array1[BOARD_SIZE][BOARD_SIZE], char board_array2[BOARD_SIZE][BOARD_SIZE]){
    int i, j, isItAlive, countOfSurround;
    setFirstArrayEqualToSecond(board_array2, board_array1);
    while(1){
        for(i = 0; i < BOARD_SIZE; i++){
            for (j = 0; j < BOARD_SIZE; j++) {
                if (board_array1[i][j] == '.') {
                    //it's a dead cell
                    isItAlive = 0;
                    countOfSurround = 0;
                    countOfSurround = surroundCount(board_array1, i, j, isItAlive);
                    if (countOfSurround == 3) {
                        //cell comes alive
                        board_array2[i][j] = 'X';
                    }
                } else {
                    //it's a live cell
                    isItAlive = 1;
                    countOfSurround = 0;
                    countOfSurround = surroundCount(board_array1, i, j, isItAlive);
                    if (countOfSurround != 2 && countOfSurround != 3) {
                        //kill cell
                        board_array2[i][j] = '.';
                    }
                }
            }
        }
        
        clearScreen();
        printCharArray(board_array1);
        usleep(100000);
        //set array just printed equal to the newly set array
        setFirstArrayEqualToSecond(board_array1, board_array2);
        
    }
}
/**************************    One Tic Forward  ********************/

void oneTic(char board_array1[BOARD_SIZE][BOARD_SIZE], char board_array2[BOARD_SIZE][BOARD_SIZE]){
    int i, j, isItAlive, countOfSurround;
    setFirstArrayEqualToSecond(board_array2, board_array1);
    for(i = 0; i < BOARD_SIZE; i++){
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board_array1[i][j] == '.') {
                //it's a dead cell
                isItAlive = 0;
                countOfSurround = 0;
                countOfSurround = surroundCount(board_array1, i, j, isItAlive);
                if (countOfSurround == 3) {
                    //cell comes alive
                    board_array2[i][j] = 'X';
                }
            } else {
                //it's a live cell
                isItAlive = 1;
                countOfSurround = 0;
                countOfSurround = surroundCount(board_array1, i, j, isItAlive);
                if (countOfSurround != 2 && countOfSurround != 3) {
                    //kill cell
                    board_array2[i][j] = '.';
                }
            }
        }
    }
    
    clearScreen();
    printCharArray(board_array1);
    //set array just printed equal to the newly set array
    setFirstArrayEqualToSecond(board_array1, board_array2);
}
/*************************   UI New Cell Alive  *********************/

void UInewCellAlive(char board_array1[BOARD_SIZE][BOARD_SIZE]){
    
    int i, j;
    //enter row
    printf("\nEnter the row number for new cell: ");
    scanf("%d", &i);
    while (i > BOARD_SIZE || i < 0){
        printf("invalid coordinate, please try again: ");
        scanf("%d", &i);
    }
    //enter column
    printf("Enter the column number for new cell: ");
    scanf("%d", &j);
    while (i > BOARD_SIZE || i < 0){
        printf("invalid coordinate, please try again: ");
        scanf("%d", &i);
    }
    //update celll
    board_array1[i][j] = 'X';
    
    
}

/************************    UI Remove Cell   ****************************/

void UIremoveCell(char board_array1[BOARD_SIZE][BOARD_SIZE]){
    int i, j;
    //enter row
    printf("\nEnter the row number for cell to be removed: ");
    scanf("%d", &i);
    while (i > BOARD_SIZE || i < 0){
        printf("invalid coordinate, please try again: ");
        scanf("%d", &i);
    }
    //enter column
    printf("Enter the column number for cell to be removed: ");
    scanf("%d", &j);
    while (i > BOARD_SIZE || i < 0){
        printf("invalid coordinate, please try again: ");
        scanf("%d", &i);
    }
    //update celll
    board_array1[i][j] = '.';
    
}

/**********************  Count surrounding alive/dead cells *****************/

int surroundCount(char board_array1[BOARD_SIZE][BOARD_SIZE], int row, int col, int isItAlive){
    int surroundCount = 0;
    //count the number of live cells surrounding the cell in question
    if (board_array1[row][col+1] == 'X') surroundCount++;
    if (board_array1[row+1][col+1] == 'X') surroundCount++;
    if (board_array1[row+1][col] == 'X') surroundCount++;
    if (board_array1[row+1][col-1] == 'X') surroundCount++;
    if (board_array1[row][col-1] == 'X') surroundCount++;
    if (board_array1[row-1][col-1] == 'X') surroundCount++;
    if (board_array1[row-1][col] == 'X') surroundCount++;
    if (board_array1[row-1][col+1] == 'X') surroundCount++;
    return surroundCount;
}

/************************    Set first array equal to second   *****************/

void setFirstArrayEqualToSecond(char board_array1[BOARD_SIZE][BOARD_SIZE], char board_array2[BOARD_SIZE][BOARD_SIZE]){
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++){
        for (j = 0; j < BOARD_SIZE; j++) {
            board_array1[i][j] = board_array2[i][j];
        }
    }
}