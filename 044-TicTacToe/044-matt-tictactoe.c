/*tic-tac-toe*/
#include<stdio.h>
#define clrscr() puts("\e[2J\e[1;1H")
#define BOARD_SIZE 3
#define XWIN BOARD_SIZE*(int)'X'
#define OWIN BOARD_SIZE*(int)'O'

char board[BOARD_SIZE][BOARD_SIZE];
int turns=0;

struct point{
    int x;
    int y;
};

int canPlace(struct point pos){
    return pos.x>=0 && pos.x<BOARD_SIZE && pos.y>=0 && pos.y<BOARD_SIZE && board[pos.x][pos.y]==NULL;
}

void placePiece(char piece, struct point pos){
    board[pos.x][pos.y] = piece;
}

struct point* getInput(struct point *pos){
    char c = turns%2==0?'X':'O';
    printf("Enter X coord(%c): ", c);
    scanf("%d", &pos->x);
    printf("Enter Y coord(%c): ", c);
    scanf("%d", &pos->y);
    return pos;
}

char hasWon(){
    char ret=NULL;
    int i,j,Csum=0,Rsum=0,Dsum=0,Asum=0;
    if(++turns==BOARD_SIZE*BOARD_SIZE) {
        ret = 'T';
    }
    for(i=0;i<BOARD_SIZE;i++){
        for(j=0;j<BOARD_SIZE;j++){
            Csum += board[i][j];                        /*column*/
            Rsum += board[j][i];                        /*row*/
            if(i==j) Dsum+=board[i][j];                 /*diagonal*/
            if(i+j==BOARD_SIZE-1) Asum+=board[i][j];    /*antidiagonal*/
        }
        if(Csum==XWIN || Rsum==XWIN || Dsum==XWIN || Asum==XWIN){
            ret = 'X';
            break;
        }else if(Csum==OWIN || Rsum==OWIN || Dsum==OWIN || Asum==OWIN){
            ret = 'O';
            break;
        }else{
            Csum=Rsum=0;
        }
    }
    return ret;
}

void printBoard(){
    int i,j,k;
    clrscr();
    for(i=0; i<BOARD_SIZE; i++){
        for(j=0;j<BOARD_SIZE;j++){
            putchar(board[i][j]==0?' ':board[i][j]);
            if(j<BOARD_SIZE-1){
                putchar('|');
            }
        }
        putchar('\n');
        if(i<BOARD_SIZE-1){
            for(k=0;k<(2*BOARD_SIZE)-1;k++){
                putchar('-');
            }
            putchar('\n');
        }
    }
}

void game(){
    struct point pos;
    char state,c;
    printBoard();
    do{
        do{
            getInput(&pos);
        }while(!canPlace(pos));
        c = turns%2==0?'X':'O';
        placePiece(c, pos);
        printBoard();
    }while((state=hasWon())==NULL);
    endGame(state);
}

void endGame(char state){
    if(state=='T'){
        printf("The game Ended in a Tie!\n");
    }else{
        printf("%c Won!\n", state);
    }
}

int main(){
    game();
}
