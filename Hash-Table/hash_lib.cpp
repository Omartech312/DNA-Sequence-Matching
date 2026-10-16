#include "hash_lib.h"

hashClass::hashClass(int initcapacity)
{
    this->array = new Node*[initcapacity];

    for(int i = 0; i < initcapacity ; i++)
    {
        this->array[i] = nullptr;
    }
    this->capacity = initcapacity;
    this->size = 0;
    this->collisions = 0;
}

bool hashClass::readQueries(const char* filename)
{
    //initialize variables
    long long int count = 0;
    int index = 0;
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
                    line[i] = 'A';
                }
            }

            index = radix(line, SEQUENCE);

            insert(line, index);

            count++;
        }
    }
    //close file
    file.close();
    //return final count
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

                    delete[] cur->fragment;
                    cur->fragment = nullptr;

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

void hashClass::insert(char *fragment,int index)
{
    //insert at front (empty headPtr)
    if(this->array[index] == nullptr)
    {
        Node* newNode = new Node;
        newNode->fragment = new char[SEQUENCE + 1];
        newNode->nextNode = nullptr;
        strcpy(newNode->fragment, fragment);
        newNode->fragment[SEQUENCE] = '\0';
        newNode->nextNode = nullptr;
        this->array[index] = newNode;
        this->size++;
    }
    //insertion in existing LL
    else
    {
        Node* newNode = new Node;
        newNode->fragment = new char[SEQUENCE + 1];
        strcpy(newNode->fragment, fragment);
        newNode->fragment[SEQUENCE] = '\0';
        newNode->nextNode = this->array[index];
        this->array[index] = newNode;
        this->collisions++;
    }
}

bool hashClass::search(char *fragment)
{

    int index = radix(fragment, SEQUENCE);

    if(this->array[index] == nullptr)
    {
        return false;
    }

    Node* cur = this->array[index];

    while(cur != nullptr)
    {
        if(compareString(cur->fragment, fragment) == 0)
        {
            return true;
        }
        cur = cur->nextNode;
    }
    return false;
}

int hashClass::resizing(char *filename)
{
    //initialize variables
    long long int count = 0;
    int index = 0;
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
            for(int i = 0; i < ELEVEN + 1; i++)
            {
                //illegal character is replaced with character 'A'
                if(line[i] != 'A' && line[i] != 'C' && line[i] != 'G' && line[i] != 'T')
                {
                    //replacing illegal character with 'A'
                    line[i] = 'A';
                }
            }
            line[ELEVEN] = '\0';

            index = radix(line, ELEVEN);

            dupInsertion(line, index);

            count++;
        }
    }
    //close file
    file.close();

    if((double)this->size / this->capacity > 0.5)
    {
        return false;
    }

    //return final count
    return true;
}

void hashClass::dupInsertion(char *fragment, int index)
{
    //empty headPtr
    if(this->array[index] == nullptr)
    {
        Node* newNode = new Node;
        newNode->fragment = new char[ELEVEN + 1];
        newNode->nextNode = nullptr;
        strcpy(newNode->fragment, fragment);
        newNode->fragment[ELEVEN] = '\0';
        newNode->nextNode = nullptr;
        this->array[index] = newNode;
        this->size++;
    }
    //insertion in existing LL avoiding duplicates
    else
    {
        Node *cur = this->array[index];
        while(cur != nullptr)
        {
            //if duplicate is found, return without inserting
            if(compareString(cur->fragment, fragment) == 0)
            {
                return;
            }
            cur = cur->nextNode;
        }
        Node* newNode = new Node;
        newNode->fragment = new char[ELEVEN + 1];
        strcpy(newNode->fragment, fragment);
        newNode->fragment[ELEVEN] = '\0';
        newNode->nextNode = this->array[index];
        this->array[index] = newNode;
        this->size++;
    }
}