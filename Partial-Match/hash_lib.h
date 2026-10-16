#ifndef HASHCLASS_H
#define HASHCLASS_H

#include "lib.h"

struct Node
{
    long long int fragmentLocation;
    Node *nextNode;
};

class hashClass
{
    public:
        Node **array;
        long long int capacity;

        hashClass(long long int initcapacity);
        ~hashClass();
        long long int populateHash(char* genome, long long int arraySize, int seedSize);
        unsigned long long int radix(char *fragment, int fragLen);
        void insert(long long int location, long long int index);
        bool search(uint8_t **matrix, char *fragment, char* genome, long long int index, int seedSize, int offset, char *query);
        bool kmer(uint8_t **matrix, char *query, char* genome, int seedSize);
};

#endif