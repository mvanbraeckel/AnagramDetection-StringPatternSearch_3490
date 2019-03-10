# AnagramDetection-StringPatternSearch_3490
Analyze and compare efficiency of anagram detection using brute force and presorting (transform-and-conquer) methods. Also, do the same for searching a document for string pattern using brute force, Horspool's, and Boyer-Moore's algorithmic solution (Analysis and Design of Computer Algorithms course A3)

NOTE: I removed CR '\r' and LF '\n' characters from the data_5.txt file when reading it into memory because I assumed that we should not be checking against these characters as it would intergere with the number of pattern shifts. I also only read this file once when the program is initially started up because it takes ~20 seconds to read. Also, I can read it in 2-5 seconds, but that gives valgrind memory errors due to strcpy dest and src overlapping and messing it up, so instead I have to use a temp and 2 strcpy calls. If I don't remove CR and LF characters, I can read it in under 20 milliseconds. Nevermind -- I found out that we aren't supposed to remove any characters/symbold from the text file, so I don't do this anymore. But I still read in the data at the start.

Schofield = 3
lifelonglove = 1
facultysupervising = 1
BarB = 3
Bellbrae = 3
DowneyWest = 1
CanadaDepartment = 1
VeterinaryCollege = 1
WWII = 1
Lagerquist = 3
Lemieux = 2
RSPCA = 1
ardon = 5
Britton = 3
planninga = 1
tongue = 1
Casselman = 1
Hearn = 2