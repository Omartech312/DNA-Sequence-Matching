#include "array_lib.h"

arrayClass::arrayClass(long long int numElements)
{
    this->queryNum = numElements;
    //initializes vertical array 
    this->array = new char*[this->queryNum];

    //traverses vertical array to create 2d array
    for(long long int i = 0; i < this->queryNum; i++)
    {
        this->array[i] = new char[SEQUENCE + 1];
    }
}


arrayClass::~arrayClass()
{
    if(this->array != nullptr)
    {
        for(long long int i = 0; i < this->queryNum; i++)
        {
            delete[] this->array[i];
        }
        delete[] this->array;
    }

    this->array = nullptr;
    this->queryNum = 0;
}

bool arrayClass::readQueries(const char* filename)
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
            for(int i = 0; line[i] != '\0'; i++)
            {

                //illegal character is replaced with character 'A'
                if(line[i] != 'A' && line[i] != 'C' && line[i] != 'G' && line[i] != 'T')
                {
                    //replacing illegal character with 'A'
                    this->array[count][i] = 'A';
                }
                else
                {
                    //not illegal character gets added to genome array
                    this->array[count][i] = line[i];
                }
                
            }
            this->array[count][SEQUENCE] = '\0';
            count++;
        }
    }
    //close file
    file.close();
    //return final count
    return count;
}

bool arrayClass::search(const char *sequence)
{
    bool found;

    for(long long int i = 0; i < this->queryNum; i++)
    {
        found = true;

        for(int j = 0; j < SEQUENCE; j++)
        {
            if(this->array[i][j] != sequence[j])
            {
                found = false;
                break;
            }
        }
        if(found)
        {
            return true;
        }
    }
    return false;
}