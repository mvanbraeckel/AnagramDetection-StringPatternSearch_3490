/**
 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 09/03/2019
 * @file P11.c
 * @brief A3 Problem 1.1 - a) brute force algorithm for anagram detection
 */

#include "a3header.h"

/**
 * Brute force algorithm that finds all anagrams of a user-given string in up to 30000 strings read from data_4.txt
 * --> then: prompt user for string, find all anagrams (excluding given string), display anagrams, report total #of anagrams found and run time (search time)
 */
void p11() {
    // declare variables
    char* arr[30000];
    char key[52];
    int size = 0;
    bool validInput = false;
    struct timeb t_start, t_end;
    
    // read in the data
    read_strings("data_4.txt", arr, &size);
    char* anagrams[size];
    
    // prompt user for key string to search for anagrams, make sure they enter something valid
    while(!validInput) {
        printf("Enter a string key: ");
        fgets(key, 52, stdin);
        flushInput(key);

        // check input
        if(isWhitespace(key) || containsWhitespace(key)) {
            printf("\nError: invalid input - search key for anagram detection cannot contain whitespace - please try again\n\n");
        } else {
            validInput = true;
        }
    }

    // search for anagrams
    printf("\n...searching for anagrams...\n");
    ftime(&t_start);
    int count = anagramSearch((const char**)arr, size, anagrams, key);
    ftime(&t_end);

    // display anagrams
    printf("\n\tDetected Anagrams:\n\t====================\n");
    for(int i = 0; i < count; i++) {
        if(i != 0) {
            printf(", ");
        }
        if(i % 5 == 0) {
            printf("\n");
        }
        printf("%10s", anagrams[i]);
        free(anagrams[i]); //don't need anymore
    }
    printf("\n");

    // calc execution time, then display results
    int t_elapsed = (int)( 1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm) );
    printf("\nTotal Anagrams Found = %d | Brute Force Time = %d milliseconds\n", count, t_elapsed);

    // free all created strings
    for(int i = 0; i < size; i++) {
        free(arr[i]);
    }
}

// ======================================================================

/**
 * Searches for anagrams in a given array and stores the found ones in another array
 * @param const char* arr[] -the list of strings being searched (do not modify)
 * @param char* anagrams[] -where detected anagrams are stored
 * @param char key[] -the string being used to search for anagrams
 * @return the total number of anagrams found
 */
int anagramSearch(const char* arr[], int size, char* anagrams[], char key[]) {
    // declare variables
    char keyCopy[52];
    int count = 0;

    // check if each string in the array is an anagram
    for(int i = 0; i < size; i++) {
        // copy the search key string to manipulate it safely
        strcpy(keyCopy, key);
        // check if it's an anagram, store it as a result (after giving some mem)
        if(isAnagram(keyCopy, arr[i])) {
            // allocate mem, then store it
            anagrams[count] = malloc((strlen(arr[i])+1) * sizeof(char));
            strcpy(anagrams[count], arr[i]);
            count++; //accumulate
        }
    }
    return count;
}

/**
 * Brute force algorithm that checks if two strings are anagrams of each another
 * @param char keyCopy[] -copy of the string to check against (can be altered)
 * @param char otherStr[] -the string being checked (must not be altered)
 * @return true if otherStr is an anagram of keyCopy, false if it isn't
 */
bool isAnagram(char keyCopy[], const char otherStr[]) {
    // declare variables
    bool match = false;

    // make sure strings are the same length and they aren't the same string first
    int len = strlen(keyCopy);
    if(len != strlen(otherStr) || strcmp(keyCopy, otherStr) == 0) {
        return false;
    }

    // loop through the otherStr to compare each char one-at-a-time
    for(int i = 0; i < len; i++) {
        match = false; //reset
        // loop through the keyCopy
        for(int j = 0; j < len; j++) {
            // remove char if it's a match (by replacing it w/ '\0'), then stop the iteration
            if(otherStr[i] == keyCopy[j]) {
                match = true;
                keyCopy[j] = '\0';
                break;
            }
        }
        // the char in otherStr was not found in keyCopy
        if(!match) {
            return false;
        }
    }
    return true;
}