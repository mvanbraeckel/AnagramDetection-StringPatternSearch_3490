/**
 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 09/03/2019
 * @file P21.c
 * @brief A3 Problem 2.1 - a) brute force algorithm to search for a substring pattern in a document
 * NOTE: only the basic 52 upper and lower case letters, and is case-sensitive
 * NOTE: do NOT remove any symbols / characters from the text
 */

#include "a3header.h"

/**
 * Brute force algorithm that searches for a substring pattern match in a document of up to 44049 lines of strings that are read from data_5.txt
 * --> then: prompts user for search pattern (substring), finds all occurences of the pattern, reports total #of occurences found, #of pattern shifts, and run time
 * @param const char* doc -the preread data_5.txt file as one string (w/ \r and \n removed)
 */
void p21(const char* doc) {
    // declare variables
    char pattern[102];
    int matches = 0;
    int shifts = 0;
    bool validInput = false;
    struct timeb t_start, t_end;

    // prompt user for search pattern substring, make sure they enter something valid
    while(!validInput) {
        printf("Enter a search pattern: ");
        fgets(pattern, 102, stdin);
        flushInput(pattern);

        // check input
        if(!isAlphabetical(pattern)) {
            printf("\nError: invalid input - search pattern must only include [A-Z] and [a-z] - please try again\n\n");
        } else {
            validInput = true;
        }
    }

    // search for matches
    printf("\n...searching for matches...\n");
    ftime(&t_start);
    findMatches(doc, pattern, &matches, &shifts);
    ftime(&t_end);

    // calc execution time, then display results
    int t_elapsed = (int)( 1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm) );
    printf("\nTotal Occurences Found\t= %d\nTotal Pattern Shifts\t= %d\nBrute Force Time\t= %d milliseconds\n", matches, shifts, t_elapsed);
}

// ======================================================================

/**
 * Finds all occurences of the search pattern substring in the text document
 * @param const char doc[] -the text being searched as a single string
 * @param char pattern[] -the search pattern key string to be matched
 * @param int *matches -passed-by-reference to count the number of occurences the pattern is found in the text
 * @param int *shifts -passed-by-reference to count the number of pattern shifts that occur while searching the text
 */
void findMatches(const char doc[], char pattern[], int *matches, int *shifts) {
    // declare variables
    int len = strlen(doc);
    int pLen = strlen(pattern);
    *matches = 0;
    *shifts = 0;
    bool isMatch = false;
    int n = 0;

    // do not need to search the last few characters of the text based on length of search pattern
    for(int i = 0; i < len-pLen+1; i++) {
        // reset
        isMatch = false;
        n = 0;

        /*if(strncmp(doc+i, pattern, pLen-1) == 0) {
            printf("match = '");
            for(int j = 0; j < pLen; j++) {
                printf("%c", doc[i+j]);
            }
            printf("'\n");
        }*/

        // search at the current point to see if it's a match
        for(int j = 0; j < pLen; j++) {
            if((doc+i)[j] != pattern[j]) {
                break;
            } else if(j == pLen-1) {
                isMatch = true;
            }
            n++;
        }
        // check for match and shift pattern appropriately
        if(isMatch) {
            (*matches)++;
            i += pLen-1;
        } else {
            i += n;
        }
        (*shifts)++;
    }

}
