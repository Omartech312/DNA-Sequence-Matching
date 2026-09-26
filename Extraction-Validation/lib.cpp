//header files
#include "lib.h"

#define ONE 1

long long int fileOptions(char *filename, Options option, char replaceChar, char *genomeArray)
{
    
    //initialize variables
    long long int count = 0;
    char line[LARGE_STR_LEN];
    char currentChar;


    //open file
    ifstream file;
    file.open(filename);

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
        else if(option == SIZE || option == COUNT)
        {
            for(int i = 0; line[i] != '\0'; i++)
            {
                if(option == COUNT)
                {
                    //add character to genome array
                    genomeArray[count] = line[i];
                }
                //increment counter
                count++;
            }
        }
        else
        {
            for(int i = 0; line[i] != '\0'; i++)
            {
                currentChar = tolower(line[i] & 0xFF);
                if(option == ILLEGAL)
                {
                    if(replaceValid(currentChar, 'N'))
                    {
                        //increment illegal character count
                        count++;
                    }
                }
                else
                {
                    if(replaceValid(currentChar, replaceChar))
                    {
                        //replace illegal character with 'A'
                        line[i] = replaceChar;
                        count++;
                    }
                }
                //add character to genome array
                genomeArray[count] = line[i];
            }
        }
    }

    //close file
    file.close();
    //return final count
    return count;
}

bool replaceValid(char c, char replaceChar)
{
    // N case replace only if (Not a,c,g,t,n)
    if(replaceChar == 'N')
    {
        if(c != 'a' && c != 'c' && c != 'g' && c != 't' && c != 'n')
        {
            return true;
        }
    }
    // A case replace if (Not a,c,g,t)
    else if(replaceChar == 'A')
    {
        if(c != 'a' && c != 'c' && c != 'g' && c != 't')
        {
            return true;
        }
    }
    // not replaceable case (is a,c,g,t (n))
    return false;
}

Node *createNode()
{
    Node *newNode;
    newNode = new Node;
    //initialize values to default
    newNode->
    newNode->next = NULL;

    return newNode;
}

