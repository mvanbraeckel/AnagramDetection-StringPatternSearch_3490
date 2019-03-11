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
    int count = 0;
    bool validInput = false;
    struct timeb t_startSort, t_endSort, t_startSearch, t_endSearch;
    
    // read in the data
    readStrings("data_4.txt", arr);
    int size = sizeof(arr) / sizeof(char*);
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

    // calculate execution time separately while sorting and searching
    int len = strlen(key);
    char copyStr[52], temp[52];
    int t_elapsedSort = 0;
    int t_elapsedSearch = 0;
    
    // track time for sorting the key
    strcpy(keySorted, key);
    ftime(&t_startSort);
    mergesort(keySorted, temp, 0, len-1);//qsort(keySorted, strlen(keySorted), sizeof(char), *charCompar);
    ftime(&t_endSort);
    t_elapsedSort += (int)( 1000.0*(t_endSort.time - t_startSort.time) + (t_endSort.millitm - t_startSort.millitm) );
    
    // search for anagrams - since sorted, anagrams are equal strings (make sure it's not the same originally though)
    ftime(&t_startSearch);
    for(int i = 0; i < size; i++) {
        int length = strlen(arr[i]);
        if(len == length) {
            // pause search time
            ftime(&t_endSearch);
            t_elapsedSearch += (int)( 1000.0*(t_endSearch.time - t_startSearch.time) + (t_endSearch.millitm - t_startSearch.millitm) );

            // track time for sorting
            strcpy(copyStr, arr[i]);
            ftime(&t_startSort);
            mergesort(copyStr, temp, 0, length-1);//qsort(copyStr, length, sizeof(char), *charCompar);
            ftime(&t_endSort);
            t_elapsedSort += (int)( 1000.0*(t_endSort.time - t_startSort.time) + (t_endSort.millitm - t_startSort.millitm) );

            // resume search time
            ftime(&t_startSearch);
            if(strcmp(keySorted, copyStr) == 0 && strcmp(key, arr[i]) != 0) {
                // allocate mem, then store original in it
                anagrams[count] = malloc((length+1) * sizeof(char));
                strcpy(anagrams[count], arr[i]);
                count++; //accumulate
            }
        }
    }
    ftime(&t_endSearch);
    t_elapsedSearch += (int)( 1000.0*(t_endSearch.time - t_startSearch.time) + (t_endSearch.millitm - t_startSearch.millitm) );

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

    // display results
    printf("\nTotal Anagrams Found\t= %d\nPre-Sorting Time\t= %d milliseconds\nSearching Time\t\t= %d milliseconds\n", count, t_elapsedSort, t_elapsedSearch);

    // free all created strings
    for(int i = 0; i < size; i++) {
        free(arr[i]);
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
/**
 * Comparator function for QSORT - compares two strings (used for sorting array of strings ascending order)
 * @param a -the first string
 * @param b -the second string
 */
int strCompar(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}
// qsort({arr}, sizeof({arr}) / sizeof({arr datatype}), sizeof(char*), *strCompar);

/**
 * Mergesort a string (ascending order)
 * @param char arr[] -the string to be sorted
 * @param char temp[] -the temp copy of the string to hold things during merging
 * @param int left -the left index (begin)
 * @param int right -the right index (end)
 */
void mergesort(char arr[], char temp[], int left, int right) {
    if(left < right) {
        // divide array into halves, then mergesort each separately, then merge it back together
        int mid = left + (right - left) / 2; // = (l+r)/2, avoids overflow for large numbers

        // total #of inversions = left-part + right-part + merging-part
        mergesort(arr, temp, left, mid);
        mergesort(arr, temp, mid+1, right);
        merge(arr, temp, left, mid+1, right);
    }
}

/**
 * Does the re-merging of two sorted strings for mergesort (ascending order)
 * @param char arr[] -the string to be sorted
 * @param int temp[] -the temp copy of the string to hold things during merging
 * @param int left -the left index (begin)
 * @param int mid -the middle index (half)
 * @param int right -the right index (end)
 */
void merge(char arr[], char temp[], int left, int mid, int right) {
    // Initial indices of left, right, and merged subarrays
    int i = left;
    int j = mid;
    int k = left;

    // create sorted array using both halves
    while( i <= mid-1 && j <= right ) {
        if(arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy any remaining elements of left and right arrays to temp, then overwrite original with merged
    while(i <= mid-1) temp[k++] = arr[i++];
    while(j <= right) temp[k++] = arr[j++];
    for(i = left; i <= right; i++) arr[i] = temp[i];
}
