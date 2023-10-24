
 
 **Getting Started**:
 For the parallel programming tasks given i have used the parallel program library openmp.Starting with for all my programs the
 memory is being dynamically allocated to avoid the overflow issues for very big matrix and arrays.All the allocated the matrices 
 and array are being filled wiht random values while using the current time as seed for random number genrator.The input for each program
 is taken from command line with two inputs being taken one of them is size of matrix/array and number of threads.The allocated matrix 
 filled with random values is being writtten to a file which is "SUM_ARRAY_INPUT.txt" ,for sum_array "LU_DECOMPOSITION_MATRIX_INPUT.txt" 
 for lu_decomposition, "INVERSE_MATRIX_INPUT.txt" for inverse matrix.
 And all the programs output is written to   "INVERSE_MATRIX_OUTPUT.txt".All the input and output files are created if those files doesnt 
 exist everytime the program is compiled and if exists. "LU_DECOMPOSITION_MATRIX_OUTPUT.txt" 
 the data is read from those respective files.To compile every program (g++ -fopenmp -o (program_file_name) (program_file_name).cpp ) and 
 to execute the program (./(program_file_name) (size of the matrix/array) (number of threads)).Each of the program for performance 
 difference calculation between serial and parallel program,for serial program the program is being execueted on single thread and paralel 
 program is being executed on 40 threads.

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
```bash|43
g++ -fopenmp -o sum_array sum_array.cpp


## Parallel LU Decomposition

The `LU_DECOMPOSE` function performs LU decomposition of a square matrix `a` into lower triangular matrix `l` and upper triangular matrix `u`. This decomposition is done in parallel using OpenMP, enhancing the performance of the operation.

### Algorithm Overview

1. **Lock Initialization**: The function initializes an OpenMP lock to ensure thread safety within the parallel region.

2. **Parallel LU Decomposition**: The core LU decomposition process is parallelized. This allows multiple threads to process different columns of the matrix concurrently, improving efficiency.

3.**The LU decomposition can be mathematically described as follows**:

Start with the original matrix A.

Create L as a lower triangular matrix and U as an upper triangular matrix.

For each column and row of A, perform the following steps in a parallelized manner (as implemented in the code):

a. If j (column index) is less than i (row index), set L[j][i] to 0, as the lower triangular matrix should have zeros above its main diagonal.

b. If j is greater than or equal to i, set L[j][i] to A[j][i]. This involves copying the values from the original matrix A.

c. Subtract the appropriate values from L[j][i] by iterating over k from 0 to i. This step ensures that L contains the correct values below its main diagonal.

d. For the upper triangular matrix U, perform similar operations. If j is less than i, set U[i][j] to 0. If j is equal to i, set U[i][j] to 1. Otherwise, perform calculations that involve A[i][j], L[i][k], and U[k][j] to populate U.

e.Once the loop iterations are complete, you have successfully decomposed matrix A into the lower triangular matrix L and the upper triangular matrix U.

f.The final L and U matrices can be used for various numerical operations, such as solving systems of linear equations, matrix inversion, or other computations where triangular matrices are useful.

4. **Parallel Processing**: The function leverages OpenMP parallelization to distribute the computation of each column across multiple threads. This minimizes the computational load and improves performance, especially for large matrices.

The `LU_DECOMPOSE` function is particularly useful for applications that require LU decomposition of large matrices, such as solving systems of linear equations or numerical simulations. It takes advantage of multi-core processors to expedite the process.

**Note:** Make sure to compile your code with OpenMP support for parallel execution. See the [Getting Started](#getting-started) section in the README for details on compiling your code with OpenMP.

Screenshot for the performance difference between serial and parallel program for LU decomposition: https://imgur.com/S1jgnQt

## Parallel Matrix Inversion

The `generate_inverse_parallel` function is designed to compute the inverse of a square matrix using parallel processing, specifically with OpenMP. This function takes as input a square matrix `input_matrix` of size `size` and the number of `threads` to use for parallelization.

### Algorithm Overview


Algorithm Overview
The generate_inverse_parallel function is designed to efficiently compute the inverse of a square matrix, leveraging parallel processing capabilities to enhance performance. Below is a step-by-step explanation of the algorithm:

1.**Matrix Initialization**:

The function starts by initializing an identity matrix I of the same size as the input matrix. An identity matrix is a square matrix with ones on the main diagonal and zeros elsewhere.

2.**Row Pivoting**:
To ensure numerical stability and avoid division by zero, the code checks if the main diagonal element of the input matrix is zero. If it is, the code performs row pivoting by swapping the current row with the nearest subsequent row where the diagonal element is non-zero. This step is essential for a stable numerical process.

3.**Normalization**:
For each row, the function normalizes it by dividing the main diagonal element. This operation makes the diagonal elements equal to 1.0. The same scaling factor is applied to the corresponding row in the identity matrix I.

4.**Parallel Elimination for Zeroing Below the Diagonal**:
To eliminate values below the diagonal and make them zero, the function performs Gaussian elimination. For each non-diagonal row (row below the current row), a thread scales and subtracts the appropriate values from both the input matrix and the identity matrix I. Parallelization is achieved using OpenMP, with multiple threads concurrently processing different rows, taking full advantage of multi-core processors.

5.**Back Substitution for Zeroing Above the Diagonal**:
After eliminating values below the diagonal, the function performs back substitution to eliminate values above the diagonal. This step ensures that all elements of the input matrix A below and above the diagonal become zero.

6.**Return Inverse Matrix**:
The result is the inverse matrix, stored in I. The inverse matrix can be used for various numerical computations, including solving systems of linear equations and other applications that require matrix inversion.


**Note:** Make sure to compile your code with OpenMP support for parallel execution. See the [Getting Started](#getting-started) section in the README for details on compiling your code with OpenMP

Screenshot for the performance difference between serial and parallel program for Inversion of matrix: https://imgur.com/X2DOdYE


