//header files
#include "lib.h"

//counts chars and 
long long int fileOptions(char *filename, Options option, char *genomeArray)
{    
    //initialize variables
    long long int count = 0;
    char line[LARGE_STR_LEN];

    //open file
    ifstream file;
    file.open(filename);

    //check if file was correctly opened
    if(!file)
    {
        cout << "Error opening file" << endl;
        return -1;
    }

    //read through file character by character
    while(file.getline(line, LARGE_STR_LEN))
    {
        //check for header line
        if(line[0] == '>')
        {
            //ignore header lines
            continue;
        }
        else if(option == SIZE || option == READ)
        {
            for(int i = 0; line[i] != '\0'; i++)
            {
                if(option == READ)
                {
                    //illegal character is replaced with character 'A'
                    if(line[i] != 'A' && line[i] != 'C' && line[i] != 'G' && line[i] != 'T')
                    {
                        //replacing illegal character with 'A'
                        genomeArray[count] = 'A';
                    }
                    else
                    {
                        //not illegal character gets added to genome array
                        genomeArray[count] = line[i];
                    }
                }
                //increment counter
                count++;
            }
        }
    }
    //close file
    file.close();
    //return final count
    return count;
}

int compareString( const char *oneStr, const char *otherStr)
{
    // initialize function/variables
    int diff, index = 0; 

    // loop to end of shortest string w/ overrun protection
    while( oneStr[index] != NULL_CHAR
                                && otherStr[index] != NULL_CHAR
                                                && index < SEQUENCE )
    {
        // get difference in characters
        diff = oneStr[index] - otherStr[index];

        // check for difference between characters
        if(diff != 0)
        {
            // return difference
            return diff; 
        }

        // increment index
        index ++; 
    }

    // return difference in lengths, if any
    return 0;
}

int getStringLength(const char *testStr)
{
    // initialize function/variables
    int index = 0;

    // loop to the end of string, protect from overflow
    while(index < STD_STR_LEN && testStr[index] != NULL_CHAR)
    {

        // update index
        index ++;
    }

    // return index/length
    return index;
}

long long int countQueries(char *filename)
{    
    //initialize variables
    long long int count = 0;
    char line[LARGE_STR_LEN];

    //open file
    ifstream file;
    file.open(filename);

    //check if file was correctly opened
    if(!file)
    {
        cout << "Error opening file" << endl;
        return -1;
    }

    //read through file character by character
    while(file.getline(line, LARGE_STR_LEN))
    {
        //check for header line
        if(line[0] == '>')
        {
            //ignore header lines
            continue;
        }
        else
        {
            count++;
        }
    }
    //close file
    file.close();
    //return final count
    return count;
}

