#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define MAX_WORDS 300
#define MAX_WORD_LENGTH 100

int mainMenu() {
    int choice;
    while(1) {
        system("cls");
        printf("\n\t\t----\033[1mHANGMAN GAME\033[0m----\n\t\t____________________\n");
        printf("\n\t\t.....Choose Mode.... \n\n\t\t1 -> Easy\n\t\t2 -> Medium\n\t\t3 -> Hard\n\n\t\tEnter your choice : "); 
        fflush(stdin); // Flush the input buffer before scanning
        scanf("%d", &choice);
        if(choice > 0 && choice < 4) break;
        else {
            system("cls");
            printf("\n\n\n\t\t\033[1mINVALID CHOICE TRY AGAIN!!!\033[0m\n");
            Sleep(1500);
        }
    }
    return choice;
}

void updateFigure(int wrongGuesses) {
    system("cls");
    printf("\n\t\t---\033[1mHANGMAN GAME\033[0m---\n\n");
    switch(wrongGuesses) {
        case 0 : 
            printf("\t\t _ _ _\n\t\t|/   \n\t\t|     \n\t\t|       \n\t\t|       \n\t\t|\n\t\t+========+\n\t\t+========+\n\n\t Wrong Guesses Before Game Over : 7\n");
            break;
        case 1 : 
            printf("\t\t _ _ _\n\t\t|/  |\n\t\t|     \n\t\t|       \n\t\t|       \n\t\t|\n\t\t+========+\n\t\t+========+\n\n\t Wrong Guesses Before Game Over : 6\n");
            break;
        case 2 : 
            printf("\t\t _ _ _\n\t\t|/  |\n\t\t|   O \n\t\t|       \n\t\t|       \n\t\t|\n\t\t+========+\n\t\t+========+\n\n\t Wrong Guesses Before Game Over : 5\n");
            break;
        case 3 : 
            printf("\t\t _ _ _\n\t\t|/  |\n\t\t|   O \n\t\t|  /    \n\t\t|       \n\t\t|\n\t\t+========+\n\t\t+========+\n\n\t Wrong Guesses Before Game Over : 4\n");
            break;
        case 4 : 
            printf("\t\t _ _ _\n\t\t|/  |\n\t\t|   O \n\t\t|  /|   \n\t\t|       \n\t\t|\n\t\t+========+\n\t\t+========+\n\n\t Wrong Guesses Before Game Over : 3\n");
            break;
        case 5 : 
            printf("\t\t _ _ _\n\t\t|/  |\n\t\t|   O \n\t\t|  /|\\ \n\t\t|       \n\t\t|\n\t\t+========+\n\t\t+========+\n\n\t Wrong Guesses Before Game Over : 2\n");
            break;
        case 6 : 
            printf("\t\t _ _ _\n\t\t|/  |\n\t\t|   O \n\t\t|  /|\\ \n\t\t|  /    \n\t\t|\n\t\t+========+\n\t\t+========+\n\n\t Wrong Guesses Before Game Over : 1\n");
            break;
        case 7 : 
            printf("\t\t _ _ _\n\t\t|/  |\n\t\t|   x \n\t\t|  /|\\ \n\t\t|  / \\ \n\t\t|\n\t\t+========+\n\t\t+========+\n");
            Sleep(500);
            printf("\t  YOU ");
            Sleep(500);
            printf("DID ");
            Sleep(500);
            printf("NOT ");
            Sleep(500);
            printf("SAVE ");
            Sleep(500);
            printf("ME!!\n");
            break;
        default : 
            printf("Wrong case!");
            return;
    }
}

void updateGuess(char *guessedWord, char *word, int wordlength) {
    printf("\n\t\t");
    for(int i=0; i<wordlength; i++) {
        if(guessedWord[i] != word[i]) 
            printf("_ ");
        else 
            printf("%c ", guessedWord[i]);
    }
}

void alphabetsToGuess(char *alpha, char g){
    printf("\n\n\n");
    for(int i=0; i<26; i++){
        if(alpha[i] != (g-32)) printf("\033[1m%c\033[0m  ",alpha[i]);
        else {
            printf("*  ");
            alpha[i] = '*';
        }
    }
}

