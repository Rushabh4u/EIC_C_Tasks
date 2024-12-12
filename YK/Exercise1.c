#include <stdio.h>
#include <stdlib.h>

// Function to get the cofactor of a matrix
void getCofactor(int **matrix, int **temp, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // Copying only those elements that are not in the current row and column
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                // Row is filled, move to next row
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Recursive function to find determinant of matrix
int determinant(int **matrix, int n) {
    int det = 0; // Initialize result

    // Base case: if matrix contains single element
    if (n == 1)
        return matrix[0][0];

    int **temp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        temp[i] = (int *)malloc(n * sizeof(int));

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++) {
        // Getting Cofactor of matrix[0][f]
        getCofactor(matrix, temp, 0, f, n);
        det += sign * matrix[0][f] * determinant(temp, n - 1);
        sign = -sign; // Alternate sign
    }

    for (int i = 0; i < n; i++)
        free(temp[i]);
    free(temp);

    return det;
}

int main() {
    int n;
    printf("Enter the size of the matrix (n): ");
    scanf("%d", &n);

    // Dynamic memory allocation for the matrix
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)malloc(n * sizeof(int));

    // Input the matrix elements
    printf("Enter the elements of the %dx%d matrix:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }

    // Calculate determinant
    int det = determinant(matrix, n);
    printf("The determinant of the matrix is: %d\n", det);

    // Free allocated memory
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);

    return 0;
}

