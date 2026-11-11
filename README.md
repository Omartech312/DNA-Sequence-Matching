# DNA-Sequence-Matching
In this project, multiple approaches are used to find queries in long genomic sequences, with each part building upon the previous one.

## Extraction-Validation
Reads characters from a file and does the following:
- Counts the total number of characters
- Replaces illegal characters with 'A'
- Creates a 1D array with the characters to act as the Genome (G)

## Searching 32-character Queries in Genome (Brute-Force)
Stores 32-character queries in a 2D array or a linked list
- Takes 32 Characters at a time from the genome and traverses one index/node at a time, attempting to find a perfect match
- Option (1A) sorts a 2D array of queries alphabetically to allow Binary Search
- Option (2A) sorts a Linked List to allow "Binary Search," essentially having 4 pointers: start, 1/4, 1/2, 3/4 of the linked list, which cuts a linear search of O(n) to O(n/4).
