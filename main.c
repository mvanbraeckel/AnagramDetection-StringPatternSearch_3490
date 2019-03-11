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
                "2. P12.c - Anagram Detection based on Presorting Technique (mergesort)\n" \
                "3. P21.c - Exhaustive Brute Force String Pattern Search\n" \
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

// ======================================= MY HELPERS =======================================

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
    int len = strlen(input);
    for(int i = 0; i < len; i++) {
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
    int len = strlen(input);
    for(int i = 0; i < len; i++) {
        if(isspace(input[i])) {
            return 1; //contained a whitespace character
        }
    }
    return 0;
}

/**
 * Checks if the string is alphabetical (lower and upper case characters only)
 * @param char *input -the string to be checked
 * @return 1 if the string only contains the basic 52 alphabetical characters
 */
int isAlphabetical(char *input) {
    int len = strlen(input);
    if(len == 0) return 0;
    for(int i = 0; i < len; i++) {
        if(!isalpha(input[i])) {
            return 0; //contained a non-alphabetical character
        }
    }
    return 1;
}

/**
 * Determines which two integers is greater
 * @param int a -the first integer
 * @param int b -the second integer
 * @return the larger integer
 */
int max(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

// ======================================== HELPERS ========================================

/**
 * Reads in up to 30000 strings from a file
 * @param char* filename -the name of the text file being read
 * @param char* arr[] -the string array of 30,000 to be loaded
 * @param int* n -passed-by-reference to count the number of strings read
 */
void readStrings(char* filename, char* arr[30000]) {
    char buffer[51] = ""; //50 char max

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
            int bLen = strlen(buffer);
            arr[i] = malloc((bLen+1) * sizeof(char));
            strcpy(arr[i], buffer);
            i++;
        }
    }
    fclose(fp);
}

/**
 * Reads into a single string one word at a time from a file
 * @param char* filename -the name of the text file document being read
 * @return a string containing all words in the file separated by a space
 */
const char* readDocument(char* filename) {
    char* doc = NULL;
    FILE *fp = fopen(filename, "r");
    // checks if fopen messed up
    if(fp == NULL) {
        fprintf(stderr, "ERROR: File could not be opened\n");

    } else {
        // calculate number of chars (using total bytes), then allocate mem
        fseek(fp, 0, SEEK_END);
        int len = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        doc = calloc(len+1, sizeof(char)); //init the string array

        fread(doc, sizeof(char), len, fp); // reads entire file into the array at once
		doc[len] = '\0';
	}
    fclose(fp);
    return (const char*)doc;
}


/**
 * Retrieves the bad-symbol shift value of the given char from the bad-symbol shift table
 * @param char table[][] -the bad-symbol shift table being used
 * @param char c -the character being looked up in the bad-symbol shift table
 * @param int pLen -the length of the search pattern string
 * @return the bad-symbol shift value of the given char
 */
int getBadShiftVal(char table[52][2], char c, int pLen) {
    // make sure it's alphabetical first (start search differently depending on char case)
    if(islower(c)) {
        for(int i = 0; i < 26; i++) {
            if(table[i][0] == c) {
                return table[i][1];
            }
        }
    } else if(isupper(c)) {
        for(int i = 26; i < 52; i++) {
            if(table[i][0] == c) {
                return table[i][1];
            }
        }
    } // else
    return pLen;
}