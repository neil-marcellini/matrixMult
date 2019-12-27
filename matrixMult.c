/**
* Name: Neil Marcellini
* Lab/task: Lab 5
* Date: 09/30/19
**/
#include "matrixMult.h"

int main(int argc, char *argv[])
{
    if (freopen(argv[1], "r", stdin) == 0)
        oops("Cannot open the input file.\n", -1);

    int **a1, **b1, **c1, **a2, **b2, **c2; // matrices
    int m1, k1, n1, m2, k2, n2; // dimensions of the matices m x k and k x n

    allocateAndLoadMatrices(&a1, &b1, &c1, &m1, &k1, &n1);
    allocateAndLoadMatrices(&a2, &b2, &c2, &m2, &k2, &n2);

    // the real magic happens in there

    // TODO: implement
    pthread_t **tids1, **tids2;
    tids1 = multiply(a1, b1, c1, m1, k1, n1);
    join(tids1, m1, n1);
    free_tids(tids1, m1);
    tids2 = multiply(a2, b2, c2, m2, k2, n2);
    join(tids2, m2, n2);
    free_tids(tids2, m2);



    // dispaly results of matrix multiplication

    printf("\nMATRIX A1\n");
    displayMatrix(a1, m1, k1);
    freeMatrix(a1, m1);
    printf("\nMATRIX B1\n");
    displayMatrix(b1, k1, n1);
    freeMatrix(b1, k1);
    printf("\nMATRIX A1 x B1\n");
    displayMatrix(c1, m1, n1);
    freeMatrix(c1, m1);

    printf("\nMATRIX A2\n");
    displayMatrix(a2, m2, k2);
    freeMatrix(a2, m2);
    printf("\nMATRIX B2\n");
    displayMatrix(b2, k2, n2);
    freeMatrix(b2, k2);
    printf("\nMATRIX A2 x B2\n");
    displayMatrix(c2, m2, n2);
    freeMatrix(c2, m2);

    return 0;
}

void *matrixThread(void *param)
{
    // map the parameter onto the structure
    MATRIX_CELL *cell = (MATRIX_CELL *)param;

    // TODO: implement
    //individual thread here

    int stepr;
    // k = length of row/col
    for(stepr = 0; stepr < cell->k; stepr++) {
        cell->c[cell->i][cell->j] += (cell->a[cell->i][stepr]) *(cell->b[stepr][cell->j]);
    }

    //end todo

    free(cell);

    return NULL;
}

void allocateAndLoadMatrices(int ***a, int ***b, int ***c, int *m, int *k, int *n)
// takes pointers to two-dimensional matrices, so they can be allocated in here
// and used by the caller
{
    if (scanf("%d %d %d", m, k, n) == 0)
        oops("Cannot read matrix sizes.\n", -2);

    // TODO: implement
    int i;
    //mxk
    (*a) = (int **) malloc(*m * sizeof(int *));
    for (i = 0; i < *m; i++) {
        (*a)[i] = (int *) malloc(*k * sizeof(int));
    }

    // k x n
    (*b) = (int **) malloc(*k * sizeof(int *));
    for (i = 0; i < *k; i++) {
        (*b)[i] = (int *) malloc(*n * sizeof(int));
    }
    // mxn
    (*c) = (int **) malloc(*m * sizeof(int *));
    for (i = 0; i < *m; i++) {
        (*c)[i] = (int *) malloc(*n * sizeof(int));
    }

    loadMatrix(a,*m,*k);
    loadMatrix(b,*k,*n);
}

void loadMatrix(int ***matrix, int m, int n)
{
    // TODO: implement
    // load input into matrix
    // m lines of k numbers for each matrix

    // loop through matrix and scanf data

    int i;
    int j;
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            if(scanf("%d", &(*matrix)[i][j]) == 0) {
                oops("Cannot read matrix input data.\n", -2);
            }
        }
    }

}

void freeMatrix(int **matrix, int m)
{
    // TODO: implement
    int i;
    for (i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);

}

pthread_t **multiply(int **a, int **b, int **c, int m, int k, int n)
{
    pthread_t **tids = alloc_tids(m, n);


    // TODO: implement
    // creation of threads here, organizing multiplication
    int i;
    int j;
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            MATRIX_CELL *data = (MATRIX_CELL *) malloc(sizeof(MATRIX_CELL));
            data->a = a;
            data->b = b;
            data->c = c;
            data->i = i;
            data->j = j;
            data->k = k;
            pthread_create(&tids[i][j], NULL, matrixThread, (void *) data);
        }

    }

    return tids;
}

pthread_t **alloc_tids(int m, int n)
{
    pthread_t **tids;

    // TODO: implement
    // allocate tids array
    int i;
    tids = (pthread_t **) malloc(m * sizeof(pthread_t *));
    for (i = 0; i < m; i++)
        tids[i] = (pthread_t *) malloc(n * sizeof(pthread_t));

    return tids;
}

void free_tids(pthread_t **tids, int m)
{
    // TODO: implement
    int i;
    for (i = 0; i < m; i++) {
        free(tids[i]);
    }
    free(tids);
}

void join(pthread_t **tids, int m, int n)
{
    // TODO: implement
    int i;
    int j;
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            pthread_join(tids[i][j], NULL);
        }
    }

}

void displayMatrix(int **matrix, int m, int n)
{
    // TODO: implement
    int i;
    int j;
    for (i = 0; i <  m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
