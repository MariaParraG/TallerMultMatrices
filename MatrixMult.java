import java.util.Random;

public class MatrixMult {

    public static double[][] generateMatrix(int n) {
        double[][] mat = new double[n][n];
        Random rand = new Random();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = rand.nextInt(10);
        return mat;
    }

    public static double[][] naiveMultiply(double[][] A, double[][] B) {
        int n = A.length;
        double[][] C = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    public static double[][] add(double[][] A, double[][] B) {
        int n = A.length;
        double[][] result = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = A[i][j] + B[i][j];
        return result;
    }

    public static double[][] subtract(double[][] A, double[][] B) {
        int n = A.length;
        double[][] result = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = A[i][j] - B[i][j];
        return result;
    }

    public static double[][] strassenMultiply(double[][] A, double[][] B) {
        int n = A.length;
        if (n == 1) {
            return new double[][]{{A[0][0] * B[0][0]}};
        }

        int s = n / 2;
        double[][] A11 = new double[s][s], A12 = new double[s][s];
        double[][] A21 = new double[s][s], A22 = new double[s][s];
        double[][] B11 = new double[s][s], B12 = new double[s][s];
        double[][] B21 = new double[s][s], B22 = new double[s][s];

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

        double[][] M1 = strassenMultiply(add(A11, A22), add(B11, B22));
        double[][] M2 = strassenMultiply(add(A21, A22), B11);
        double[][] M3 = strassenMultiply(A11, subtract(B12, B22));
        double[][] M4 = strassenMultiply(A22, subtract(B21, B11));
        double[][] M5 = strassenMultiply(add(A11, A12), B22);
        double[][] M6 = strassenMultiply(subtract(A21, A11), add(B11, B12));
        double[][] M7 = strassenMultiply(subtract(A12, A22), add(B21, B22));

        double[][] C = new double[n][n];
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++) {
                C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
                C[i][j + s] = M3[i][j] + M5[i][j];
                C[i + s][j] = M2[i][j] + M4[i][j];
                C[i + s][j + s] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
            }

        return C;
    }

    public static void main(String[] args) {
        int n = 512;
        double[][] A = generateMatrix(n);
        double[][] B = generateMatrix(n);

        long startNaive = System.nanoTime();
        double[][] C_naive = naiveMultiply(A, B);
        long endNaive = System.nanoTime();
        System.out.printf("Tiempo naive (Java): %.2f ms%n", (endNaive - startNaive) / 1_000_000.0);

        long startStrassen = System.nanoTime();
        double[][] C_strassen = strassenMultiply(A, B);
        long endStrassen = System.nanoTime();
        System.out.printf("Tiempo Strassen (Java): %.2f ms%n", (endStrassen - startStrassen) / 1_000_000.0);
    }
}