int main() {
    char easyWords[MAX_WORDS][MAX_WORD_LENGTH];
    char mediumWords[MAX_WORDS][MAX_WORD_LENGTH];
    char hardWords[MAX_WORDS][MAX_WORD_LENGTH];

    FILE *file = fopen("hangman_words.csv", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    char buffer[300];
    int index = 0;

    // Skip the header line
    fgets(buffer, sizeof(buffer), file);

    // Read each line from the CSV
    while (fgets(buffer, sizeof(buffer), file) != NULL && index < MAX_WORDS) {
        // Tokenize the line by commas
        char *token = strtok(buffer, ",");

        // Copy the easy word
        strcpy(easyWords[index], token);

        // Copy the medium word
        token = strtok(NULL, ",");
        strcpy(mediumWords[index], token);

        // Copy the hard word
        token = strtok(NULL, ",");
        strcpy(hardWords[index], token);

        // Move to the next index
        index++;
    }

    fclose(file);

    system("cls");
    printf("\n\t\t---\033[1mHANGMAN GAME\033[0m---\n\n");
    printf("\t\t\t O \n\t\t\t/|\\ \n\t\t\t/ \\ \n\t\t Please save me!!\n\n");

    char ch;

    printf("\n\t\tClick Enter!\n");

    // Get character from keyboard (non-blocking)
    while (ch != 13) {
        ch = _getch();
    } 

    do{
    
    int mainMenuChoice = mainMenu();
    srand(time(NULL));
    int randomIndex = rand() % index; // Use index to ensure it only uses filled slots
    char *word = NULL;

    if(mainMenuChoice == 1) word = easyWords[randomIndex];
    else if(mainMenuChoice == 2) word = mediumWords[randomIndex];
    else word = hardWords[randomIndex];

    int wordLength = strlen(word);
    char guessedWord[wordLength + 1]; // +1 for null terminator
    memset(guessedWord, '_', wordLength); // Initialize with '_'
    guessedWord[wordLength] = '\0'; // Null terminate the guessedWord array

    int wrongGuesses = 0, remainingLetters = wordLength;
    int gameOver = 0, guessedCorrect = 0;
    char g;
    char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (!gameOver) {
        updateFigure(wrongGuesses);
        updateGuess(guessedWord, word, wordLength);
        alphabetsToGuess(alpha, g);
        printf("\n\n\tGuess a letter: ");
        fflush(stdin); // Flush the input buffer before scanning
        scanf(" %c", &g); // Use space before %c to skip whitespace/newline characters

        guessedCorrect = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == g && guessedWord[i] != g) {
                guessedWord[i] = g;
                remainingLetters--;
                guessedCorrect = 1;
            }
        }

        if (!guessedCorrect) {
            wrongGuesses++;
        }

        if (wrongGuesses == 7) {
            updateFigure(wrongGuesses);
            printf("\n\tYou Lost! The word was: %s\n", word);
            gameOver = 1;
        }

        if (remainingLetters == 0) {
            system("cls");
            printf("\n\t\t---\033[1mHANGMAN GAME\033[0m---\n\n");
            printf("\t\t \033[1m_ _ _\033[0m\n\t\t\033[1m|/\033[0m  \n\t\t\033[1m|\033[0m \n\t\t\033[1m|\033[0m   o \n\t\t\033[1m|\033[0m  /|\\ \n\t\t\033[1m|\033[0m  / \\\n\t\t\033[1m+========+\033[0m\n\t\t\033[1m+========+\033[0m\n");
            Sleep(500);
            printf("\t    YOU ");
            Sleep(500);
            printf("SAVED ");
            Sleep(500);
            printf("ME!!\n");
            printf("\n\tCongratulations! You guessed the word: %s\n", word);
            gameOver = 1;
        }
    }

    printf("\n---------------------------------------------------------------\nPress 'Q' to Quit\t\tClick 'Enter Key' to Play again\n");
    ch = _getch();
    }while(ch != 'q');
    system("cls");
    printf("\n\n\n\t\t\033[1mTHANK YOU FOR PLAYING\033[0m\n");
    Sleep(1500);
    system("cls");
    return 0;
}
