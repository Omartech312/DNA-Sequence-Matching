# DNA-Sequence-Matching
In this project, multiple approaches are used to find queries in long genomic sequences, with each part building upon the previous one.

n = 32-character query
N = Number of Queries to find in the genome
G = Size of Genome

## Extraction-Validation
Reads characters from a file and does the following:
- Counts the total number of characters
- Replaces illegal characters with 'A'
- Creates a 1D array with the characters to act as the Genome (G)

## Searching 32-character Queries in Genome (Brute-Force)
Stores 32-character queries in a 2D array or a linked list
- Takes 32 Characters at a time from the genome and traverses one index/node at a time, attempting to find a perfect match
- Option (1A) sorts a 2D array of queries alphabetically to allow Binary Search
- Option (2A) sorts a Linked List to allow "Binary Search," essentially having 4 pointers: start, 1/4, 1/2, and 3/4 of the linked list, which cuts a linear search of O(n) to O(n/4).

## Hash Table (Efficient Search for Perfect Match)
Splits the genome into 32-character segments and stores them in a Hash Table using Radix to generate an index.
- Selecting each 32-character query from a 2D array, its radix is calculated; using that number as hash[index] lies the head of a Linked List; if traversed, it will either find a perfect match or the query is simply not in the Genome.
- Access time O(1), Hash Table Creation (G * n) and query search (n * N)

## Partial-Match
### Smith-Waterman (Option 1)
- This approach creates a 2D array with dimensions n x G, attempting to find partial matches between the queries and the genome.
- Allows partial matching, but it's inefficient, as it requires computing Smith-Waterman for each Query against the entire Genome.
