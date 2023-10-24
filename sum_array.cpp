#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include<chrono>
using namespace std;



//To compile the program file: g++ -fopenmp -o sum_array sum_array.cpp
//to execute the program file: ./sum_array (size of the array) (number of threads)







int main(int argc, char* argv[]) {

	//size of the array taken as input from command line
    int arraySize = atoi(argv[1]);
     
    //number of threads is bbeing from input
    int thread=atoi(argv[2]);
    omp_set_num_threads(thread);
    
    //to calculate the time required to calculate the execute the program
    auto start = std::chrono::high_resolution_clock::now();

    // Create and fill a random array
    int* array = new int[arraySize];
    srand(static_cast<unsigned>(time(0)));

    //array is being filled with random values
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % 100;
    }

    // Save the array to a file
    ofstream outFile("SUM_ARRAY_INPUT.txt");
    if (!outFile) {
        cerr << "Error opening the file for writing." << endl;
        return 1;
    }
    for (int i = 0; i < arraySize; ++i) {
        outFile << array[i] << " ";
    }
    outFile.close();
    cout << "Random array saved to SUM_ARRAY_INPUT.txt" << endl;

    // Parallel sum of the array
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arraySize; ++i) {
        sum += array[i];
    }

    // Clean up
    delete[] array;

    cout << "The sum of the array: " << sum << endl;

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_time = end - start;

    std::cerr << "Execution time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
