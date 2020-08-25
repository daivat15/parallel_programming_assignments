#include <stdio.h>
#include <omp.h>

int recurse(int n, int row, int sum[], int arr[][n], int visited[][n]) {
    int count = 0, s, temp;

    for (int i = 0; i < n; ++i) {
        s = 0;
        for (int j = i; j < n; ++j) {
            if (row != 2 && visited[row][j])
                break;
            if (row == 2 && (visited[0][j] || visited[1][j]))
                break;

            if (row != 2)
                s += arr[row][j];
            else
                s += sum[j];
            if (s == 0) {
                #pragma omp parallel for
                for (int k = i; k <= j; ++k) {
                    if (row != 2)
                        visited[row][k] = 1;
                    else {
                        visited[0][k] = 1;
                        visited[1][k] = 1;
                    }
                }
                for (int l = 0; l < 3; ++l) {
                    temp = recurse(n, l, sum, arr, visited);
                    if (temp + 1 > count)
                        count = temp + 1;
                }
                #pragma omp parallel for
                for (int k = i; k <= j; ++k) {
                    if (row != 2)
                        visited[row][k] = 0;
                    else {
                        visited[0][k] = 0;
                        visited[1][k] = 0;
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    int n, count = 0, temp[3];
    scanf("%d", &n);
    int arr[2][n], sum[n], visited[3][2][n];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &arr[i][j]);
            visited[0][i][j] = 0;
            visited[1][i][j] = 0;
            visited[2][i][j] = 0;
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        sum[i] = arr[0][i] + arr[1][i];
    }

    #pragma omp parallel for
    for (int l = 0; l < 3; ++l) {
        temp[l] = recurse(n, l, sum, arr, visited[l]);
    }

    for (int i = 0; i < 3; ++i) {
        if (temp[i] > count)
            count = temp[i];
    }
    printf("%d\n", count);
    return 0;
}

