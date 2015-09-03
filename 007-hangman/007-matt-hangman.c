#include<stdio.h>
#include<stdint.h>
#include<string.h>

#define clrscr() puts ("\e[2J\e[1;1H")

#define MAX_GUESSES 11

const char* man = "\0(X)\n/|\\\n/\\\n";

void drawMan(uint8_t level){
    int i;
    for(i=0; i<=level; i++){
        printf("%c", man[i]);
    }
    printf("\n\n");
}

void drawWord(char* word, size_t length, uint8_t* guessed){
    uint8_t i;
    for(i=0; i<length; i++){
        if(guessed[i]){
            putchar(word[i]);
        }else{
            putchar('_');
        }
        putchar(' ');
    }
    putchar('\n');
}

int containsChar(char guess, char* word, size_t length, uint8_t* guessed){
    int i,r=0;
    for(i=0;i<length;i++){
        if(!guessed[i] && word[i]==guess) r++;
    }
    return r;
}

void placeGuess(char guess, char* word, size_t length, uint8_t* guessed){
    int i;
    for(i=0;i<length;i++){
        if(!guessed[i] && word[i]==guess)
            guessed[i] = 1;
    }
}

char getInput(){
    char c;
    printf("Guess a letter:");
    c = getchar();
    fflush(stdin);
    return c;
}

int hasWon(uint8_t* guessed, size_t length){
    uint8_t i,j;
    j = guessed[0];
    for(i=1; i<length; i++){
        j = j && guessed[i];
    }
    return j;
}

void game(){
    char* word = "hangman";
    size_t length = strlen(word);
    uint8_t guessed[length];
    memset(guessed, 0, sizeof(guessed));
    uint8_t guesses = 0;
    char guess;

    while(guesses <= MAX_GUESSES && !hasWon(guessed, length)){
        drawMan(guesses);
        drawWord(word, length, guessed);
        guess = getInput();
        if(containsChar(guess, word, length, guessed)){
            placeGuess(guess, word, length, guessed);
        }else if(guess != '\n'){
            guesses++;
        }
        clrscr();
    }
    if(hasWon(guessed, length)){
        printf("Y O U W O N");
    }else{
        printf("G A M E O V E R");
    }
}

int main(void){
    game();
}
