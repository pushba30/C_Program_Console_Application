#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#define SPACE 32
#define HL 196
#define VL 179
#define TT 194
#define LST 195
#define RST 180
#define BT 193
#define LT 218
#define RT 191
#define LB 192
#define RB 217
#define CROSS 197
#define BS 8
#define TOTCOLS 80
#define TOTROWS 25
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 5
#define DIM 9
#define SAFE 1
#define UNSAFE 0
#define FOUND 1
#define NOT_FOUND 0


void sudokuSolver(int orgi[DIM][DIM]);
void sudokuSolver_helper(int orgi[DIM][DIM], int copy[DIM][DIM], int row, int col);
int isSafe(int copy[DIM][DIM], int wr, int wc, int trail );

int found_solution = NOT_FOUND;
int org_col;
int org_row;

//Main original Box Dimensions
//       80    -    (5 * 9) + (9 +1)  => 80-55 / 2 => 12
org_col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
//       25     -  (9 +10 ) =>25 -19 /2 => 6/2 = > 3
org_row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;


void sudokuSolver(int orgi[DIM][DIM]){

    int copy[DIM][DIM];
    int row;
    int col;
    // Making Copy array

    for( row = 0; row < DIM ; row += 1) {
        for( col = 0; col < DIM ; col += 1) {
            copy[row][col] = orgi[row][col];
        }
    }
    sudokuSolver_helper(orgi,copy,0,0);
}

void sudokuSolver_helper(int orgi[DIM][DIM], int copy[DIM][DIM], int row, int col) {

    int wr;
    int wc;
    wr = row;
    wc = col;
    //Boundary Check  first we can tell our base case by our row become our DIM\
    for this first we to check our boundary like its crossing or not

    //Update our Boundary and increment our Row
    if(wc == DIM)
    {
        wr += 1;
        wc = 0;
    }


    //If our Row becomes our DIM it is solved
    if(wr == DIM) {
        found_solution = FOUND;
        int text_print_row;
        int text_print_col;

        text_print_col = org_col;
        text_print_row = org_row;

        text_print_col += 18;
        text_print_row += 19;
        gotoxy(text_print_col, text_print_row);
        printf("......Solved........");
//        int row;
//        int col;
//        for( row =0; row < DIM ; row += 1, printf("\n")) {
//            for( col =0; col < DIM ; col += 1) {
//                printf("%d ",copy[row][col]);
//            }
//        }
//        getch();
        int our_col;
        int our_row;
        our_col = org_col;
        our_row = org_row;

        our_row += 20;
        drawBox( our_col, our_row);
        printAns(copy, our_col, our_row);
        return;
    }

    if(orgi[wr][wc]!=0) {
        sudokuSolver_helper(orgi, copy, wr, wc+1 );
    }
    else {
        int trail;
        //Enumerate All possible Choices
        for(trail = 1; trail <= DIM && (found_solution != FOUND); trail += 1) {
            // Check our Choice is valid or not
            if(isSafe(copy, wr, wc, trail) == SAFE) {
                copy[wr][wc]=trail;
                //Continue Process
                sudokuSolver_helper(orgi, copy, wr, wc+1);
                copy[wr][wc]=0;
            }
        }
    }
}

int isSafe(int copy[DIM][DIM], int wr, int wc, int trail ) {

    int row;
    int col;

    //Row Check
    row=wr;
    for( col = 0; col < DIM ; col += 1) {
        if(copy[row][col]==trail)
            return UNSAFE;
    }

    //Column Check
    col=wc;
    for( row = 0; row < DIM; row += 1) {
        if(copy[row][col]==trail)
            return UNSAFE;
    }

    //Sub matrix check
    row=(wr/3)*3;
    col=(wc/3)*3;
    int r;
    int c;
    for(r = 0; r < 3; r += 1) {
        for( c = 0; c < 3; c += 1) {
            if(copy[row+r][col+c] == trail)
                return UNSAFE;
        }
    }
    return SAFE;
}


void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBox(int col, int row) {

    int our_row;
    int our_col;
    int ctr1;
    int ctr2;
    int ctr3;
    int ct4;
    /*
    //       80    -    (5 * 9) + (9 +1)  => 80-55 / 2 => 12
    col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
    //       25     -  (9 +10 ) =>25 -19 /2 => 6/2 = > 3
    row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;
    */

    our_col = col;
    our_row = row;
    gotoxy ( our_col, our_row);


    //Starting of First Row

    printf("%c",LT);
    for(ctr2 = 1; ctr2 <= DIM ; ctr2 += 1) {
        //Printing Horizontal Line
        for( ctr1 = 1; ctr1 <= 5 ; ctr1 += 1)
            printf("%c",HL);
        //Printing Top T line of Each 5 space
        printf("%c",TT);
    }
    printf("%c%c",BS,RT);

    //First Row Completed;
    our_row += 1;
    gotoxy(our_col,our_row);
    for(ctr3 = 1; ctr3 <= DIM ; ctr3 += 1) {
        printf("%c",VL);
        for(ctr1 = 1; ctr1 <= DIM; ctr1 +=1) {
            //Printing Input space Box
            for( ctr2 = 1; ctr2 <= 5; ctr2 += 1)
                printf("%c",SPACE);
            //Printing Vertical Line
            printf("%c",VL);
        }
        our_row += 1;
        gotoxy(our_col,our_row);

        printf("%c",LST);
        for( ctr1 = 1; ctr1 <= DIM ; ctr1 += 1) {
            for(ctr2 = 1; ctr2 <= 5 ; ctr2 += 1)
                printf("%c",HL);
            printf("%c",CROSS);
        }
        printf("%c%c",BS,RST);
        our_row += 1;
        gotoxy(our_col, our_row);
    }

    our_row -= 1;
    gotoxy(our_col,our_row);

    printf("%c",LB);
    for(ctr1 = 1; ctr1 <= DIM; ctr1 += 1) {
        for(ctr2 = 1; ctr2 <= 5; ctr2 += 1)
            printf("%c",HL);
        printf("%c",BT);
    }
    printf("%c%c",BS,RB);
    //getch();
}

