# matrixMult
C program that multiplies two sets of matrices together and prints the results. Implemented using p-threads multithreading where each thread computes one element of the product. This was my 5th lab assignment for the Operating Systems class at CSU Channel Islands.

## Prerequisites
This program is designed to be run on Linux. 

## Getting Started
Open up the matrixMult folder in terminal. To compile:
```
cd cmake-build-debug
cmake ..
make
```

To run:
```
cd bin
./matrixMult in.txt
```

## Configuration
If you would like to multiply different matrices you must edit in.txt which is located in the bin folder. The first line of the file should be `m n k` where `m x n` are the dimensions of matrix A1, `n x k` are the dimensions of matrix B1, and `m x k` are the dimensions of the resulting matrix A1 x B1. The dimensions are written as `numRows x numColumns`.

Enter the matrices on the following lines seperating each number by spaces and with each row on a new line. Enter a blank line and then follow the same format for matrices A2 and B2.

### Example
The following example of an in.txt file multiplies matrix A1 with dimensions `2 x 4` times matrix B1 with dimensions `4 x 3`, then matrix A2 with dimensions `1 x 5` times matrix B2 with dimensions `5 x 1`
```
2 4 3 
1 4 6 10
2 7 5 3
1 4 6
2 7 5
9 0 11
3 1 0

1 5 1
1 2 3 4 5
1
2
3
4
5 
```

## What I learned
I learned how to use pthreads, specifically writing a method that acts as a thread. I also learned how to allocate the appropriate data structures, pass them to methods, and how to join the threads after computation.

## Acknowledgements
The basic structure of this program was created by Dr. Bieszczad for COMP 362 Operating Systems at CSU Channel Islands. He also answered many of my questions as I worked on the project.
