/**
 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 09/03/2019
 * @file P12.c
 * @brief A3 Problem 1.2 - b) presort-based, transform-and-conquer algorithm to detect anagrams
 * NOTE: using qsort function from stdlib.h to presort
 */

#include "a3header.h"

/**
 * Transform-and-conquer algorithm that counts number of anagrams in up to 30000 strings read from data_4.txt using a presort technique
 * --> then: prompts user for string, finds all anagrams (excluding given string), displays anagrams, report total #of anagrams found, run time (sort time separate from search time)
 */
void p12() {
    // declare variables
    char* arr[30000];
    char key[52];
    char keySorted[52];
    int size = 0;
    int count = 0;
    bool validInput = false;
    struct timeb t_startSort, t_endSort, t_startSearch, t_endSearch;
    
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

    // pre-sort every string first (key, and all in the array): sort copies of the original
    printf("\n...presorting the strings via qsort...\n");
    ftime(&t_startSort);

    char* arrSorted[size];
    strcpy(keySorted, key);
    qsort(keySorted, strlen(keySorted), sizeof(char), charCompar);
    // allocate mem, then store original in it, then sort it
    for(int i = 0; i < size; i++) {
        arrSorted[i] = malloc((strlen(arr[i])+1) * sizeof(char));
        strcpy(arrSorted[i], arr[i]);
        qsort(arrSorted[i], strlen(arrSorted[i]), sizeof(char), charCompar);
    }

    ftime(&t_endSort);

    // search for anagrams
    printf("\n...searching for anagrams...\n");
    ftime(&t_startSearch);

    int len = strlen(key);
    // since sorted, anagrams are equal strings (make sure it's not the same originally though)
    for(int i = 0; i < size; i++) {
        if(len == strlen(arr[i]) && strcmp(key, arr[i]) != 0 && strcmp(keySorted, arrSorted[i]) == 0) {
            // allocate mem, then store original in it
            anagrams[count] = malloc((strlen(arr[i])+1) * sizeof(char));
            strcpy(anagrams[count], arr[i]);
            count++; //accumulate
        }
    }

    ftime(&t_endSearch);

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
    }
    printf("\n");

    // calc execution time, then display results
    int t_elapsedSort = (int)( 1000.0*(t_endSort.time - t_startSort.time) + (t_endSort.millitm - t_startSort.millitm) );
    int t_elapsedSearch = (int)( 1000.0*(t_endSearch.time - t_startSearch.time) + (t_endSearch.millitm - t_startSearch.millitm) );
    printf("\nTotal Anagrams Found\t= %d\nSorting Time\t\t= %d milliseconds\nSearching Time\t\t= %d milliseconds\n", count, t_elapsedSort, t_elapsedSearch);

    // free all created strings
    for(int i = 0; i < size; i++) {
        free(arr[i]);
        free(arrSorted[i]);
    }
    for(int i = 0; i < count; i++) {
        free(anagrams[i]);
    }
}

// ======================================================================

/**
 * Comparator function for QSORT - compares two characters (used for sorting strings ascending order)
 * @param a -the first char
 * @param b -the second char
 */
int charCompar(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
}