/**
 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 09/03/2019
 * @file P12.c
 * @brief A3 Problem 1.2 - b) presort-based, transform-and-conquer algorithm to detect anagrams
 */

#include "a3header.h"

/**
 * Transform-and-conquer algorithm that counts number of anagrams in up to 30000 strings read from data_4.txt using a presort technique
 * --> prompts user for string, finds all anagrams (excluding given string), displays anagrams, report total #of anagrams found, run time (sort time separate from search time)
 */
void p12() {
    // declare variables
    
    /*int arr[50000];
    int count = 0;
    struct timeb t_start, t_end;
    
    // read in the data
    read_ints("data_1.txt", arr);
    int size = sizeof(arr)/sizeof(int);
    int temp[size];
    
    // count #of inversions, also track time
    ftime(&t_start);
    mergesort(arr, temp, 0, size-1, &count);
    ftime(&t_end);

    // calc execution time, then display results
    int t_elapsed = (int)( 1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm) );
    printf("\nInversion Count = %d | Recursive Divide-and-Conquer Time = %d milliseconds\n", count, t_elapsed);*/
}

// ======================================================================

