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
 * --> prompts user for string, finds all anagrams (excluding given string), displays anagrams, report total #of anagrams found and run time (search time)
 */
void p11() {
    // declare variables

    /*int arr[50000];
    struct timeb t_start, t_end;
    
    // read in the data
    read_ints("data_1.txt", arr);
    int size = sizeof(arr)/sizeof(int);
    
    // count #of inversions, also track time
    printf("\n...counting inversions...\n");
    ftime(&t_start);
    int count = selection_count(arr, size);
    ftime(&t_end);

    // calc execution time, then display results
    int t_elapsed = (int)( 1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm) );
    printf("Inversion Count = %d | Brute Force Time = %d milliseconds\n", count, t_elapsed);*/

    printf("\tI am p11\n");
}

// ======================================================================
