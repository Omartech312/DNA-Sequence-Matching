#ifndef LLCLASS_H
#define LLCLASS_H

#include "lib.h"

struct Node
{
    char *fragment;
    Node *nextNode;
};

class llClass
{
    public:
        Node *headPtr;
        Node *tailPtr;
        long long int queryNum;

        llClass();
        ~llClass();
            
        bool readQueries(const char* filename);
        void sort();
        bool search(const char *sequence);
        bool binarySearch(const char *sequence, Node* quarter, Node* half, Node* threeQuarter);
        void sortTime(const int numElements);

};

#endif