#include <vector>
#include <string>
#include <sys/time.h>
#include <iostream>
#include <unordered_map>
#include "sorts.h"

using namespace std;

//Global variables

//Hashmap that stores [UserInput, sorting function]
//Sorting functions take in:
//  Reference of vector to sort
//  Beginning index
//  Ending index
unordered_map<string, function<void(vector<int>&, int, int)>> SortingMethods = {
    {"BubbleSort", sorts::BubbleSort},
    {"InsertionSort", sorts::InsertionSort},
    {"MergeSort", sorts::MergeSort},
    {"IterativeMergeSort", sorts::IterativeMergeSort},
    {"QuickSort", sorts::QuickSort},
    {"ShellSort", sorts::ShellSort},
};

//Global functions
void InitVector(vector<int>& item_vector, int size);
void PrintVector(const vector<int>& item_vector, string name);
int Elapsed(const timeval &start, const timeval &end);

int main(int argc, char* argv[])
{
    //Valid argument amount check
    if ((argc != 3) && (argc != 4))
    {
        cerr << "Usage: Sorter algorithm size [Print]" << endl;
        return -1;
    }

    //Assign inputs to variables
    string sort_name = string(argv[1]);
    int size = atoi(argv[2]);
    bool print_out = false;

    //Size error check
    if (size <= 0)
    {
        cerr << "Vector size must be positive" << endl;
        return -1;
    }

    //Print argument check and confirmation
    if (argc == 4)
    {
        string print_arr = string(argv[3]);
        if (print_arr == "Print")
        {
            print_out = true;
        }
        else
        {
            cerr << "Usage: Sorter algorithm size [Print]" << endl;
            return -1;
        }
    }

    //Making a vector using seed randomization and size input
    srand(1);
    vector<int> items(size);
    InitVector(items, size);

    //Prints out randomized vector if optional Print input exists
    if (print_out)
    {
        cout << "Initial:" << endl;
        PrintVector(items, string("items"));
        cout << endl;
    }

    //Set up a timer
    struct timeval start_time, end_time; //contains times
    gettimeofday(&start_time, 0); //Note start time

    //Do the sorting method
    if (SortingMethods.find(sort_name) != SortingMethods.end()) {
        SortingMethods[sort_name](items, 0, size - 1);
    } else {
        //Case where the sorting method doesn't exist
        cerr << "Sort method not found" << endl;

        string methods;
        for (const auto& pair : SortingMethods) {
            methods += pair.first + ", ";
        }
        cerr << methods << endl;

        return -1;
    }

    //Note end time
    gettimeofday(&end_time, 0); //Not sure what this function does

    //Print out sorted list
    if (print_out)
    {
        cout << "Sorted:" << endl;
        PrintVector(items, string("item"));
    }

    //Print out time for completion
    cout << "Time (microsecs): " << Elapsed(start_time, end_time) << endl;
    return 0;
}

void InitVector(vector<int>& item_vector, int rand_max)
{
    if (rand_max < 0)
    {
        return;
    }
    vector<int> pool(rand_max);
    for (int i = 0; i < rand_max; i++)
    {
        pool[i] = i;
    }
    int spot;
    for (int i = 0; i < rand_max; i++)
    {
        spot = rand() % (pool.size());
        item_vector[i] = pool[spot];
        pool.erase(pool.begin() + spot);
    }
}
void PrintVector(const vector<int>& item_vector, string name)
{
    int size = item_vector.size();
    for (int i = 0; i < size; i++)
    {
        cout << item_vector[i] << " ";
    }
    cout << endl;
}
// Function to calculate elapsed time
// Microseconds
int Elapsed(const timeval &start, const timeval &end)
{
    return (end.tv_sec - start.tv_sec) * 1000000
    + (end.tv_usec - start.tv_usec);
}