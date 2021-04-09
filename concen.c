#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
/*
AUTHOR: Ryan Dawson
DATE: 4/8/2021
*/
void initializeGame();
int main();
void teardown();
int score; //Global score variable which is updated with each match
char *strings[] = {"frog", "cow", "moose", "raccoon", "pig", "monkey", "giraffe", "turtle", "dog", "cat",
                   "frog", "cow", "moose", "raccoon", "pig", "monkey", "giraffe", "turtle", "dog", "cat"};
int countArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int remainingCards;
int *ptr;
int exitGame = 0;

//Structure to hold all card values
struct Card
{
    int number;
    char animal[10];
    bool chosen;
};

//Creates 20 diffrent structures of the Card structure
struct Card cards[20];
struct Card chosenCards[20];

int acceptInput() //Takes input from user and returns it as choice, saved to number variable
{
    int choice = 0;
    int alreadyChosen = 0;
    //Checks to make sure card hasn't been chosen, if it has, new input is requested
    while (alreadyChosen == 0)
    {
        printf("Enter a number between 1 and 20: \n");
        scanf("%d", &choice);
        if (cards[choice].chosen < 1) //Checks to see if current card's value has already been chosen
        {
            alreadyChosen++;
        }
        else
        {
            printf("CARD HAS ALREADY BEEN CHOSEN! Try again...\n");
        }
    }
    return choice;
}
//Compares strings of the cards to see if they match, if so, adds a point to score
int updateWorld(struct Card card1, struct Card card2)
{
    if ((strcmp(card1.animal, card2.animal)) == 0) //If strings of both cards match, point is earned
    {
        score++;
        if (score == 10)
        {
            //Prints when final match of game is found and prompts user to play again
            printf("Final match has been found!\nGAME OVER!\n");
            int again;
            printf("Play again? Enter 1 for YES or 2 for NO...\n");
            scanf("%d", &again);
            if (again == 1)
            {
                teardown(); //Tears down game
                main();     //Calls main to restart game
            }
            else if (again == 2)
            {
                exitGame = 1;
                teardown(); //Tears down game
                return 2;
            }
        }
        return 1;
    }
    else
    {
        return 2;
    }
}
//Displays to console whether a match has been found, displays global score
int displayWorld(int world, int num1, int num2)
{
    if (world == 1)
    {
        printf("The card selections are a match!\n");
        printf("Current game score is: %d\n", score);
        if (remainingCards > 0) //Keeps track of how many cards are left after a successful match
        {
            remainingCards = remainingCards - 2;
        }
        //Adjusts member of card to indicate it has already been chosen so acceptInput won't take it again
        cards[num1].chosen = 1;
        cards[num2].chosen = 1;
    }
    else if (world == 2)
    {
        printf("The card selections are not a match\n");
        printf("Current game score is: %d\n", score);
    }
    if (remainingCards != 0)
    {
        printf("Remaining cards on the board: %d\n", remainingCards); //Displays how many cards are remaining in play
    }
}
//Shuffles string array to give random assortment each round
void shuffle()
{
    srand(time(0)); //CPU time is used as a seed
    int size = 20;
    if (size > 1)
    {
        int i;
        for (i = 0; i < size - 1; i++)
        {
            int j = rand() % 20;
            //Switches indexes with random numbers and i;
            char *temp = strings[j];
            strings[j] = strings[i];
            strings[i] = temp;
        }
    }
}

//Sets up the game
//Resets values upon game restarting
void initializeGame()
{
    int n = 20;
    ptr = (int *)malloc(n * sizeof(int)); //Allocates memory for the game
    score = 0;
    remainingCards = 20;
    int loop = 0;
    exitGame = 0;
    int world = 0;
    int chooseCount = 0;
    printf("Setting up the game...\n");
    shuffle(); //Shuffles string array so they have random assignment each playthrough
    /*USED FOR DISPLAYING SHUFFLED ARRAY
    for (int p = 0; p < 20; p++)
    {
        printf("%i: %s\n", p, strings[p]);
    }
    */
    for (int i = 1; i < 21; i++) //Assigns each card with a value and string corresponding to the shuffled array
    {
        cards[i].number = i;
        strcpy(cards[i].animal, strings[i - 1]);
        cards[i].chosen = 0;
    }
    //USED FOR DISPLAYING CARDS
    for (int k = 1; k < 21; k++)
    {
        printf("NUMBER: %d\nANIMAL: %s\n", cards[k].number, cards[k].animal);
    }
}

//Breaks down the game and frees memory
void teardown()
{
    printf("Destroying the game...\n");
    ptr = 0;
    free(ptr);
}

int main()
{
    //Declaration of variables
    int loop = 0;
    int num1, num2;
    int world = 0;
    struct Card card1;
    struct Card card2;
    int chooseCount = 0;
    //Calls to initialize game
    initializeGame();
    //Main game loop, breaks if 0 is input
    while (exitGame == 0)
    {
        //Sets loop back to 0 if it is broken, prevents infinite loop
        loop = 0;
        //Accepts numbers and error checks, if all passes, loops is broken which then updates and displays to console
        while (loop == 0)
        {
            loop = 0;
            //Calls acceptInput to scan for 2 number inputs
            num1 = acceptInput();
            num2 = acceptInput();
            card1 = cards[num1];
            card2 = cards[num2];
            //If number is equal to zero, game exits and tearsdown
            if (num1 == 0 || num2 == 0)
            {
                printf("Invalid input of 0!\n");
                loop++;
                exitGame++;
            }
            //If numbers are within bounds, function continues, otherwise new inputs are taken from user
            if (num1 <= 20 && num1 >= 0)
            {
                if (num2 <= 20 && num2 >= 0)
                {
                    //If numbers are equivalent, input loop is broken, error is output to console, and new inputs are taken
                    if (num1 != num2)
                    {
                        loop++;
                    }
                    else
                        printf("Numbers cannot match!\n");
                }
                else
                {
                    printf("Value %d exceeds maximum of 20, try again\n", num2);
                }
            }
            else
            {
                printf("Value %d exceeds maximum of 20, try again\n", num1);
            }
        }
        //Checks to make sure exit value is not zero
        //i.e. zero was not input, if condition passes, prints updates and displays
        if (exitGame == 0)
        {
            world = updateWorld(card1, card2);
            if (exitGame == 0)
            {
                printf("Your first card was %d (%s)\n", card1.number, card1.animal);
                printf("Your second card was %d (%s)\n\n", card2.number, card2.animal);
                displayWorld(world, num1, num2); //Displays to console
            }
        }
    }
    return 0;
}