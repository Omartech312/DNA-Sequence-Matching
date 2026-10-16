#ifndef LIB_H
#define LIB_H

//header files
#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>
#include <fstream>
#include <chrono>
#include <math.h>
#include <cstring>
#include <ctime>

//namespaces
using namespace std;

//constants
#define STD_STR_LEN 64
#define LARGE_STR_LEN 256
#define SEQUENCE 32
#define MILLION 1000000
#define BASE 4
#define ELEVEN 11
#define ERROR_RATE 95
#define NULL_CHAR '\0'
#define MATCH 2
#define MISMATCH -1
#define GAP -3
#define LOOPS 2000
#define FULL_MATCH 64
#define ONE_MISMATCH 61
#define ONE_GAP 59
#define SEED_SIZE 16

//enums
enum Options { SIZE, READ };
enum Genome { A, C, G, T };

// Function Prototypes
long long int fileOptions(char *filename, Options option, char *genomeArray);
int compareString( const char *oneStr, const char *otherStr, int length);
int getStringLength(const char *testStr);
long long int countQueries(char *filename);
uint8_t** declareMatrix(int rows, long long int cols);
void freeMatrix(uint8_t **matrix, int rows);
void introduceError(char *sequence, int errorRate);
bool smithWaterman(uint8_t **matrix, char *genomeArray, char *queryArray, long long int genomeLength);




#endif
