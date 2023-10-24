#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;


//to compile and run file: g++ -fopenmp -o inverse_matrix inverse_matrix.cpp
//to execute: ./inverse_matrix (size of the matrix) (number of threads)




// Filling the allocated matrix with random values
float** create_and_fill_matrix(int size) {
    float** matrix = new float*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new float[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = static_cast<float>(rand()) / RAND_MAX; // Fill with random float values between 0 and 1
        }
    }
    return matrix;
}

// Save a matrix to a file
void save_matrix_to_file(float** matrix, int size, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening the file for writing." << endl;
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            outFile << matrix[i][j] << " ";
        }
        outFile << "\n";
    }

    outFile.close();
    cout << "Matrix saved to " << filename << endl;
}

// Dynamically allocate memory for a matrix and create an identity matrix
float** generate_identity(int size) {
    float** matrix = new float*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new float[size];
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 1.0f; // Diagonal elements are filled with 1
            } else {
                matrix[i][j] = 0.0f; // Rest of the matrix is being filled with 0
            }
        }
    }
    return matrix;
}

// The memory is deallocated after finding the inverse of the matrix
void delete_matrix(float** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Gaussian Jordan elimination is being implemented to find the inverse of the matrix in parallel
float** generate_inverse_parallel(float** input_matrix, int size, int threads) {
    float** I = generate_identity(size);
    for (int i = 0; i < size; i++) {
        if (input_matrix[i][i] == 0) {
            // swap nearest subsequent row s.t input_matrix[i][i] != 0 after swapping
            for (int j = i + 1; j < size; j++) {
                if (input_matrix[j][i] != 0.0f) {
                    swap(input_matrix[i], input_matrix[j]);
                    swap(I[i], I[j]);
                    break;
                }
                if (j == size - 1) {
                    cout << "Inverse does not exist for this matrix";
                    exit(0);
                }
            }
        }
        float scale = input_matrix[i][i];
        omp_set_num_threads(threads);
#pragma omp parallel for
        for (int col = 0; col < size; col++) {
            input_matrix[i][col] = input_matrix[i][col] / scale;
            I[i][col] = I[i][col] / scale;
        }
        if (i < size - 1) {
#pragma omp parallel for
            for (int row = i + 1; row < size; row++) {
                float factor = input_matrix[row][i];
                for (int col = 0; col < size; col++) {
                    input_matrix[row][col] -= factor * input_matrix[i][col];
                    I[row][col] -= factor * I[i][col];
                }
            }
        }
    }
    // Zero out the elements above the diagonal in both matrices
    for (int zeroing_col = size - 1; zeroing_col >= 1; zeroing_col--) {
#pragma omp parallel for
        for (int row = zeroing_col - 1; row >= 0; row--) {
            float factor = input_matrix[row][zeroing_col];
            for (int col = 0; col < size; col++) {
                input_matrix[row][col] -= factor * input_matrix[zeroing_col][col];
                I[row][col] -= factor * I[zeroing_col][col];
            }
        }
    }
    return I;
}

// Printing the matrix
void print_matrix(float** matrix, int size) {
    for (int i = 0; i < size; i++) {
        cout << endl;
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
    }
    cout << endl << endl;
}

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    int size = atoi(argv[1]); // Size of the matrix is being taken as a command line argument
    const int numThreads = atoi(argv[2]); // Manually, the number of threads is set

    // The current time is used for seed for the random values being filled in the input matrix
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    // Generate and save the matrix to a file
    float** a = create_and_fill_matrix(size);
    save_matrix_to_file(a, size, "inverse_matrix_input.txt");

    freopen("INVERSE_MATRIX_OUTPUT.txt", "w", stdout);

    cout << "Original Matrix:" << endl;
    print_matrix(a, size);

    cout << "Inverse Matrix (Parallel):" << endl;
    float** inverse_parallel = generate_inverse_parallel(a, size, numThreads);
    print_matrix(inverse_parallel, size);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_time = end - start;

    std::cerr << "Execution time: " << elapsed_time.count() << " seconds" << std::endl;

    // Clean up and close the file
    delete_matrix(a, size);
    delete_matrix(inverse_parallel, size);

    return 0;
}    
