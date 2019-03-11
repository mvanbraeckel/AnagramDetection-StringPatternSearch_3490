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
int isAlphabetical(char *input);


void readStrings(char* filename, char* arr[30000]);
int anagramSearch(const char* arr[], int size, char* anagrams[], char key[]);
bool isAnagram(char keyCopy[], const char otherStr[]);

int charCompar(const void *a, const void *b);
int strCompar(const void *a, const void *b);
void mergesort(char arr[], char temp[], int left, int right);
void merge(char arr[], char temp[], int left, int mid, int right);


const char* readDocument(char* filename);
void findMatches(const char doc[], char pattern[], int *matches, int *shifts);
void horspool(const char doc[], char pattern[], int *matches, int *shifts);
int getBadShiftVal(char table[52][2], char c, int pLen);
void boyerMoore(const char doc[], char pattern[], int *matches, int *shifts);

#endif