#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

using Matrix = vector<vector<double>>;

Matrix generate_matrix(int n) {
    Matrix mat(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = rand() % 10;
    return mat;
}

Matrix naive_multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix result(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

Matrix subtract(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix result(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}

Matrix strassen(const Matrix& A, const Matrix& B) {
    int n = A.size();
    if (n == 1)
        return {{A[0][0] * B[0][0]}};

    int s = n / 2;
    Matrix A11(s, vector<double>(s)), A12(s, vector<double>(s));
    Matrix A21(s, vector<double>(s)), A22(s, vector<double>(s));
    Matrix B11(s, vector<double>(s)), B12(s, vector<double>(s));
    Matrix B21(s, vector<double>(s)), B22(s, vector<double>(s));

    for (int i = 0; i < s; ++i)
        for (int j = 0; j < s; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + s];
            A21[i][j] = A[i + s][j];
            A22[i][j] = A[i + s][j + s];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + s];
            B21[i][j] = B[i + s][j];
            B22[i][j] = B[i + s][j + s];
        }

    Matrix M1 = strassen(add(A11, A22), add(B11, B22));
    Matrix M2 = strassen(add(A21, A22), B11);
    Matrix M3 = strassen(A11, subtract(B12, B22));
    Matrix M4 = strassen(A22, subtract(B21, B11));
    Matrix M5 = strassen(add(A11, A12), B22);
    Matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
    Matrix M7 = strassen(subtract(A12, A22), add(B21, B22));

    Matrix C(n, vector<double>(n));
    for (int i = 0; i < s; ++i)
        for (int j = 0; j < s; ++j) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + s] = M3[i][j] + M5[i][j];
            C[i + s][j] = M2[i][j] + M4[i][j];
            C[i + s][j + s] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }

    return C;
}

int main() {
    int n = 512;
    srand(time(nullptr));

    Matrix A = generate_matrix(n);
    Matrix B = generate_matrix(n);

    auto start_naive = high_resolution_clock::now();
    Matrix C_naive = naive_multiply(A, B);
    auto end_naive = high_resolution_clock::now();
    auto dur_naive = duration_cast<milliseconds>(end_naive - start_naive).count();
    cout << "Tiempo naive (C++): " << dur_naive << " ms" << endl;

    auto start_strassen = high_resolution_clock::now();
    Matrix C_strassen = strassen(A, B);
    auto end_strassen = high_resolution_clock::now();
    auto dur_strassen = duration_cast<milliseconds>(end_strassen - start_strassen).count();
    cout << "Tiempo Strassen (C++): " << dur_strassen << " ms" << endl;

    return 0;
}
