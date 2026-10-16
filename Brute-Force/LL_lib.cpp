#include "LL_lib.h"

llClass::llClass()
{
    this->headPtr = nullptr;
    this->tailPtr = nullptr;
    this->queryNum = 0;
}

llClass::~llClass()
{
    //gets the headPtr
    Node* cur = this->headPtr;

    //loops as long as its not null
    while (cur != nullptr)
    {
        Node* next = cur->nextNode;

        delete[] cur->fragment;
        cur->fragment = nullptr;

        delete cur;
        cur = next;
    }

    this->headPtr = nullptr;
    this->tailPtr = nullptr;
    this->queryNum = 0;
}

bool llClass::readQueries(const char* filename)
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
        return false;
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
            Node* newNode = new Node();
            newNode->fragment = new char[SEQUENCE + 1];

            for(int i = 0; i < SEQUENCE; i++)
            {
                //illegal character is replaced with character 'A'
                if(line[i] != 'A' && line[i] != 'C' && line[i] != 'G' && line[i] != 'T')
                {
                    //replacing illegal character with 'A'
                    newNode->fragment[i] = 'A';
                }
                else
                {
                    //not illegal character gets added to genome array
                    newNode->fragment[i] = line[i];
                }
                
            }
            newNode->fragment[SEQUENCE] = '\0';
            count++;

            if(this->headPtr == nullptr)
            {
                this->headPtr = newNode;
                this->tailPtr = newNode;
            }
            else
            {
                this->tailPtr->nextNode = newNode;
                this->tailPtr = newNode;
            }
        }
    }
    //close file
    file.close();
    this->queryNum = count;

    return true;
}

bool llClass::search(const char *sequence)
{
    Node* cur = this->headPtr;
    bool found;

    while(cur != nullptr)
    {
        found = true;

        for(int j = 0; j < SEQUENCE; j++)
        {
            if(cur->fragment[j] != sequence[j])
            {
                found = false;
                break;
            }
        }
        if(found)
        {
            return true;
        }
        cur = cur->nextNode;
    }
    return false;
}

void llClass::sort()
{
    Node* cur = this->headPtr;
    while(cur != nullptr)
    {
        Node* minNode = cur;
        Node* nextNode = cur->nextNode;
        while(nextNode != nullptr)
        {
            if(compareString(nextNode->fragment, minNode->fragment) < 0)
            {
                minNode = nextNode;
            }
            nextNode = nextNode->nextNode;
        }
        if(minNode != cur)
        {
            char* temp = cur->fragment;
            cur->fragment = minNode->fragment;
            minNode->fragment = temp;
        }
        cur = cur->nextNode;
    }
}

bool llClass::binarySearch(const char *sequence, Node* quarter, Node* half, Node* threeQuarter)
{
    Node* cur = this->headPtr;
    Node* end = this->tailPtr;

    if(compareString(half->fragment, sequence) < 0)
    {
        if(compareString(threeQuarter->fragment, sequence) > 0)
        {
            //its in the third quarter
            cur = half;
            end = threeQuarter;
        }
        else if(compareString(threeQuarter->fragment, sequence) < 0)
        {
            //its in the last quarter
            cur = threeQuarter;
            end = this->tailPtr;
        }
        else
        {
            //its the three quarter element
            return true;
        }
    }
    else if(compareString(half->fragment, sequence) > 0)
    {
        //its in the first half
        if(compareString(quarter->fragment, sequence) < 0)
        {
            //its in the second quarter
            cur = quarter;
            end = half;
        }
        else if(compareString(quarter->fragment, sequence) > 0)
        {
            //its in the first quarter
            cur = this->headPtr;
            end = quarter;
        }
        else
        {
            //its the quarter element
            return true;
        }
    }
    else
    {
        //its the middle element
        return true;
    }

    while(cur != nullptr && cur != end)
    {
        bool found = true;

        for(int j = 0; j < SEQUENCE; j++)
        {
            if(cur->fragment[j] != sequence[j])
            {
                found = false;
                break;
            }
        }
        if(found)
        {
            return true;
        }
        cur = cur->nextNode;
    }
    if (end == this->tailPtr && compareString(end->fragment, sequence) == 0)
    {
        return true;
    }
    return false;
}

void llClass::sortTime(const int numElements)
{
    Node* cur = this->headPtr;
    int count = 0;

    while(cur != nullptr && count < numElements)
    {
        int traversalCount = 0;
        Node* minNode = cur;
        Node* nextNode = cur->nextNode;
        while(nextNode != nullptr && traversalCount < numElements)
        {
            if(compareString(nextNode->fragment, minNode->fragment) < 0)
            {
                minNode = nextNode;
            }
            nextNode = nextNode->nextNode;
            traversalCount++;
        }
        if(minNode != cur)
        {
            char* temp = cur->fragment;
            cur->fragment = minNode->fragment;
            minNode->fragment = temp;
        }
        cur = cur->nextNode;
        count++;
    }
}

