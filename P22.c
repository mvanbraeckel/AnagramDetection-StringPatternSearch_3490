/**
 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 10/03/2019
 * @file P22.c
 * @brief A3 Problem 2.2 - b) Horspool's algorithm to search for a substring pattern in a document
 * NOTE: only the basic 52 upper and lower case letters, and is case-sensitive
 * NOTE: do NOT remove any symbols / characters from the text
 */

#include "a3header.h"

/**
 * Horspool's algorithm that searches for a substring pattern match in a document of up to 44049 lines of strings that are read from data_5.txt
 * --> prompt user for search pattern (substring), find all occurences of the pattern, report total #of occurences found, #of pattern shifts, and run time
 * @param const char* doc -the preread data_5.txt file as one string (w/ \r and \n removed)
 */
void p22(const char* doc) {
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
    int pLen = strlen(pattern);
    
    // search for matches
    printf("\n...searching for matches... (not using horspool's yet)\n");
    ftime(&t_start);
    horspool(doc, pattern, &matches, &shifts);
    ftime(&t_end);

    // calc execution time, then display results
    int t_elapsed = (int)( 1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm) );
    printf("\nTotal Occurences Found\t= %d\nTotal Pattern Shifts\t= %d\nBrute Force Time\t= %d milliseconds\n", matches, shifts, t_elapsed);

    printf("\tI am p22\n");
}

// ======================================================================

/**
 * Horspool's Algorithm - Finds all occurences of the search pattern substring in the text document
 * @param const char doc[] -the text being searched as a single string
 * @param char pattern[] -the search pattern key string to be matched
 * @param int *matches -passed-by-reference to count the number of occurences the pattern is found in the text
 * @param int *shifts -passed-by-reference to count the number of pattern shifts that occur while searching the text
 */
void horspool(const char doc[], char pattern[], int *matches, int *shifts) {
    // declare variables
    char table[52][2]; // letter (as char)(lower, then upper), shift value (as int)
    int len = strlen(doc);
    int pLen = strlen(pattern);
    *matches = 0;
    *shifts = 0;
    bool isMatch = false;
    int n = 0;

    // init shift table ([a-zA-Z] and default shift val as pattern length)
    for(int i = 0; i < 26; i++) {
        table[i][0] = 'a'+i;
        table[i+26][0] = 'A'+i;
        table[i][1] = table[i+26][1] = pLen;
    }
    // fill shift table (length - index - 1)
    for(int i = 0; i < pLen-1; i++) {
        // check its case first
        if(islower(pattern[i])) {
            table[pattern[i]-'a'][1] = pLen-i-1;
        } else {
            table[pattern[i]-'A'+26][1] = pLen-i-1;
        }
    }

    /*for(int i = 0; i < 52; i++) {
        printf(" %c=%d", table[i][0], table[i][1]);
    }*/

    // do not need to search the last few characters of the text based on length of search pattern
    for(int i = 0; i < len-pLen+1; i++) {
        
        // compare pattern in reverse order on current spot in doc

        // upon first mis-match, look up that doc's char of the mis-match in the table and shift by its val

        // if it was a complete match, shift by 1
        
        /*// reset
        isMatch = false;
        n = 0;

        if(strncmp(doc+i, pattern, pLen) == 0) {
            (*matches)++;
        }

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
        (*shifts)++;*/
    }
}
