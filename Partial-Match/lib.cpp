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

int compareString( const char *oneStr, const char *otherStr, int length)
{
    // initialize function/variables
    int diff, index = 0; 

    // loop to end of shortest string w/ overrun protection
    while( oneStr[index] != NULL_CHAR
                                && otherStr[index] != NULL_CHAR
                                                && index < length )
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
        index++; 
    }

    // return difference in lengths, if any
    return 0;
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

uint8_t** declareMatrix(int rows, long long int cols)
{
    //creates 1st dimension of matrix
    uint8_t **matrix = new uint8_t*[rows];

    //iterates through rows
    for(int i = 0; i < rows; i++)
    {
        //creates 2nd dimension of matrix
        matrix[i] = new uint8_t[cols]();

    }

    //returns pointer to matrix
    return matrix;
}

void freeMatrix(uint8_t **matrix, int rows)
{
    //iterates through rows
    for(int i = 0; i < rows; i++)
    {
        //frees memory allocated for each row
        delete[] matrix[i];
    }
    //frees memory allocated for the matrix
    delete[] matrix;
}

bool smithWaterman(uint8_t **matrix, char *genomeArray, char *queryArray, long long int genomeLength)
{
    int highest = 0;
    //iterates through rows
    for(long long int i = 1; i <= genomeLength; i++)
    {
        for(int j = 1; j <= SEQUENCE; j++)
        {
            //diagonal
            if(genomeArray[i-1] == queryArray[j-1])
            {
                matrix[j][i] = matrix[j-1][i-1] + MATCH;
            }
            else
            {
                matrix[j][i] = max((int)(matrix[j-1][i-1] + MISMATCH), 0);
            }

            highest = max((int)matrix[j-1][i] + GAP, (int)matrix[j][i-1] + GAP);

            matrix[j][i] = max((int)matrix[j][i], highest);

        }
        //check for hit
        if(matrix[SEQUENCE][i] == FULL_MATCH || matrix[SEQUENCE][i] == ONE_MISMATCH || matrix[SEQUENCE][i] == ONE_GAP)
        {
            return true;
        }
    }
    //no hit found
    return false;
}

void introduceError(char *sequence, int errorRate)
{
    int randChar;
    char newChar = NULL_CHAR;
    //iterates through characters in sequence
    for(int i = 0; i < SEQUENCE; i++)
    {
        //generates random number between 0 and 99
        int randNum = rand() % 100;

        //if random number is less than error rate, introduce error
        if(randNum < errorRate)
        {
            do
            {
                //generates random number between 0 and 3 to determine which character to replace with
                randChar = rand() % 4;

                //replaces character with random character
                switch(randChar)
                {
                    case 0:
                        newChar = 'A';
                        break;
                    case 1:
                        newChar = 'C';
                        break;
                    case 2:
                        newChar = 'G';
                        break;
                    case 3:
                        newChar = 'T';
                        break;
                }
            } while (newChar == sequence[i]);
            sequence[i] = newChar;
        }
    }
}