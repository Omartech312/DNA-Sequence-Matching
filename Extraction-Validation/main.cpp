/*
    AI acknowledgement:
    - I was getting an error when using tolower to which chatGPT suggested adding: (& 0xFF)
    - To ignore the header files I had already noticed the first character being '>', but didn't have a plan 
        for how to ignore them, to which the chatGPT suggested adding continue; I was planning to just leave it
        empty, but the GUR from CS 249 left traumas on my mind.
    - Helped me to properly write the makefile, since its been a while since the last time I wrote one
*/

//header files
#include "lib.h"

//IMPORTANT:
//HOW TO RUN: ./homework A A filepath/file.fasta
int main(int argc, char* argv[])
{
    //declare variables
        //array variables
    char *genomeArray = 0;
    long long int arraySize;
    
    char problem;
    char replaceChar;
    bool printAll = false;
    int newLine = 0;

    //check for necessary arguments
    if(argc != 3)
    {
        //prints error message and expected run command 
        cout << " " << endl;
        cout << "Error: Expecting One Flags and Filename" << endl;
        cout << "Example: ./homework 2A filePath/human.fasta" << endl << endl;

        cout << "First Flag options: " << endl;
        cout << "1A -> Search Array Queries in Genome" << endl;
        cout << "2B -> Sorts Array and Search queries in Genome" << endl;
        cout << "2A -> Search Linked List Queries in Genome" << endl;
        cout << "2B -> Sorts Linked List and Search queries in Genome" << endl;
        return -1;
    }

    //takes second argument and lowers it
    problem = tolower(argv[1][0] & 0xFF);

    //initialize genome array size
        //get array size from file & check for valid array size
    arraySize = fileOptions(argv[3], SIZE, replaceChar, genomeArray);
    if(arraySize == -1)
    {
        cout << "File Not Found" << endl;
        return -1;
    }
        //allocate genome array
    genomeArray = new char[arraySize];

    // First flag checks
    if(problem == 'c' || printAll)
    {
        //count genome characters
        fileOptions(argv[3], COUNT, replaceChar, genomeArray);
        cout << "Genome Character Count: " << arraySize << endl << endl;
    }
    //might need to combine these two and handle two different cases within the funciton itself
    if(problem == 'i' || printAll)
    {
        //count illegal characters
        cout << "Illegal Characters Count: " <<  fileOptions(argv[3], ILLEGAL, replaceChar, genomeArray) << endl << endl;
    }
    if(problem == 'r' || printAll)
    {
        cout << "Replacing illegal characters with '" << replaceChar << "'" << endl;
        //replace illegal characters
        cout << "Number of Characters Replaced with " << replaceChar << ": " << fileOptions(argv[3], REPLACE, replaceChar, genomeArray) << endl << endl;

        if(printAll)
        {
            //performs replacement with the other character
            if(replaceChar == 'N')
            {
                cout << "Replacing illegal characters with 'A'" << endl;
                cout << "Number of Characters Replaced with A: " << fileOptions(argv[3], REPLACE, 'A', genomeArray) << endl;
            }
            else if(replaceChar == 'A')
            {
                cout << "Replacing illegal characters with 'N'" << endl;
                cout << "Number of Characters Replaced with N: " << fileOptions(argv[3], REPLACE, 'N', genomeArray) << endl;
            }

            cout << endl;
        }
    }
    /*
    if(problem == 'p' || printAll)
    {
        if(!printAll)
        {
            //populating genome array
            fileOptions(argv[3], COUNT, replaceChar, genomeArray);
        }

        cout << "LAST 100 CHARACTERS:" << endl;

        //print last 100 characters
        for(long long int i = arraySize - 100; i < arraySize; i++)
        {
            cout << genomeArray[i];

            //just formatting
            newLine++;
            if(newLine % 25 == 0)
            {
                cout << endl;
            }
        }
    }
    */

    //deallocate genome array
    delete[] genomeArray;

    //end program sucess
    return 0;
}
