#ifndef ARRAY_LIB_H
#define ARRAY_LIB_H

#include "lib.h"

class arrayClass
{
    public:
        char **array;
        long long int queryNum;

        arrayClass(long long int numElements);
        ~arrayClass();
        
        bool readQueries(const char* filename);
        void sort();
        bool search(const char *sequence);
        bool binarySearch(const char *sequence);
        void sortTime(const int numElements);

};

#endif