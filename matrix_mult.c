#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double** alloc_matrix(int n) {
    double** mat = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
        mat[i] = calloc(n, sizeof(double));
    return mat;
}

void free_matrix(double** mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void fill_random(double** mat, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 10;
}

void naive_multiply(int n, double** A, double** B, double** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void add_matrix(double** A, double** B, double** result, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
}

void sub_matrix(double** A, double** B, double** result, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
}

void strassen(double** A, double** B, double** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int s = n / 2;
    double **A11 = alloc_matrix(s), **A12 = alloc_matrix(s), **A21 = alloc_matrix(s), **A22 = alloc_matrix(s);
    double **B11 = alloc_matrix(s), **B12 = alloc_matrix(s), **B21 = alloc_matrix(s), **B22 = alloc_matrix(s);
    double **M1 = alloc_matrix(s), **M2 = alloc_matrix(s), **M3 = alloc_matrix(s), **M4 = alloc_matrix(s);
    double **M5 = alloc_matrix(s), **M6 = alloc_matrix(s), **M7 = alloc_matrix(s);
    double **temp1 = alloc_matrix(s), **temp2 = alloc_matrix(s);

    for (int i = 0; i < s; i++)
        for (int j = 0; j < s; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + s];
            A21[i][j] = A[i + s][j];
            A22[i][j] = A[i + s][j + s];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + s];
            B21[i][j] = B[i + s][j];
            B22[i][j] = B[i + s][j + s];
        }

    add_matrix(A11, A22, temp1, s); add_matrix(B11, B22, temp2, s); strassen(temp1, temp2, M1, s);
    add_matrix(A21, A22, temp1, s); strassen(temp1, B11, M2, s);
    sub_matrix(B12, B22, temp2, s); strassen(A11, temp2, M3, s);
    sub_matrix(B21, B11, temp2, s); strassen(A22, temp2, M4, s);
    add_matrix(A11, A12, temp1, s); strassen(temp1, B22, M5, s);
    sub_matrix(A21, A11, temp1, s); add_matrix(B11, B12, temp2, s); strassen(temp1, temp2, M6, s);
    sub_matrix(A12, A22, temp1, s); add_matrix(B21, B22, temp2, s); strassen(temp1, temp2, M7, s);

    for (int i = 0; i < s; i++)
        for (int j = 0; j < s; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + s] = M3[i][j] + M5[i][j];
            C[i + s][j] = M2[i][j] + M4[i][j];
            C[i + s][j + s] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }

    free_matrix(A11, s); free_matrix(A12, s); free_matrix(A21, s); free_matrix(A22, s);
    free_matrix(B11, s); free_matrix(B12, s); free_matrix(B21, s); free_matrix(B22, s);
    free_matrix(M1, s); free_matrix(M2, s); free_matrix(M3, s); free_matrix(M4, s);
    free_matrix(M5, s); free_matrix(M6, s); free_matrix(M7, s);
    free_matrix(temp1, s); free_matrix(temp2, s);
}

int main() {
    int n = 512;
    srand(time(NULL));

    double** A = alloc_matrix(n);
    double** B = alloc_matrix(n);
    double** C = alloc_matrix(n);

    fill_random(A, n);
    fill_random(B, n);

    clock_t start = clock();
    naive_multiply(n, A, B, C);
    clock_t end = clock();
    printf("Tiempo naive (C): %.2f ms\n", 1000.0 * (end - start) / CLOCKS_PER_SEC);

    clock_t start2 = clock();
    strassen(A, B, C, n);
    clock_t end2 = clock();
    printf("Tiempo Strassen (C): %.2f ms\n", 1000.0 * (end2 - start2) / CLOCKS_PER_SEC);

    free_matrix(A, n); free_matrix(B, n); free_matrix(C, n);
    return 0;
}
