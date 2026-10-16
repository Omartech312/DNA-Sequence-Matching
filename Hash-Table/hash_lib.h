#ifndef HASHCLASS_H
#define HASHCLASS_H

#include "lib.h"

struct Node
{
    char *fragment;
    Node *nextNode;
};

class hashClass
{
    public:
        Node **array;
        int size;
        int capacity;
        int collisions;

        hashClass(int initcapacity);
        ~hashClass();
        bool readQueries(const char* filename);
        unsigned long long int radix(char *fragment, int fragLen);
        void insert(char *fragment,int index);
        bool search(char *fragment);
        int resizing(char *filename);
        void dupInsertion(char *fragment, int index);
};

#endif