#include <FEHLCD.h>
#include <FEHUtility.h>
#include <FEHImages.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

//Blueprint for Card object
struct Card{
    char *name;
    char *file;
    int value;
};

void menu();
int bet();
void payout(char winner, int bet);
void display(Card player_hand[], Card computer_hand[], Card deck[], bool player_turn);
void hit (Card current_deck[], Card hand[]);
int cardsInArray(Card array[], int maxSize);
int cardValueSum(Card hand[]);
void computerDeal(Card player_hand[], Card computer_hand[], Card deck[]);
char CheckWinner(int player_score, int computer_score);
int getBalance();
int getHighScore();
void resetBalance();


int main() {
    //deck of cards
    while (true){
    Card deck[52] = {
        {"2_of_hearts", "pictures/cards/2_of_hearts.png", 2},
        {"3_of_hearts", "pictures/cards/3_of_hearts.png", 3},
        {"4_of_hearts", "pictures/cards/4_of_hearts.png", 4},
        {"5_of_hearts", "pictures/cards/5_of_hearts.png", 5},
        {"6_of_hearts", "pictures/cards/6_of_hearts.png", 6},
        {"7_of_hearts", "pictures/cards/7_of_hearts.png", 7},
        {"8_of_hearts", "pictures/cards/8_of_hearts.png", 8},
        {"9_of_hearts", "pictures/cards/9_of_hearts.png", 9},
        {"10_of_hearts", "pictures/cards/10_of_hearts.png", 10},
        {"jack_of_hearts", "pictures/cards/jack_of_hearts.png", 10},
        {"queen_of_hearts", "pictures/cards/queen_of_hearts.png", 10},
        {"king_of_hearts", "pictures/cards/king_of_hearts.png", 10},
        {"ace_of_hearts", "pictures/cards/ace_of_hearts.png", 11},

        {"2_of_diamonds", "pictures/cards/2_of_diamonds.png", 2},
        {"3_of_diamonds", "pictures/cards/3_of_diamonds.png", 3},
        {"4_of_diamonds", "pictures/cards/4_of_diamonds.png", 4},
        {"5_of_diamonds", "pictures/cards/5_of_diamonds.png", 5},
        {"6_of_diamonds", "pictures/cards/6_of_diamonds.png", 6},
        {"7_of_diamonds", "pictures/cards/7_of_diamonds.png", 7},
        {"8_of_diamonds", "pictures/cards/8_of_diamonds.png", 8},
        {"9_of_diamonds", "pictures/cards/9_of_diamonds.png", 9},
        {"10_of_diamonds", "pictures/cards/10_of_diamonds.png", 10},
        {"jack_of_diamonds", "pictures/cards/jack_of_diamonds.png", 10},
        {"queen_of_diamonds", "pictures/cards/queen_of_diamonds.png", 10},
        {"king_of_diamonds", "pictures/cards/king_of_diamonds.png", 10},
        {"ace_of_diamonds", "pictures/cards/ace_of_diamonds.png", 11},

        {"2_of_clubs", "pictures/cards/2_of_clubs.png", 2},
        {"3_of_clubs", "pictures/cards/3_of_clubs.png", 3},
        {"4_of_clubs", "pictures/cards/4_of_clubs.png", 4},
        {"5_of_clubs", "pictures/cards/5_of_clubs.png", 5},
        {"6_of_clubs", "pictures/cards/6_of_clubs.png", 6},
        {"7_of_clubs", "pictures/cards/7_of_clubs.png", 7},
        {"8_of_clubs", "pictures/cards/8_of_clubs.png", 8},
        {"9_of_clubs", "pictures/cards/9_of_clubs.png", 9},
        {"10_of_clubs", "pictures/cards/10_of_clubs.png", 10},
        {"jack_of_clubs", "pictures/cards/jack_of_clubs.png", 10},
        {"queen_of_clubs", "pictures/cards/queen_of_clubs.png", 10},
        {"king_of_clubs", "pictures/cards/king_of_clubs.png", 10},
        {"ace_of_clubs", "pictures/cards/ace_of_clubs.png", 11},

        {"2_of_spades", "pictures/cards/2_of_spades.png", 2},
        {"3_of_spades", "pictures/cards/3_of_spades.png", 3},
        {"4_of_spades", "pictures/cards/4_of_spades.png", 4},
        {"5_of_spades", "pictures/cards/5_of_spades.png", 5},
        {"6_of_spades", "pictures/cards/6_of_spades.png", 6},
        {"7_of_spades", "pictures/cards/7_of_spades.png", 7},
        {"8_of_spades", "pictures/cards/8_of_spades.png", 8},
        {"9_of_spades", "pictures/cards/9_of_spades.png", 9},
        {"10_of_spades", "pictures/cards/10_of_spades.png", 10},
        {"jack_of_spades", "pictures/cards/jack_of_spades.png", 10},
        {"queen_of_spades", "pictures/cards/queen_of_spades.png", 10},
        {"king_of_spades", "pictures/cards/king_of_spades.png", 10},
        {"ace_of_spades", "pictures/cards/ace_of_spades.png", 11}
    };

    //display main menu
    menu();

    //get player bet
    int player_bet;
    player_bet = bet();

    //deal cards
    Card player_hand[12] = {};
    Card computer_hand[12] = {};

    hit(deck, player_hand); hit(deck, player_hand); hit(deck, computer_hand);
    int player_score = cardValueSum(player_hand);

    //check for blackjack
    bool turn = true;

    if (player_score == 21){
        turn = false;
    } 

    //display hands and prompt for hit or stand
    display(player_hand, computer_hand, deck, turn);
    player_score = cardValueSum(player_hand);

    if (player_score < 21) {
        computerDeal(player_hand, computer_hand, deck);
    }

    //get player and computer scores to see who won
    player_score = cardValueSum(player_hand);
    int computer_score = cardValueSum(computer_hand);

    char winner = CheckWinner(player_score, computer_score);

    //payout player/computer and display end game message
    payout(winner, player_bet);

    int balance = getBalance();

    if (balance <= 0){
        LCD.SetFontColor(BLUE);
        LCD.WriteAt("GAME OVER",100,100);
        resetBalance();
    } else {
        if (winner == 'p'){
            LCD.SetFontColor(BLUE);
            if (player_score == 21 && !turn){
                LCD.WriteAt("BLACKJACK!!!",100,100);
            } else{
                LCD.WriteAt("YOU WIN!",100,100);
            }
        } else if (winner == 'c'){
            LCD.SetFontColor(BLUE);
            LCD.WriteAt("YOU LOSE",100,100);
        } else {
            LCD.SetFontColor(BLUE);
            LCD.WriteAt("TIE",100,100);
        }
    }
    
    int x_pos, y_pos;
    while (!LCD.Touch(&x_pos,&y_pos)){}
    }

}

