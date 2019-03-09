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
 * --> then: prompts user for string, finds all anagrams (excluding given string), displays anagrams, report total #of anagrams found and run time (search time)
 */
void p11() {
    // declare variables
    char* arr[30000];
    //struct timeb t_start, t_end;
    int size = 0;
    char word[52];
    bool validInput = false;
    
    // read in the data
    read_strings("data_4.txt", arr, &size);

    /*for(int i = 0; i < size; i++) {
        if(i % 5 == 0) {
            printf("\n");
        }
        printf("%10s ", arr[i]);
    }
    printf("\n");*/

    // prompt user for key string to search for anagrams, make sure they enter something valid
    while(!validInput) {
        printf("Enter a string key: ");
        fgets(word, 52, stdin);
        flushInput(word);

        // check input
        if(isWhitespace(word) || containsWhitespace(word)) {
            printf("\nError: invalid input - search key for anagram detection cannot contain whitespace - please try again\n\n");
        } else {
            validInput = true;
        }
    }
    
    // count #of inversions, also track time
    /*printf("\n...counting inversions...\n");
    ftime(&t_start);
    int count = selection_count(arr, size);
    time(&t_end);

    // calc execution time, then display results
    int t_elapsed = (int)( 1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm) );
    printf("Inversion Count = %d | Brute Force Time = %d milliseconds\n", count, t_elapsed);*/

    printf("\tI am p11\n");
}

// ======================================================================
