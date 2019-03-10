/**
 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 09/03/2019
 * @file main.c
 * @brief A3 menu to run each different program to solve a program
 */

// ====================================== INCLUDES ======================================
#include "a3header.h"


int main(int argc, char* argv[]) {

    // declare variables
    char menu_input[3];

    // infinite menu loop, only ending program with '7' as input
    while(1) {
        printf("\n1. P11.c - Brute Force Anagram Detection\n" \
                "2. P12.c - Anagram Detection based on Presorting Technique (qsort)\n" \
                "3. P21.c - Brute Force String Pattern Search\n" \
                "4. P22.c - Horspool's Algorithm (String Pattern Search)\n" \
                "5. P23.c - Boyer-Moore Algorithm (String Pattern Search)\n" \
                "6. Exit\n" \
                "Enter a code (1 – 6) and hit Return\n" \
                "algos/> ");
        fgets(menu_input, 3, stdin);    //only need the first character of input for menu option
        flushInput(menu_input);

        // checks user input
        if(strlen(menu_input) > 1) {
            // display error msg inputting more than just the number option
            printf("\nError: invald input - You must choose one of the menu options by number: [1,6]\nPlease try again\n");

        } else if(menu_input[0] == '1') {         // ================================= 1 =================================
            p11();

        } else if(menu_input[0] == '2') {         // ================================= 2 =================================
            p12();

        } else if(menu_input[0] == '3') {         // ================================= 3 =================================
            p21();

        } else if(menu_input[0] == '4') {         // ================================= 4 =================================
            p22();

        } else if(menu_input[0] == '5') {         // ================================= 5 =================================
            p23();

        } else if(menu_input[0] == '6') {         // ================================= 6 =================================
            printf("\nGood bye!\n");    // display closing msg
            return 0;

        } else {                                  // =============================== ELSE ================================
            // display error msg for bad input
            printf("\nError: invald input - You must choose one of the menu options by number: [1,7]\nPlease try again\n");
        }
    } // end menu loop
}

// ======================================== HELPERS ========================================

/**
 * Flushes all leftover data in the stream
 * @param char* input -the string that was just read from stdin
 */
void flushInput(char* input) {
    // if the '\n' is NOT found in the word itself, flush the stream (null-terminate the input regardless)
    if(strchr(input, '\n') == NULL) {
        while ((getchar()) != '\n');
        input[strlen(input)] = '\0';
    } else {
        input[strlen(input)-1] = '\0';
    }
}

/**
 * Checks if the string is pure whitespace
 * @param char *input -the string to be checked
 * @return 1 if the string only contains whitespace characters
 */
int isWhitespace(char *input) {
    for(int i = 0; i < strlen(input); i++) {
        if(!isspace(input[i])) {
            return 0; //contained a non-whitespace character
        }
    }
    return 1;
}

/**
 * Checks if the string contains any whitespace
 * @param char *input -the string to be checked
 * @return 1 if the string contains at least one whitespace character
 */
int containsWhitespace(char *input) {
    for(int i = 0; i < strlen(input); i++) {
        if(isspace(input[i])) {
            return 1; //contained a whitespace character
        }
    }
    return 0;
}


/**
 * Reads in up to 30000 strings from a file
 * @param char* filename -the name of the text file being read
 * @param char* arr[] -the string array of 30,000 to be loaded
 * @param int* n -passed-by-reference to count the number of strings read
 */
void read_strings(char* filename, char* arr[30000], int *n) {
    char buffer[51] = ""; //50 char max
    *n = 0;

    FILE *fp = fopen(filename, "r");
    // checks if fopen messed up
    if(fp == NULL) {
        fprintf(stderr, "ERROR: File could not be opened\n");

    } else {
        // read one string at a time until the end of the file (or max reached)
        int i = 0;
        while(!feof(fp) && i < 30000) {
            // read a word, allocate mem, copy over data, null terminate (just in case)
            fscanf(fp, " %s ", buffer);
            arr[i] = malloc((strlen(buffer)+1) * sizeof(char));
            strcpy(arr[i], buffer);
            arr[i][strlen(arr[i])] = '\0';
            i++;
        }
        *n = i;
    }
    fclose(fp);
}
