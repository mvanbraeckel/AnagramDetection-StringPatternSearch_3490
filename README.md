# AnagramDetection-StringPatternSearch_3490

Analyze and compare efficiency of anagram detection using brute force and presorting (transform-and-conquer) methods. Also, do the same for searching a document for string pattern using brute force, Horspool's, and Boyer-Moore's algorithmic solution (Analysis and Design of Computer Algorithms course A3)

## NOTES & ASSUMPTIONS

Assumption: Since it doesn't specify the shift value when a match occurs in Horspool's Algorithm for string searching because it usually is only used to find first occurrence instead of all occurences, I shift by the most possible amount. a) If the first character of the search pattern string does not occur again in the pattern, shift by the full length of the pattern. b) If the first character of the search pattern string occurs in the pattern multiple times, shift by the index of its second occurrence.

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