/**
 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 09/03/2019
 * @file a3header.h
 * @brief header file for A3
 */

#ifndef A3HEADER_H
#define A3HEADER_H

// ============================== INCLUDES ==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

// ============================== STRUCTS ===============================

// ======================================================================
void p11();
void p12();
void p21();
void p22();
void p23();

// ======================================================================

void flushInput(char *input);
int isWhitespace(char *input);
int containsWhitespace(char *input);

void read_strings(char* filename, char* arr[30000], int *n);

int anagramSearch(const char* arr[], int size, char* anagrams[], char key[]);
bool isAnagram(char keyCopy[], const char otherStr[]);

int charCompar(const void *a, const void *b);

#endif