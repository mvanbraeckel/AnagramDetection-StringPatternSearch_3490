/**
 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 10/03/2019
 * @file P23.c
 * @brief A3 Problem 2.3 - c) Boyer-Moore algorithm to search for a substring pattern in a document
 * NOTE: only the basic 52 upper and lower case letters, and is case-sensitive
 * NOTE: do NOT remove any symbols / characters from the text
 */

#include "a3header.h"

/**
 * Boyer-Moore algorithm that searches for a substring pattern match in a document of up to 44049 lines of strings that are read from data_5.txt
 * --> prompt user for search pattern (substring), find all Occurrences of the pattern, report total #of Occurrences found, #of pattern shifts, and run time
 */
void p23() {
    // declare variables
    const char* doc = NULL;
    char pattern[102];
    int matches = 0;
    int shifts = 0;
    bool validInput = false;
    struct timeb t_start, t_end;

    // read in the data
    doc = readDocument("data_5.txt");

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
    ftime(&t_start);
    boyerMoore(doc, pattern, &matches, &shifts);
    ftime(&t_end);

    // calc execution time, then display results
    int t_elapsed = (int)( 1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm) );
    printf("\nTotal Occurrences Found\t\t= %d\nTotal Pattern Shifts\t\t= %d\nBoyer-Moore Execution Time\t= %d milliseconds\n", matches, shifts, t_elapsed);

    // free all created strings
    free((char*)doc);
}

// ======================================================================

/**
 * Boyer-Moore Algorithm - Finds all occurrences of the search pattern substring in the text document
 * @param const char doc[] -the text being searched as a single string
 * @param char pattern[] -the search pattern key string to be matched
 * @param int *matches -passed-by-reference to count the number of occurrences the pattern is found in the text
 * @param int *shifts -passed-by-reference to count the number of pattern shifts that occur while searching the text
 */
void boyerMoore(const char doc[], char pattern[], int *matches, int *shifts) {
    // declare variables
    int len = strlen(doc);
    int pLen = strlen(pattern);
    char table[52][2]; // letter (as char)(lower, then upper), shift value (as int)
    int suff[pLen];
    *matches = 0;
    *shifts = 0;
    bool isMatch = true;
    bool suffixMatch = true;
    int shiftVal = pLen;
    
    // ********************************************** creating bad-symbol shift table **********************************************
    // init bad-symbol shift table ([a-zA-Z] and default bad-symbol shift val as pattern length)
    for(int i = 0; i < 26; i++) {
        table[i][0] = 'a'+i;
        table[i+26][0] = 'A'+i;
        table[i][1] = table[i+26][1] = pLen;
    }
    // fill bad-symbol shift table (length - index - 1)
    for(int i = 0; i < pLen-1; i++) {
        // check its case first
        if(islower(pattern[i])) {
            table[pattern[i]-'a'][1] = pLen-i-1;
        } else {
            table[pattern[i]-'A'+26][1] = pLen-i-1;
        }
    }
    // calculate bad-symbol shift val for if a match is found
    int matchShiftVal = pLen;
    if(pLen > 1) {
        char firstChar = pattern[0];
        for(int i = 1; i < pLen; i++) {
            if(pattern[i] == firstChar) {
                matchShiftVal = i;
                break;
            }
        }
    }

    /*// prints the bad-symbol shift table
    for(int i = 0; i < 52; i++) {
        printf(" %c=%d", table[i][0], table[i][1]);
    }
    printf("\nmatchShiftVal = %d\n", matchShiftVal);*/

    // ********************************************** creating good-suffix shift table **********************************************
    /* fill good-suffix shift table (k=#of matches, is the index --init 0th index as 1)
     * good-suffix shift val is the distance between the suffix and prefix, otherwise pattern length
     * where the prefix is the longest prefix < k that matches suffix of same size */
    suff[0] = 1;
    for(int i = 1; i < pLen; i++) { // loops through good-suffix table
        // start at end of pattern and try i chars to find the right-most second suffix occurence with a different preceding char
        char precedingChar = pattern[pLen-1-i];
        // loops through the pattern in reverse (start one extra char in)
        for(int j = pLen-2; j > -1; j--) {
            suffixMatch = true;
            // number of matched characters trying to be matched (while it goes in reverse)
            for(int k = 0; k < i; k++) {
                // make sure it's still in bounds
                if(j-k < 0) {
                    break;
                } else if(pattern[j-k] != pattern[pLen-1-k]) {
                    suffixMatch = false;
                    break;
                }
            }
            // if it matches, make sure the preceding char is different
            if( suffixMatch && (j-i < 0 || pattern[j-i] != precedingChar) ) {
                suff[i] = (pLen-1) - j; // distance between the suffix and prefix endpoints
                break;
            }
        }
        // if no suffix matches are found, default it to pattern length
        if(!suffixMatch) {
            suff[i] = pLen;
        }
    }

    /*// print good-suffix shift table
    for(int i = 0; i < pLen; i++) {
        printf(" @k=%d->%d", i, suff[i]);
    }
    printf("\n");*/
    
    // ********************************************** searching for matches **********************************************
    // do not need to search the last few characters of the text based on length of search pattern
    for(int i = 0; i < len-pLen+1; i++) {
        isMatch = true; //reset
        // compare pattern in reverse order on current spot in doc
        for(int j = pLen-1; j > -1; j--) {
            // upon first mis-match, look up the bad-symbol shift val for the doc's corresponding char next to the pattern's char using bad-symbol shift table
            // and also look up what the good-suffix shift value in the good suffix table is (d2)
            if(doc[i+j] != pattern[j]) {
                isMatch = false;
                // the shift value calculation is: max(d1, d2) --where d1 is: max(<bad-symbol table shift val> - <#of char matches>, 1)
                int k = pLen-1-j;
                shiftVal = max( max(getBadShiftVal(table, doc[i+j], pLen) - k, 1), suff[k] );
                break;
            }
        }
        // shift by the appropriate amount (account that for loop will +1 afterwards)
        if(!isMatch) {
            i += shiftVal-1;
        } else {
            // SEE ASSUMPTION: if it was a complete match, shift by length if first char only occurs once in pattern, otherwise shift by the index value of its second occurrence
            (*matches)++;
            i += matchShiftVal-1;
        }
        (*shifts)++;
    }
    (*shifts)--; //account for it iterating an extra time but not making a check in the last iteration of the loop
}