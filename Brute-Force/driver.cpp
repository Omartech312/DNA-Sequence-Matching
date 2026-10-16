/*
    AI acknowledgement:

*/

//header files
#include "lib.h"
#include "array_lib.h"
#include "LL_lib.h"

//IMPORTANT:
//HOW TO RUN: ./homework 1A filepath/file.fasta
int main(int argc, char* argv[])
{
    cout << "     HOMEWORK 2   \n" << "====================\n\n";
    //declare variables
        //Genome array variables
    char *genomeArray = 0;
    long long int arraySize;

    long long int numberOfQueries;
    
    //might not be needed
    char problem;

    //check for necessary arguments
    if(argc != 4)
    {
        //prints error message and expected run command 
        cout << " " << endl;
        cout << "Error: Expecting One Flag, Genome Filename, Query Filename" << endl;
        cout << "Example: ./homework 2A viral.fasta query.fasta" << endl << endl;

        cout << "Flag options: " << endl;
        cout << "1A -> Search Array Queries in Genome" << endl;
        cout << "2B -> Sorts Array and Search queries in Genome" << endl;
        cout << "2A -> Search Linked List Queries in Genome" << endl;
        cout << "2B -> Sorts Linked List and Search queries in Genome" << endl;
        return -1;
    }

    cout << "File Processing . . ." << endl;
    //takes second argument and lowers it
    problem = toupper(argv[1][1] & 0xFF);

    //initialize genome array size
        //get array size from file & check for valid array size
    arraySize = fileOptions(argv[2], SIZE, genomeArray);

    if(arraySize == -1)
    {
        cout << "File Not Found" << endl;
        return -1;
    }
    //allocate genome array
    //cout << "Array size: " << arraySize << endl;

    genomeArray = new char[arraySize + 1];
    //populates genome array from file
    fileOptions(argv[2], READ, genomeArray);
    genomeArray[arraySize] = '\0';

    //cout << "problem: " << argv[1][0] << problem << endl;

    numberOfQueries = countQueries(argv[3]);
    //cout << "queries: " << numberOfQueries << endl;
    long long int counter = 0;

    //Using Array
    if(argv[1][0] == '1')
    {
        //Fill Array
        arrayClass myArray(numberOfQueries);

        myArray.readQueries(argv[3]);

        auto start = chrono::high_resolution_clock::now();
        cout << endl << "Array Selected" << endl << endl;

        if(problem == 'C')
        {
            int numElements = 10000;
            myArray.sortTime(numElements);
            auto now = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsed = now - start;
            cout << "Sorted: " << (numElements) << " elements" << endl;
            cout << "Time: " << elapsed.count() << " Seconds" << endl << endl;
            /*
            making sure that sorting actually works
            for(int i = 0; i < 5; i++)
            {
                cout << myArray.array[i] << endl;
            }
            */
        }

        //Search without sorting
        if(problem == 'A')
        {
            for(long long int i = 0; i < 100000; i++)
            {
                if(myArray.search(&genomeArray[i]))
                {
                    counter++;
                }

                if (i == 999 || i == 9999 || i == 99999)
                {
                    auto now = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = now - start;

                    cout << "Windows checked: " << (i + 1) << endl;
                    cout << "Hits: " << counter << endl;
                    cout << "Time: " << elapsed.count() << " Seconds" << endl << endl;
                }

            }

        }
        //Sort and then Search
        else if(problem == 'B')
        {
            cout << "Sorting Queries . . ." << endl << endl;
            myArray.sort();

            for(long long int i = 0; i < 100000; i++)
            {
                if(myArray.binarySearch(&genomeArray[i]))
                {
                    counter++;
                }

                if (i == 999 || i == 9999 || i == 99999)
                {
                    auto now = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = now - start;

                    cout << "Windows checked: " << (i + 1) << endl;
                    cout << "Hits: " << counter << endl;
                    cout << "Time: " << elapsed.count() << " Seconds" << endl << endl;
                }

            }

        }
    }
    //Linked List
    else if(argv[1][0] == '2')
    {
        //Fill LL
        cout << endl << "Linked List Selected" << endl << endl;
        llClass List;
        List.readQueries(argv[3]);
        auto start = chrono::high_resolution_clock::now();

        if(problem == 'C')
        {
            int numElements = 10000;
            List.sortTime(numElements);
            auto now = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsed = now - start;
            cout << "Sorted: " << (numElements) << " elements" << endl;
            cout << "Time: " << elapsed.count() << " Seconds" << endl << endl;

        }

        //Search without sorting
        if(problem == 'A')
        {
            for(long long int i = 0; i < 100000; i++)
            {
                if(List.search(&genomeArray[i]))
                {
                    counter++;
                }

                if (i == 999 || i == 9999 || i == 99999)
                {
                    auto now = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = now - start;

                    cout << "Windows checked: " << (i + 1) << endl;
                    cout << "Hits: " << counter << endl;
                    cout << "Time: " << elapsed.count() << " Seconds" << endl << endl;
                }

            }
        }
        //Sort and then Search
        else if(problem == 'B')
        {
            cout << "Sorting Queries . . ." << endl << endl;
            List.sort();
            Node *quarter = List.headPtr;
            Node *half = List.headPtr;
            Node *threeQuarter = List.headPtr;

            for(long long int i = 0; i < List.queryNum ; i++)
            {
                if(i < List.queryNum / 4)
                {
                    quarter = quarter->nextNode;
                }
                if(i < List.queryNum / 2)
                {
                    half = half->nextNode;
                }
                if(i < (3 * List.queryNum) / 4)
                {
                    threeQuarter = threeQuarter->nextNode;
                }

            }

            for(long long int i = 0; i < 100000; i++)
            {
                if(List.binarySearch(&genomeArray[i], quarter, half, threeQuarter))
                {
                    counter++;
                }

                if (i == 999 || i == 9999 || i == 99999)
                {
                    auto now = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = now - start;

                    cout << "Windows checked: " << (i + 1) << endl;
                    cout << "Hits: " << counter << endl;
                    cout << "Time: " << elapsed.count() << " Seconds" << endl << endl;
                }
            }
        }
    }
    else
    {
        cout << "Invalid Problem Number Please Use 1 or 2" << endl;
    }

    //clean up data
    delete[] genomeArray;
    //end program sucess
    return 0;
}
