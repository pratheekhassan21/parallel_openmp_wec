#include <iostream>
#include <iomanip>
#include <omp.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include<chrono>
#include <ctime>
#include <cstdio>
using namespace std;

//To compile and run the program file; g++ -fopenmp -o lu_decomposition lu_decomposition.cpp





void print(float**, int);

// Print the matrix out
void print(float** matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << left << setw(9) << setprecision(3) << matrix[i][j] << left << setw(9);
        }
        cout << endl;
    }
}

// Load the matrix from a file
void loadMatrixFromFile(float** matrix, int size, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening the file for reading." << endl;
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            inFile >> matrix[i][j];
        }
    }

    inFile.close();
}

// Save a random matrix to a file
void saveRandomMatrix(int size, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening the file for writing." << endl;
        exit(1);
    }

    srand(static_cast<unsigned>(time(0)));

    //matrix is being filled with random values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            outFile << (rand() % 10 + 1) << " ";
        }
        outFile << "\n";
    }

    outFile.close();
}

// LU decomposition function
void LU_DECOMPOSE(float** a, float** l, float** u, int size)
{
    //initialize a simple lock for parallel region
    omp_lock_t lock;

    omp_init_lock(&lock);
    //for each column...
    //make the for loops of lu decomposition parallel. Parallel region
    #pragma omp parallel shared(a,l,u)
    {
    
        for (int i = 0; i < size; i++)
        {
            //for each row....
            //rows are split into seperate threads for processing
            #pragma omp for schedule(static)
            for (int j = 0; j < size; j++)
            {
                //if j is smaller than i, set l[j][i] to 0
                if (j < i)
                {
                    l[j][i] = 0;
                    continue;
                }
                //otherwise, do some math to get the right value
                l[j][i] = a[j][i];
                for (int k = 0; k < i; k++)
                {
                    //deduct from the current l cell the value of these 2 values multiplied
                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
                }
            }
            //for each row...
            //rows are split into seperate threads for processing
            #pragma omp for schedule(static)
            for (int j = 0; j < size; j++)
            {
                //if j is smaller than i, set u's current index to 0
                if (j < i)
                {
                    u[i][j] = 0;
                    continue;
                }
                //if they're equal, set u's current index to 1
                if (j == i)
                {
                    u[i][j] = 1;
                    continue;
                }
                //otherwise, do some math to get the right value
                u[i][j] = a[i][j] / l[i][i];
                for (int k = 0; k < i; k++)
                {
                    u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                }
            
            }
        }
    }
}
int main(int argc, char** argv)
{
	auto start = std::chrono::high_resolution_clock::now();
   
    int thread=atoi(argv[2]);

    // Number of threads is set manually
    omp_set_num_threads(thread);

    // Size of matrix
    int size = atoi(argv[1]);

    // Initialize matrices
    float** a = new float*[size];
    float** l = new float*[size];
    float** u = new float*[size];

    // Check if the matrix file exists, if not, create and save it
    string matrixFilename = "matrix.txt";
    if (!ifstream(matrixFilename)) {
        // File doesn't exist, generate a random matrix and save it
        cout << "Matrix file not found. Generating a random matrix and saving it." << endl;
        saveRandomMatrix(size, matrixFilename);
        cout << "Matrix saved to " << matrixFilename << endl;
    } else {
        // File exists, load the matrix
        for (int i = 0; i < size; i++) {
            a[i] = new float[size];
            l[i] = new float[size];
            u[i] = new float[size];
        }
        loadMatrixFromFile(a, size, matrixFilename);
    }

    // Redirect the output to lu_out.txt, create if it doesn't exist
    freopen("lu_out.txt", "w", stdout);

    // Print A
    cout << "A Matrix: " << endl;
    print(a, size);

    // FINDING RUNTIME USING STANDARD OMP GET_TIME
    // runtime = omp_get_wtime();
    // DOING LU DECOMPOSITION
    LU_DECOMPOSE(a, l, u, size);
    // Print L and U
    cout << "L Matrix: " << endl;
    print(l, size);
    cout << "U Matrix:" << endl;
    print(u, size);
    // TOTAL RUNTIME OF THE PROGRAM
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_time = end - start;

    std::cerr << "Execution time: " << elapsed_time.count() << " seconds" << std::endl;


    // Free memory for a, l, and u
    for (int i = 0; i < size; ++i) {
        delete[] a[i];
        delete[] l[i];
        delete[] u[i];
    }
    delete[] a;
    delete[] l;
    delete[] u;

    return 0;
}
