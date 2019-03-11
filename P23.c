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

    // ********************************************** creating good-suffix table *****************************************
    int pLen = strlen(pattern);

    int suff[pLen];
    bool suffixMatch = true;

    // fill good-suffix shift table (k=#of matches, is the index --init 0th index as 1)
    // good-suffix shift val is the distance between the suffix and prefix, otherwise pattern length
    // where the prefix is the longest prefix < k that matches suffix of same size
    suff[0] = 1;
    for(int i = 1; i < pLen; i++) { // loops through good-suffix table
        // start at end of pattern and try i chars to find the right-most second suffix occurence with a different preceding char
        char precedingChar = pattern[pLen-1-i];
        // loops through the pattern in reverse (start one extra char in)
        for(int j = pLen-2; j >= 0; j--) {
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

    // print good-suffix shift table
    for(int i = 0; i < pLen; i++) {
        printf(" @k=%d->%d", i, suff[i]);
    }
    printf("\n");
    
    // search for matches
    printf("\n...searching for matches...(not doing BM right now)\n");
    ftime(&t_start);
    //horspool(doc, pattern, &matches, &shifts);
    ftime(&t_end);

    // calc execution time, then display results
    int t_elapsed = (int)( 1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm) );
    printf("\nTotal Occurrences Found\t\t= %d\nTotal Pattern Shifts\t\t= %d\nBoyer-Moore Execution Time\t= %d milliseconds\n", matches, shifts, t_elapsed);

    // free all created strings
    free((char*)doc);
}

// ======================================================================
