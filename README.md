
 
 Getting Started:
 For the parallel programming tasks given i have used the parallel program library openmp.Starting with for all my programs the
 memory is being dynamically allocated to avoid the overflow issues for very big matrix and arrays.All the allocated the matrices 
 and array are being filled wiht random values while using the current time as seed for random number genrator.The input for each program
 is taken from command line with two inputs being taken one of them is size of matrix/array and number of threads.The allocated matrix filled
 with random values is being writtten to a file which is "SUM_ARRAY_INPUT.txt" ,for sum_array "LU_DECOMPOSITION_MATRIX_INPUT.txt" for lu_decomposition, "INVERSE_MATRIX_INPUT.txt" for inverse matrix.
 And all the programs output is written to   "INVERSE_MATRIX_OUTPUT.txt".All the input and output files are created if those files doesnt exist everytime the program is compiled and if exists. "LU_DECOMPOSITION_MATRIX_OUTPUT.txt" 
 the data is read from those respective files.To compile every program (g++ -fopenmp -o (program_file_name) (program_file_name).cpp ) and to 
 execute the program (./(program_file_name) (size of the matrix/array) (number of threads)).Each of the program for performance difference caluclation 
 between serial and parallel program,for serial program the program is being execueted on single thread and paralel program is being executed on
 40 threads.

 ## Parallel Array Summation

The `sum_array` program is designed to compute the sum of an array in parallel using OpenMP. This program takes the size of the array and the number of threads to use as command-line arguments.

### Program Overview

1. **Array Initialization**: The program starts by creating an array of integers with random values. The array is filled with random values between 0 and 100.

2. **Array Saving**: It saves the generated array to a text file named "SUM_ARRAY_INPUT.txt"

3. **Parallel Summation**: The core of the program is parallelized using OpenMP. It uses a parallel loop to calculate the sum of the array elements concurrently. The result is stored in the `sum` variable.

4. **Execution Time Measurement**: The program measures the execution time using the C++ `<chrono>` library to determine the efficiency of the parallel computation.

5. **Clean-Up**: The dynamically allocated array is properly deallocated to prevent memory leaks.

6. **Result Display**: The final result, which is the sum of the array, is displayed on the console.
 
Screenshot for the performance difference between serial and parallel program for sum array:https://imgur.com/uQE0uB8

### Parallel Processing

The program utilizes OpenMP's parallelism to distribute the sum computation across multiple threads. This can significantly reduce the execution time for large arrays, making it suitable for applications that require fast summation of data.

**Note:** To compile and run the program with OpenMP support, you can use the following command:

g++ -fopenmp -o sum_array sum_array.cpp


## Parallel LU Decomposition

The `LU_DECOMPOSE` function performs LU decomposition of a square matrix `a` into lower triangular matrix `l` and upper triangular matrix `u`. This decomposition is done in parallel using OpenMP, enhancing the performance of the operation.

### Algorithm Overview

1. **Lock Initialization**: The function initializes an OpenMP lock to ensure thread safety within the parallel region.

2. **Parallel LU Decomposition**: The core LU decomposition process is parallelized. This allows multiple threads to process different columns of the matrix concurrently, improving efficiency.

3. **Lower Triangular Matrix (L)**: Within the parallel region, the function iterates through each column and row of the input matrix. If the current row index is less than the column index, it sets the corresponding value in the lower triangular matrix `l` to 0. Otherwise, it calculates the value by performing mathematical operations.

4. **Upper Triangular Matrix (U)**: Similarly, for the upper triangular matrix `u`, if the current row index is less than the column index, the value is set to 0. If they are equal, the value is set to 1. For other cases, mathematical operations are performed to determine the value.

5. **Parallel Processing**: The function leverages OpenMP parallelization to distribute the computation of each column across multiple threads. This minimizes the computational load and improves performance, especially for large matrices.

The `LU_DECOMPOSE` function is particularly useful for applications that require LU decomposition of large matrices, such as solving systems of linear equations or numerical simulations. It takes advantage of multi-core processors to expedite the process.

**Note:** Make sure to compile your code with OpenMP support for parallel execution. See the [Getting Started](#getting-started) section in the README for details on compiling your code with OpenMP.

Screenshot for the performance difference between serial and parallel program for LU decomposition: https://imgur.com/S1jgnQt

## Parallel Matrix Inversion

The `generate_inverse_parallel` function is designed to compute the inverse of a square matrix using parallel processing, specifically with OpenMP. This function takes as input a square matrix `input_matrix` of size `size` and the number of `threads` to use for parallelization.

### Algorithm Overview

1. **Matrix Initialization**: The function initializes an identity matrix `I` of the same size as the input matrix.

2. **Row Pivoting**: It performs row pivoting to ensure that the main diagonal of the input matrix contains non-zero values. If the main diagonal contains zeros, it swaps rows to bring a non-zero value to the diagonal. If no such value exists, it exits the function as an inverse does not exist.

3. **Normalization**: The function normalizes the rows by dividing the diagonal element. This ensures that the diagonal elements become 1.

4. **Parallel Elimination**: Parallelization is achieved by dividing the elimination process into multiple threads. For each non-diagonal row, a thread scales and subtracts the appropriate values from both the input matrix and the identity matrix. This process is done concurrently, taking advantage of multiple CPU cores.

5. **Back Substitution**: After eliminating values below the diagonal, the function performs back substitution to eliminate values above the diagonal.

6. **Return Inverse Matrix**: The final result is the inverse matrix, stored in `I`.

This function is designed to efficiently compute the inverse of a matrix, leveraging parallel processing capabilities to enhance performance. It is suitable for applications that require matrix inversion, such as linear algebra operations and solving systems of linear equations.

**Note:** Make sure to compile your code with OpenMP support for parallel execution. See the [Getting Started](#getting-started) section in the README for details on compiling your code with OpenMP

Screenshot for the performance difference between serial and parallel program for Inversion of matrix: https://imgur.com/X2DOdYE


