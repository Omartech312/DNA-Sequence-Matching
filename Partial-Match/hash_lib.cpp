#include "hash_lib.h"

hashClass::hashClass(long long int initcapacity)
{
    this->array = new Node*[initcapacity];

    for(long long int i = 0; i < initcapacity; i++)
    {
        this->array[i] = nullptr;
    }

    this->capacity = initcapacity;
}

long long int hashClass::populateHash(char* genome, long long int arraySize, int seedSize)
{
    long long int index;
    long long int count = 0;

    for(long long int i = 0; i < arraySize - seedSize + 1; i++)
    {
        index = radix(&genome[i], seedSize);
        insert(i, index);
        count++;
    }
    return count;
}

hashClass::~hashClass()
{
    if(this->capacity > 0)
    {

        int i = 0;
        Node *cur;

        while(i < this->capacity)
        {

            if(this->array[i] != nullptr)
            {
                cur = this->array[i];
                while(cur != nullptr)
                {
                    Node* next = cur->nextNode;

                    delete cur;
                    cur = next;
                }
                this->array[i] = nullptr;
            }
            i++;
        }
    }
}

unsigned long long int hashClass::radix(char *fragment, int fragLen)
{
    int value = 0;
    unsigned long long int total = 0;

    for(int i = 0; i < fragLen; i++)
    {
        if(fragment[i] == 'A')
        {
            value = 0;
        }
        else if(fragment[i] == 'C')
        {
            value = 1;
        }
        else if(fragment[i] == 'G')
        {
            value = 2;
        }
        else
        {
            value = 3;
        }

        total = total * 4 + value;
    }
    //get an index
    return total % this->capacity;
}

void hashClass::insert(long long int location, long long int index)
{
    //insert at front (empty headPtr)

    Node* newNode = new Node;
    //location in genome 2D array
    newNode->fragmentLocation =  location;
    newNode->nextNode = this->array[index];
    //
    this->array[index] = newNode;
}

bool hashClass::kmer(uint8_t **matrix,char *query, char* genome, int seedSize)
{
    long long int index;
    for(int i = 0; i < SEQUENCE - seedSize + 1; i++)
    {
        index = radix(&query[i], seedSize);
        if(this->array[index] == nullptr)
        {
            return false;
        }
        else
        {
            if(search(matrix, &query[i], genome, index, seedSize, i, query))
            {
                return true;
            }
        }
    }
    return false;
}

bool hashClass::search(uint8_t **matrix,char *fragment, char* genome, long long int index, int seedSize, int offset, char* query)
{
    Node* cur = this->array[index];
    //cout << "Searching for fragment: " << fragment << " at index: " << index << endl;

    while(cur != nullptr)
    {
        if(compareString(fragment, &genome[cur->fragmentLocation], seedSize) == 0)
        {
            //Use Smith Waterman here for partial matches. How big should be the NxN matrix?
            if(smithWaterman(matrix, &genome[cur->fragmentLocation - offset], query, SEQUENCE))
            {
                return true;
            }
        }
        cur = cur->nextNode;
    }
    return false;
}