#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
bool gameover = false;
bool gameexitrps = false;
bool gameexitbj = false;

#define DEALER_LIMIT 17
#define MAX_LIMIT 21

void clear_screen(){
    system("cls");
}

void wait(int time) {// time in ms
Sleep(time);
}

int ask_user(int choice){
    char input;
    printf("Do You Want To HIT(h) or STAY(s)?\n");
    printf("Choose: ");
    scanf(" %c", &input);  // Boşluk karakteri önceki newline'ı temizler
    
    if (input == 'h' || input == 'H') {
        choice = 0;
    } else if (input == 's' || input == 'S') {
        choice = 1;
    } else if (input == 'e' || input == 'E') {
        choice = 2;
    } else {
        printf("!!! You Must Type (h) - (s) - (e for exit) !!!\n");
        wait(2500);
        choice = -1;  // Geçersiz değer
    }
    return choice;
}

int getcard() {
    int card = (rand() % 13) + 1;
    if (card > 10) {
        card = 10;
    }
    return card;
}

void CheckWinner(int usertotal, int dealertotal) {
    if (dealertotal == MAX_LIMIT) {
        printf("You LOST!!!\n\n");
        printf("----PREPARING NEXT GAME----");
        gameover = true;
        wait(4000);
    }else if (usertotal == MAX_LIMIT) {
        printf("You WON!!!\n\n");
        printf("----PREPARING NEXT GAME----");
        gameover = true;
        wait(4000);
    }else if(usertotal > MAX_LIMIT) {
        printf("You LOST!!!\n\n");
        printf("----PREPARING NEXT GAME----");
        gameover = true;
        wait(4000);
    }else if(dealertotal > MAX_LIMIT) {
        printf("You WON!!!\n\n");
        printf("----PREPARING NEXT GAME----");
        gameover = true;
        wait(4000);
    } else if (dealertotal >= DEALER_LIMIT && dealertotal < MAX_LIMIT) {
        if(usertotal > dealertotal){
            printf("You WON!!!\n\n");
            printf("----PREPARING NEXT GAME----");
            gameover = true;
            wait(4000);
        } else if (usertotal < dealertotal) {
            printf("You LOST!!!\n\n");
            printf("----PREPARING NEXT GAME----");
            gameover = true;
            wait(4000);
        } else if (usertotal == dealertotal) {
            printf("TIE!!!\n\n");
            printf("----PREPARING NEXT GAME----");
            gameover = true;
            wait(4000);
        }
    }
}

void determine_move(char user_move, char **user_display){
    if(user_move == 'r' || user_move == 'R'){
        *user_display = "Rock";
    }

    if(user_move == 'p' || user_move == 'P'){
        *user_display = "Paper";
    }

    if(user_move == 's' || user_move == 'S'){
        *user_display = "Scissors";
    }
}

void rps_winner() {

}



int main() {
    while(true){
    srand(time(0));
    int gamechoose;

    printf("==========GAME HUB==========\n\n");
    printf("--Avaliable Games--\n");
    printf("1) Rock-Paper-Scissors\n");
    printf("2) Blackjack\n");

    do{printf("Choose a Game:");
       scanf("%d", &gamechoose);
} while(gamechoose < 1 || gamechoose > 2);
clear_screen();
    
//-------------------------------------------------------------

    if(gamechoose == 1) {
        while(gameexitrps == false){
        char user_move;
        char *user_display;
        int ai_move = rand() % 3;
        char *ai_display[] = {"Rock", "Paper", "Scissors"};
        char *ai_displayBEFORE[] = {"Rock...", "Paper...", "Scissors...", "SHOOT"};
        printf("==========ROCK-PAPER-SCISSORS==========EXIT(e)\n\n");
        printf("Rock(r) - Paper(p) - Scissors(s)\n");
        printf("Choose your Move:");
        scanf(" %c", &user_move);
        if(user_move == 'e'|| user_move == 'E') {
            printf("Exiting Game...");
            wait(2000);
            clear_screen();
            gameexitrps = true;
            break;
        }
        determine_move(user_move, &user_display);
        printf("YOU           ||       AI\n");
        for(int i = 0; i <= 3; i++){
        printf("\r%s        ||      %s    ", user_display, ai_displayBEFORE[i]);
        fflush(stdout);
        wait(1000);
        }
        printf("\r%s        ||      %s    ", user_display, ai_display[ai_move]);
        wait(1000);



    } 
}
//-----------------------------------------------------------------
    if(gamechoose == 2) {

    while(gameexitbj == false) {
    gameover = false;
    int startinghand_d = getcard();
    int startinghand1_u = getcard();
    int startinghand2_u = getcard();
    int choice;
    int dealertotal = startinghand_d;
    int usertotal = startinghand1_u + startinghand2_u;


    
    clear_screen();
    printf("==========BLACKJACK========== | EXIT(e)\n\n");
    printf("Dealer's Hand: [Hidden] - %d | TOTAL: %d\n\n", startinghand_d, dealertotal);
    printf("Your Hand: %d - %d | TOTAL: %d\n", startinghand1_u, startinghand2_u, usertotal);
    do {choice = ask_user(choice);
    }
    while(choice < 0 || choice > 2 );

    while(gameover == false) {

        if(choice == 1) {
            while(dealertotal < DEALER_LIMIT){
                int tempdrew = dealertotal;
                dealertotal += getcard();
                printf("\nDealer Drew %d | TOTAl: %d\n", dealertotal - tempdrew , dealertotal);
                wait(1500);
                   CheckWinner(usertotal, dealertotal);
                    if(gameover == true) {
                    break;
                }
                } 
            }

        if(choice == 0) {
           while(choice == 0 && usertotal < MAX_LIMIT){
            int tempdrew = usertotal;
                usertotal += getcard();
                printf("\nYou Drew %d | TOTAL: %d\n", usertotal - tempdrew, usertotal);
                CheckWinner(usertotal, dealertotal);
                if(gameover == true) {
                    break;
                }
                do {choice = ask_user(choice);
                }
                while(choice < 0 || choice > 2 );
           }
            
        }
        if(choice == 2) {
            gameexitbj = true;
            printf("Exiting Game...\n");
            wait(2000);
            clear_screen();
            break;
            

        }
    }
}

}


    
}

//----------------------------------------------------------


}