void userInput(int col, int row) {
    int our_row;
    int our_col;
    int work_row;
    int work_col;
    int mov_row;
    int mov_col;
    /*
    //       80    -    (5 * 9) + (9 +1)  => 80-55 / 2 => 12
    col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
    //       25     -  (9 +10 )
    row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;
    */

    our_col = col;
    our_row = row;

    //Our input cursor should be one row below
    our_row += 1;
    //And our column shoulb be in 3rd pos from our starting our width is 5
    our_col+=3;

    gotoxy ( our_col, our_row);

    mov_row = our_row;
    mov_col = our_col;

    int sudoku[DIM][DIM];
    for( work_row = 0; work_row < DIM ; work_row += 1) {
        for(work_col = 0; work_col < DIM; work_col += 1){
            scanf("%d",&sudoku[work_row][work_col]);
            mov_col += 6;
            gotoxy( mov_col, mov_row );
        }
        mov_row += 2;
        mov_col = our_col;
        gotoxy(mov_col, mov_row);
    }

    sudokuSolver(sudoku);
    //getch();

}

//Only for Checking
void dummyFill() {
    int row;
    int col;
    int work_row;
    int work_col;
    int mov_row;
    int mov_col;
    char ch;
    //       80    -    (5 * 9) + (9 +1)  => 80-55 / 2 => 12
    col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
    //       25     -  (9 +10 )
    row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;

    row += 1;
    col+=3;

    gotoxy ( col, row);

    mov_row = row;
    mov_col = col;

    //Dummy Matrix

    int sudoku[DIM][DIM]= {
                      {3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 9, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 6, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}
                      };;

    for( work_row = 0; work_row < DIM ; work_row += 1) {
        for(work_col = 0; work_col < DIM; work_col += 1){
            printf("%d",sudoku[work_row][work_col]);
            mov_col += 6;
            gotoxy( mov_col, mov_row );
        }
        mov_row += 2;
        mov_col = col;
        gotoxy(mov_col, mov_row);
    }
    getch();
    sudokuSolver(sudoku);
}


void printAns(int sudoku[DIM][DIM], int col, int row) {

    int our_row;
    int our_col;
    int work_row;
    int work_col;
    int mov_row;
    int mov_col;

    /*
    //       80    -    (5 * 9) + (9 +1)  => 80-55 / 2 => 12
    col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
    //       25     -  (9 +10 )
    row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;
    */

    our_row = row;
    our_col = col;

    our_row += 1;
    our_col+=3;

    gotoxy ( our_col, our_row);

    mov_row = our_row;
    mov_col = our_col;

    for( work_row = 0; work_row < DIM ; work_row += 1) {
        for(work_col = 0; work_col < DIM; work_col += 1){
            printf("%d",sudoku[work_row][work_col]);
            mov_col += 6;
            gotoxy( mov_col, mov_row );
        }
        mov_row += 2;
        mov_col = our_col;
        gotoxy(mov_col, mov_row);
    }
}

int main() {

    int text_print_row;
    int text_print_col;

    text_print_row = org_row;
    text_print_col = org_col;

    text_print_row -= 2;
    text_print_col += 10;


    gotoxy (text_print_col, text_print_row);

    printf("Hello.. Welcome to Sudoku Solver .....");

    text_print_row += 1;
    text_print_col -= 11;
    gotoxy(text_print_col, text_print_row);

    printf("Rules are Simple PUT values on BOX and PUT 0 for EMPTY boxes");

    //getch();

    int our_row;
    int our_col;

    our_col = org_col;
    our_row = org_row;

    drawBox(our_col, our_row);

   userInput(our_col, our_row);

   //  dummyFill();

  //  printf("%d",found_solution);

     if( found_solution == NOT_FOUND ) {

        text_print_col = org_col;
        text_print_row = org_row;

        text_print_col += 2;
        text_print_row += 19;

        gotoxy(text_print_col, text_print_row);
        printf("!! Sorry..Solution Not Found .. Try to Check Values");
     }

    return EXIT_SUCCESS;
}

