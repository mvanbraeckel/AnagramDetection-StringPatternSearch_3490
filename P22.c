/**
 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 09/03/2019
 * @file P22.c
 * @brief A3 Problem 2.2 - b) Horspool's algorithm to search for a substring pattern in a document
 * NOTE: only the basic 52 upper and lower case letters, and is case-sensitive
 * NOTE: do NOT remove any symbols / characters from the text
 */

#include "a3header.h"

/**
 * Horspool's algorithm that searches for a substring pattern match in a document of up to 44049 lines of strings that are read from data_5.txt
 * --> prompt user for search pattern (substring), find all occurences of the pattern, report total #of occurences found, #of pattern shifts, and run time
 */
void p22() {
    // declare variables
    
    /*Point points[30000];
    int count = 0;
    struct timeb t_start, t_end;
    
    // read in the data
    read_points("data_2.txt", points);
    int size = sizeof(points)/sizeof(Point);
    Point hull_set[size];

    // check that min size requirements are met
    if(size < 3) {
        fprintf(stderr, "\nInvalid: Convex hull not possible - must have at least 3 points\n");
        return;
    }
    
    // determine bounding convex hull set
    ftime(&t_start);
    // Find max and min point (wrt to x-coord)
    int min_x = 0;
    int max_x = 0;
    for(int i = 1; i < size; i++) {
        if( points[i].x < points[min_x].x ) min_x = i;
        if( points[i].x > points[max_x].x ) max_x = i;
    }

    // Recursively find convex hull points on either side of line PMIN-PMAX
    quick_hull(points, hull_set, size, points[min_x], points[max_x],  1, &count);
    quick_hull(points, hull_set, size, points[min_x], points[max_x], -1, &count);
    ftime(&t_end);

    // selection sort by x-coord so it's a little easier to read
    for(int i = 0; i < count-1; i++) {
        for(int j = i+1; j < count; j++) {
            if(hull_set[i].x > hull_set[j].x) {
                Point temp = hull_set[i];
                hull_set[i] = hull_set[j];
                hull_set[j] = temp;
            }
        }
    }

    // calc execution time, then display results
    int t_elapsed = (int)( 1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm) );

    printf("\n\tMinimum Bounding Convex Hull Set:\n\t=================================\n");
    for(int i = 0; i < count; i++) {
        printf("\tPoint %03d: (%8.1lf, %8.1lf)\n", i+1, hull_set[i].x, hull_set[i].y);
    }
    printf("Recursive Divide-and-Conquer Quickhull Algorithm Execution Time = %d milliseconds\n", t_elapsed);*/

    printf("\tI am p22\n");
}

// ======================================================================
