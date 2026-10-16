#ifndef LIB_H
#define LIB_H

//header files
#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>
#include <fstream>
#include <chrono>


using namespace std;

//constants
#define STD_STR_LEN 64
#define LARGE_STR_LEN 256
#define SEQUENCE 32


#define NULL_CHAR '\0'

enum Options { SIZE, READ };
// Function Prototypes
long long int fileOptions(char *filename, Options option, char *genomeArray);
int compareString( const char *oneStr, const char *otherStr);
int getStringLength(const char *testStr);
long long int countQueries(char *filename);

#endif