//main menu function
void menu() {
    bool play = false;
    int x, y;

    FEHImage menu;
    FEHImage stats;
    FEHImage instructions;
    FEHImage credits;

    menu.Open("pictures/main_menu.png");
    stats.Open("pictures/stats.png");
    instructions.Open("pictures/instructions.png");
    credits.Open("pictures/credits.png");
    
    menu.Draw(1,1);
    LCD.Update();

    while(!play){
        while(!LCD.Touch(&x,&y)){}

        while(LCD.Touch(&x,&y)){}

        if (x>107 && x<204){
            if (y>86 && y<110){
                play = true;
            }
            else if (y>124 && y<147){
                LCD.Clear();
                int balance = getBalance();
                int highScore = getHighScore();
                stats.Draw(0,0);

                LCD.SetFontColor(GREEN);
                LCD.WriteAt(highScore,166,75);
                LCD.WriteAt(balance,177,99);

                LCD.Update();

                while(!LCD.Touch(&x,&y)){}

                while(LCD.Touch(&x,&y)){}

                LCD.Clear();
                menu.Draw(1,1);
                LCD.Update();
            }
            else if (y>165 && y<187){
                LCD.Clear();
                instructions.Draw(0,0);
                LCD.Update();

                while(!LCD.Touch(&x,&y)){}

                while(LCD.Touch(&x,&y)){}

                LCD.Clear();
                menu.Draw(1,1);
                LCD.Update();
            }
            else if (y>201 && y<224){
                LCD.Clear();
                credits.Draw(0,0);
                LCD.Update();

                while(!LCD.Touch(&x,&y)){}

                while(LCD.Touch(&x,&y)){}

                LCD.Clear();
                menu.Draw(1,1);
                LCD.Update();
            }
        }

        LCD.Update();
    }
    
}

