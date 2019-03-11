# AnagramDetection-StringPatternSearch_3490

 * @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * @course CIS*3490: Analysis and Design of Computer Algorithms - A3
 * @version 11/03/2019
 * @file README
 * @brief Analyze and compare efficiency of anagram detection using brute force and presorting (transform-and-conquer) methods. Also, do the same for searching a document for a string pattern using brute force, Horspool's, and Boyer-Moore's algorithmic solution (Analysis and Design of Computer Algorithms course A3)

## Notes & Assumptions

* Assumption: data files passed are valid and have good formatting
* NOTE: the A3 description was not very strict in regards to many things, so if something was NOT explicitly outlined to be required it may not have been implemented. Or if something wasn't specified for how to do something, it may have been done slightly differently due to vagueness.
* NOTE: the A3 guide only recommended to "submit something like...", so I have decided to use this format of README (alternate format can be provided upon request), and I will be submitting a PDF instead of including my anaylsis here (this would be too difficult to use to write all my answers)
* NOTE: Please see my in-code comments for more details
* NOTE: Significant references used have been sourced in my code (if any have been used)

* Assumption: Since it doesn't specify the shift value when a match occurs in Horspool's Algorithm for string searching because it usually is only used to find first occurrence instead of all occurences, I shift by the most possible amount. a) If the first character of the search pattern string does not occur again in the pattern, shift by the full length of the pattern. b) If the first character of the search pattern string occurs in the pattern multiple times, shift by the index of its second occurrence. This same assumption applies to Boyer-Moore Algorithm as well (i.e. I do the same thing when I find a match).
* Assumption: For Question 1 - since an anagram is just a word, input must not contain whitespace
* Assumption: For Question 2 - only allow alphabetical characters [a,z] & [A,Z] to be contained in the input
* NOTE: I haven't restarted my computer in a long time, I also haven't restarted my VM in a long time, and I have lots of stuff runnning in the background. Thus, my execution time may be a little slow, but this shouldn't really affect the ratios during analysis. I restarted it when I wrote the anaylsis PDF, so should be better than here.
* Assumption: since the A3 handout description just says to choose 10 search patterns of different lengths, I will assume that it doesn't matter how many times the search pattern occurs
* NOTE: As there is no explicit explanation given in the A3 handout/description, guide, or marking scheme, I will interpret that "briefly" wrting comparison and analysis for Q2.4 means a simple paragraph analyzing and comparing data trends is sufficient.

## makefile, then Run

My files: README.md, analysis.pdf, makefile, a3header.h, main.c, P11.c, P12.c, P21.c, P22.c, P23.c, data_4.txt, and data_5.txt

_NOTE: make sure a bin folder exists before compiling using "make"_
To compile: type "make" --all *.o files and the executable file "run" will be located in a bin folder

## main.c

Usage: ./bin/run

> You will see a menu come up, where you can choose which of the 4 questions to run, or exit. For example:

```
1. P11.c - Brute Force Anagram Detection
2. P12.c - Anagram Detection based on Presorting Technique (mergesort)
3. P21.c - Exhaustive Brute Force String Pattern Search
4. P22.c - Horspool's Algorithm (String Pattern Search)
5. P23.c - Boyer-Moore Algorithm (String Pattern Search)
6. Exit
Enter a code (1 – 6) and hit Return
algos/>
```

* NOTE: entering '6' will exit the program
* NOTE: typing bad input will give an error message

### P11.c

Option 1: Brute Force Anagram Detection - Example input, output:

```
algos/> 1
Enter a string key: 231106813

    Detected Anagrams:
    ====================

 801621133,  231106831

Total Anagrams Found = 2 | Brute Force Time = 14 milliseconds
```

### P12.c

Option 2: Anagram Detection based on Presorting Technique (mergesort) - Example input, output:

```
algos/> 2
Enter a string key: 231106813

    Detected Anagrams:
    ====================

 801621133,  231106831

Total Anagrams Found    = 2
Pre-Sorting Time        = 22 milliseconds
Searching Time          = 10 milliseconds
```

### P21.c

Option 3: Exhaustive Brute Force String Pattern Search - Example input, output:

```
algos/> 3
Enter a search pattern: Schofield

Total Occurrences Found     = 3
Total Pattern Shifts        = 3300583
Exhaustive Brute Force Time = 49 milliseconds
```

### P22.c

Option 4: Horspool's Algorithm (String Pattern Search) - Example input, output:

```
algos/> 4
Enter a search pattern: Schofield

Total Occurrences Found     = 3
Total Pattern Shifts        = 451786
Horspool Execution Time     = 130 milliseconds
```

### P23.c

Option 5: Boyer-Moore Algorithm (String Pattern Search) - Example input, output:

```
algos/> 5
Enter a search pattern: Schofield

Total Occurrences Found     = 3
Total Pattern Shifts        = 451786
Boyer-Moore Execution Time  = 118 milliseconds
```
