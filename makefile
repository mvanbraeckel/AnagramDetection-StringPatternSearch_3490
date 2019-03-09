# @author Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
# @course CIS*3490: Analysis and Design of Computer Algorithms - A3
# @version 09/03/2019
# @file makefile
# @brief compiles everything for A3
 
CC = gcc
CFLAGS = -g -Wall -std=c11 -pedantic

all: P11 P12 P21 P22 P23 main

main: P11 P12 P21 P22 P23 main.c a3header.h
	$(CC) $(CFLAGS) -c main.c -o bin/main.o
	$(CC) $(CFLAGS) bin/*.o -o bin/run

P11: P11.c
	$(CC) $(CFLAGS) -c P11.c -o bin/P11.o
P12: P12.c
	$(CC) $(CFLAGS) -c P12.c -o bin/P12.o
P21: P21.c
	$(CC) $(CFLAGS) -c P21.c -o bin/P21.o
P22: P22.c
	$(CC) $(CFLAGS) -c P22.c -o bin/P22.o
P23: P23.c
	$(CC) $(CFLAGS) -c P23.c -o bin/P23.o

git: clean makefile *.c *.h *.txt *.md
	git add makefile
	git add README.md
	git add bin
	git add *.pdf
	git add *.txt
	git add *.h
	git add *.c
	git commit -m "automatic backup via makefile"
	git remote rm origin
	git config credential.helper store
	git config --global credential.helper 'cache --timeout 3600'
	git remote add origin https://github.com/mvanbraeckel/AnagramDetection-StringPatternSearch_3490.git
	git push -u origin master

clean:
	rm -f *.o bin/*