//Counts the amount of cards in both player and computer hands and the deck
int cardsInArray(Card array[], int maxSize){
    int cards = 0;

    for (int i=0; i<maxSize; i++){
        if (array[i].value != NULL){
            cards++;
        }
    }

    return cards;
}

//Returns the player's current balance
int getBalance(){
    int old_balance;
    FILE *balance = fopen("data/savedbalance.txt", "r");
    fscanf(balance, "%d", &old_balance); /*bring the old balance out of the save file*/
    fclose(balance);
    return old_balance;
}

//Returns the player's current high score
int getHighScore(){
    int highscore;
    FILE *score = fopen("data/highscore.txt", "r");
    fscanf(score, "%d", &highscore); /*bring the old high score out of the save file*/
    fclose(score);
    return highscore;
}

//Calculates the value of a hand. Aces go from a value of 11 to 1 if the value goes over 21
int cardValueSum(Card hand[]){
    int value = 0;
    int high_aces = 0;

    for (int i=0; i<cardsInArray(hand, 12); i++){
        int cardValue = hand[i].value;
        
        value = value + cardValue;

        if (cardValue == 11){
            high_aces++;
        }

        if (value > 21 && high_aces != 0){
            value -= 10;
            high_aces--;
        }
        
    }

    return value;
}

//Evaluates who won the round
char CheckWinner(int player_score, int computer_score)
{
    char winner;
    
    /*assigns winner checking if someone busted*/
    if (player_score > 21 || computer_score > 21)
    {
        if (player_score > 21)
        { 
            winner = 'c';
        }
        
        else if (computer_score > 21)
        {
            winner = 'p';
        }
    }

    else if (player_score != computer_score)
    {
        if (player_score > computer_score)
        {
            winner = 'p';
        }

        else if (computer_score > player_score)
        {
            winner = 'c';
        }
    }

    else /*if the scores are equal*/
    {
        winner = 't';
    }

    return winner;
}

//Takes a random card out of the deck and gives it to either the player or computer's hand
void hit(Card current_deck[], Card hand[]) {
    int deck_size = cardsInArray(current_deck, 52);
    int hand_size = cardsInArray(hand, 12);

    // Generate a random index
    int rd_index = rand() % deck_size;

    // Add the selected card to the hand
    
    hand[hand_size] = current_deck[rd_index];

    // Shift remaining cards in the deck
    for (int i = rd_index; i < deck_size - 1; i++) {
        current_deck[i] = current_deck[i + 1];
    }

    // Nullify the last card in the deck
    current_deck[deck_size - 1].name = NULL;
    current_deck[deck_size - 1].file = NULL;
    current_deck[deck_size - 1].value = NULL;
}

//Pays the player if they win or charges them if they lose
void payout(char winner,int bet) 
{
    int old_balance = getBalance();  
    int highScore = getHighScore();
    
    switch (winner)
    {
    /*player wins*/
    case 'p':
        old_balance += bet; /*add doubled bet to old balance*/
        break;
    /*computer wins*/
    case 'c':
        old_balance -= bet; /*subtract bet from old balance*/
        break;
    }

    if (old_balance > highScore){
        FILE *score = fopen("data/highscore.txt", "w");
        fprintf(score, "%d", old_balance); /*bring the old balance out of the save file*/
        fclose(score);
    }

    FILE *balance = fopen("data/savedbalance.txt", "w");
    fprintf(balance, "%d", old_balance); /*bring the old balance out of the save file*/
    fclose(balance);

}

//Brings the player's balance back to 100 after they lose all their money
void resetBalance(){
    FILE *balance = fopen("data/savedbalance.txt", "w");
    fprintf(balance, "%d", 100); /*bring the old balance out of the save file*/
    fclose(balance);
}

