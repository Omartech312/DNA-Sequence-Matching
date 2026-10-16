/*
    AI acknowledgement:

*/

//header files
#include "lib.h"
#include "hash_lib.h"

//IMPORTANT:
//HOW TO RUN: ./homework 1A filepath/file.fasta
int main(int argc, char* argv[])
{
    cout << "     HOMEWORK 3   \n" << "====================\n";
    //declare variables
        //Genome array variables
    char *genomeArray = 0;
    long long int arraySize;
    
    //might not be needed
    char problem;

    //check for necessary arguments
    if(argc != 4)
    {
        cout << "Problems B-D Expect One flag, Genome Filename, Query Filename" << endl;
        cout << "Example: ./homework 2B viral.fasta query.fasta" << endl << endl;
        cout << "Flag options: " << endl;
        cout << "1A -> Search hash table with 1M, 50M, 100M, 200M" << endl;
        cout << "1B -> Search Speed with hash table size 50M" << endl;
        cout << "1C -> Search Speed with hash table size 200M" << endl;
        cout << "1D -> Dynamically resizing hash table starting with 1M" << endl;
        return -1;
    }

    cout << "File Processing . . ." << endl;
    //takes second argument and lowers it
    problem = toupper(argv[1][1] & 0xFF);

    if(problem != 'A' || problem != 'D')
    {
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
    }

    int hits = 0;
    int firstTen = 0;

    //Using Array
    if(problem == 'A')
    {
        int sizes[] = {1, 50, 100, 200};

        for(int i = 0; i < 4; i++)
        {
            hashClass table(sizes[i] * MILLION);

            cout << "\nHash Table Size: " << sizes[i] << " Million" << endl;

            auto start = chrono::high_resolution_clock::now();
            table.readQueries(argv[3]);
            auto end = chrono::high_resolution_clock::now();

            double seconds = chrono::duration<double>(end - start).count();

            cout << "Time: " << seconds << " seconds" << endl;
            cout << "Number of Collisions: " << table.collisions << endl;
        }
    }
    else if(problem == 'B')
    {
        hashClass table(50 * MILLION);
        table.readQueries(argv[3]);

        cout << "\nPrinting first 10 hits:" << endl;
        
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < arraySize - SEQUENCE + 1; i++)
        {
            if(table.search(&genomeArray[i]))
            {
                hits++;
                if(firstTen < 10)
                {
                    for(int j = 0; j < SEQUENCE; j++)
                    {
                        cout << genomeArray[i + j];
                    }
                    cout << endl;
                    firstTen++;
                }
            }
        }
        auto end = chrono::high_resolution_clock::now();

        double seconds = chrono::duration<double>(end - start).count();
        cout << "\nTime: " << seconds << " seconds" << std::endl;
        cout << "\nTotal Hits: " << hits << endl;
    }
    else if(problem == 'C')
    {
        hashClass table(200 * MILLION);
        table.readQueries(argv[3]);

        cout << "\nPrinting first 10 hits:" << endl;
        
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < arraySize - SEQUENCE + 1; i++)
        {
            if(table.search(&genomeArray[i]))
            {
                hits++;
                if(firstTen < 10)
                {
                    for(int j = 0; j < SEQUENCE; j++)
                    {
                        cout << genomeArray[i + j];
                    }
                    cout << endl;
                    firstTen++;
                }
            }
        }
        auto end = chrono::high_resolution_clock::now();

        double seconds = chrono::duration<double>(end - start).count();
        cout << "\nTime: " << seconds << " seconds" << std::endl;
        cout << "\nTotal Hits: " << hits << endl;
    }
    else if(problem == 'D')
    {
        int initSize = 0;
        bool resizing = false;
        while(!resizing)
        {
            initSize++;
            hashClass table(initSize * MILLION);
            resizing = table.resizing(argv[3]);
        }

        cout << "\nDynamically resizing requires " << initSize << " Million entries." << endl;
    }
    else
    {
        cout << "Invalid problem" << endl;
    }

    //clean up data
    delete[] genomeArray;
    //end program sucess
    return 0;
}

