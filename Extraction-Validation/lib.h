//header files
#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>
#include <fstream>

using namespace std;

//constants
#define STD_STR_LEN 64
#define LARGE_STR_LEN 256

enum Options { SIZE, COUNT, ILLEGAL, REPLACE };

//Struct 
struct Node
{
    //Necessary data
    Node *next;
};

// Function Prototypes
long long int fileOptions(char *filename, Options option, char replaceChar, char *genomeArray);
bool replaceValid(char c, char replaceChar);