//Displays a page with betting options for the player
int bet()
{
    int bet = 0;
    bool betting = true;
    
    while(betting)
    { 
        /*draw the bet choice screen*/
        LCD.SetBackgroundColor(GREEN);
        LCD.Clear();
        LCD.Update();
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("PLACE YOUR BET!",69,111);

        int balance = getBalance();

        /*draw bet choice rectangles*/
        LCD.SetFontColor(RED);
        LCD.FillRectangle(34,180,50,25);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("5",51,186);

        if (balance >= 50){
            LCD.SetFontColor(RED);
        } else {
            LCD.SetFontColor(GRAY);
        }
        LCD.FillRectangle(98,180,50,25);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("50",110,186);
        

        if (balance >= 100){
            LCD.SetFontColor(RED);
        } else {
            LCD.SetFontColor(GRAY);
        }
        LCD.FillRectangle(162,180,50,25);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("100",166,186);

        if (balance >= 500){
            LCD.SetFontColor(RED);
        } else {
            LCD.SetFontColor(GRAY);
        }
        LCD.FillRectangle(226,180,50,25);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("500",231,186);
        
        /*variables for the position of the click and the edge coordinates of each box*/
        float x_pos,y_pos;
        int y1=180, y2=205;
        int x11=34, x12=84;
        int x21=98, x22=148;
        int x31=162, x32=212;
        int x41=226, x42=276;

        

        /*wait for touch*/
        while (!LCD.Touch(&x_pos,&y_pos)){}

        /*detects which box is clicked based off of its coordinates and assigns the respective value to bet*/
        while (LCD.Touch(&x_pos,&y_pos))
        {
            betting = false;

            if (x_pos >= x11 && x_pos <= x12 && y_pos >= y1 && y_pos <=y2)
            {
                bet=5;
            }

            else if (x_pos >= x21 && x_pos <= x22 && y_pos >= y1 && y_pos <=y2 && balance >= 50)
            {
                bet=50;
            }

            else if (x_pos >= x31 && x_pos <= x32 && y_pos >= y1 && y_pos <=y2 && balance >= 100)
            {
                bet=100;
            }

            else if (x_pos >= x41 && x_pos <= x42 && y_pos >= y1 && y_pos <=y2 && balance >= 500)
            {
                bet=500;
            }

            else {
                betting = true;
            }
        }
        Sleep(1);
        LCD.Clear();
    }

    /*return bet to the main script*/
    return bet;
}

//Hits the computers hand until they reach a score of at least 17
void computerDeal(Card player_hand[], Card computer_hand[], Card deck[]){
    hit(deck, computer_hand);
    display(player_hand, computer_hand, deck, false);

    if (cardValueSum(computer_hand) < 17){
        computerDeal(player_hand, computer_hand, deck);
    }
}

//Displays both the player and computer's hands and prompts the user to hit or stand if it is their turn
void display(Card player_hand[], Card computer_hand[], Card deck[], bool player_turn){
        LCD.Clear();
        LCD.SetBackgroundColor(GREEN);
        LCD.Update();

        int x_pos, y_pos;

        int handSizePlayer = cardsInArray(player_hand, 12);
        int handSizeComputer = cardsInArray(computer_hand, 12);

        for (int i=0; i<handSizePlayer; i++){
            FEHImage card;
            card.Open(player_hand[i].file);

            int xPos = (320 / (handSizePlayer+1)) * (i+1) - 25;
            card.Draw(xPos, 120);
        }

        for (int i=0; i<handSizeComputer; i++){
            FEHImage card;
            card.Open(computer_hand[i].file);

            int xPos = (320 / (handSizeComputer+1)) * (i+1) - 25;
            card.Draw(xPos, 20);
        }

        if(player_turn){
        int btnX = 240;
        int hitY = 180;
        int standY = 210;
        int btnHeight = 25;

        LCD.SetFontColor(RED);
        LCD.FillRectangle(btnX,hitY,75,btnHeight);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("HIT",btnX+18,hitY+4);

        LCD.SetFontColor(RED);
        LCD.FillRectangle(btnX,standY,75,btnHeight);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("STAND",btnX+6,standY+4);

        LCD.Update();
        
            bool clickedbtn = false;
            while (!clickedbtn){
                while (!LCD.Touch(&x_pos,&y_pos)){}
                while(LCD.Touch(&x_pos,&y_pos)){}

                if (x_pos>btnX && x_pos<btnX+75){
                    if (y_pos>hitY && y_pos<hitY+btnHeight){
                        hit(deck, player_hand); 

                        if (cardValueSum(player_hand) > 20){
                            player_turn = false;
                        }

                        display(player_hand, computer_hand, deck, player_turn);
                        clickedbtn = true;
                    } else if (y_pos>standY && y_pos<standY+btnHeight){
                        clickedbtn = true;
                    }
                }
            }
        
        }

        LCD.Update();
}