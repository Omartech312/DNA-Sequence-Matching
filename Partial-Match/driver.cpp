/*
    AI acknowledgement:

*/

//header files
#include "lib.h"
#include "array_lib.h"
#include "hash_lib.h"

//IMPORTANT:
//HOW TO RUN: ./homework 1A filepath/file.fasta
int main(int argc, char* argv[])
{
    //print title
    cout << "     HOMEWORK 4   \n" << "====================\n";

    // Initialize random seed
    srand(time(NULL)); 

    //declare variables
        //Genome array variables
    char *genomeArray = 0;
    long long int arraySize;
    int queriesNum;
    int randomIndex;
    
    //might not be needed
    char problem;
    int hits = 0;
    bool display = true;


    //check for necessary arguments
    if(argc != 4)
    {
        cout << "Problems B-D Expect One flag, Genome Filename, Query Filename" << endl;
        cout << "Example: ./homework 1B viral.fasta query.fasta" << endl << endl;
        cout << "Flag options: " << endl;
        cout << "1A -> Smith Waterman - Search with real data" << endl;
        cout << "1B -> Smith Waterman - Search with Garbage data" << endl;
        cout << "2A -> BLAST - Search with real data" << endl;
        cout << "2B -> BLAST - Search with Garbage data" << endl;
        cout << "2C -> BLAST - Impact of seed size" << endl;
        return -1;
    }

    cout << "File Processing . . .\n" << endl;
    //takes second argument and lowers it
    problem = toupper(argv[1][1] & 0xFF);

    //initialize genome array size
        //get array size from file & check for valid array size
    arraySize = fileOptions(argv[2], SIZE, genomeArray);
    queriesNum = countQueries(argv[3]);

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

    arrayClass myArray(queriesNum);
    myArray.readQueries(argv[3]);

    cout << "Important Information:\n" << endl;
    cout << "Genome Length: " << arraySize << endl;
    cout << "Number of Queries: " << queriesNum << endl;
    if(argv[1][0] == '1')
    {
        cout << "Searches: " << LOOPS << endl << endl;
    }
    else
    {
        cout << "Searches: All Queries" << endl << endl;
    }

    if(argv[1][0] == '1')
    {
        //decleare 2d array for smith waterman
        uint8_t **matrix = declareMatrix(SEQUENCE + 1, arraySize + 1);
                
        //smith waterman
        if(problem == 'A')
        {
            //real data
            cout << "Smith Waterman - Real Data\n" << endl;
            auto start = chrono::high_resolution_clock::now();

            for(int i = 0; i < LOOPS; i++)
            {
                randomIndex = rand() % queriesNum;
                if(smithWaterman(matrix, genomeArray, myArray.array[randomIndex], arraySize))
                {
                    hits++;
                    display = true;
                }
                if(i % 50 == 0 && i != 0 && display)
                {
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = end - start;
                    cout << "Query #: " << i << endl;
		    cout << "Number of hits: " << hits << endl;
                    cout << "Time: " << elapsed.count() << " seconds\n" << endl;
                    display = false;               
                }
            }
            cout << "Number of hits: " << hits << endl;
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            cout << "Time: " << elapsed.count() << " seconds\n";


        }
        else if(problem == 'B')
        {
            //garbage data
            cout << "Smith Waterman - Garbage Data" << endl;
            cout << "Introducing errors into queries . . ." << endl << endl;
            auto start = chrono::high_resolution_clock::now();

            for(int i = 0; i < LOOPS; i++)
            {
                randomIndex = rand() % queriesNum;
                introduceError(myArray.array[randomIndex], ERROR_RATE);
                if(smithWaterman(matrix, genomeArray, myArray.array[randomIndex], arraySize))
                {
                    hits++;
                    display = true;
                }

                if(i % 50 == 0 && i != 0 && display)
                {
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = end - start;
                    cout << "Query #: " << i << endl;
                    cout << "Number of hits: " << hits << endl;
                    cout << "Time: " << elapsed.count() << " seconds\n" << endl;    
                    display = false;            
                }
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            cout << "Final results:" << endl;
            cout << "Number of hits: " << hits << endl;
            cout << "Time: " << elapsed.count() << " seconds\n";
        }
        else
        {
            cout << "Invalid Subproblem Letter" << endl;
            return -1;
        }

        freeMatrix(matrix, SEQUENCE + 1);
    }
    else if(argv[1][0] == '2')
    {
        uint8_t **matrix = declareMatrix(SEQUENCE + 1, SEQUENCE + 1);
        cout << "Smith Waterman matrix declared for BLAST" << endl;

        // blast
        //declare and initialize hash table
        hashClass table(arraySize);
        cout << "Hash Table Declared with capacity: " << arraySize << endl;

        if(problem == 'A')
        {
            //fill hash table with genome fragments
            long long int count = table.populateHash(genomeArray, arraySize, SEED_SIZE);
            cout << "Hash Table Populated with " << count << " fragments\n" << endl;

            // real data
            cout << "BLAST - Real Data\n" << endl;
            auto start = chrono::high_resolution_clock::now();
            for(int i = 0; i < queriesNum; i++)
            {
                if(table.kmer(matrix, myArray.array[i], genomeArray, SEED_SIZE))
                {
                    hits++;
                    display = true;
                }

                if((i % (MILLION) == 0) && i != 0 && display)
                {
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = end - start;
                    cout << "Query #: " << i << endl;
                    cout << "Number of hits: " << hits << endl;
                    cout << "Time: " << elapsed.count() << " seconds\n" << endl;   
                    display = false;             
                }
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            cout << "Final results:" << endl;
            cout << "Number of hits: " << hits << endl;
            cout << "Time: " << elapsed.count() << " seconds\n";
        }
        else if(problem == 'B')
        {
            //fill hash table with genome fragments
            long long int count = table.populateHash(genomeArray, arraySize, SEED_SIZE);
            cout << "Hash Table Populated with " << count << " fragments\n" << endl;

            // garbage data
            cout << "BLAST - Garbage Data\n" << endl;
            auto start = chrono::high_resolution_clock::now();
            for(int i = 0; i < queriesNum; i++)
            {
                introduceError(myArray.array[i], ERROR_RATE);
                if(table.kmer(matrix, myArray.array[i], genomeArray, SEED_SIZE))
                {
                    hits++;
                    display = true;
                }
                if((i % (MILLION) == 0) && i != 0 && display)
                {
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = end - start;
                    cout << "Query #: " << i << endl;
                    cout << "Number of hits: " << hits << endl;
                    cout << "Time: " << elapsed.count() << " seconds\n" << endl; 
                    display = false;               
                }
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            cout << "Final results:" << endl;
            cout << "Number of hits: " << hits << endl;
            cout << "Time: " << elapsed.count() << " seconds\n";
        }
        else if(problem == 'C')
        {
            //fill hash table with genome fragments
            long long int count = table.populateHash(genomeArray, arraySize, 30);
            cout << "Hash Table Populated with " << count << " fragments\n" << endl;

            // impact of seed size
            cout << "BLAST - Impact of Seed Size (30)\n" << endl;
            auto start = chrono::high_resolution_clock::now();
            for(int i = 0; i < queriesNum; i++)
            {
                if(table.kmer(matrix, myArray.array[i], genomeArray, 30))
                {
                    hits++;
                    display = true;
                }
                if((i % (10 * MILLION) == 0) && i != 0 && display)
                {
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = end - start;
                    cout << "Number of hits: " << hits << endl;
                    cout << "Time: " << elapsed.count() << " seconds\n" << endl;  
                    display = false;              
                }
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            cout << "Final results:" << endl;
            cout << "Number of hits: " << hits << endl;
            cout << "Time: " << elapsed.count() << " seconds\n";
        }
        else
        {
            cout << "Invalid Subproblem Letter" << endl;
            return -1;
        }
    }
    else
    {
        cout << "Invalid problem number" << endl;
        return -1;
    }

    //clean up data
    delete[] genomeArray;
    //end program sucess
    return 0;
}

