#include <stdio.h>
#include <limits.h>
#include <omp.h>

int max(int x, int y) {
    return (x > y) ? x : y;
}

int minJumpsArray(int n, int arr[]) {
    int maxReach = arr[0], step = arr[0], jump = 1;
    if (n <= 1)
        return 0;

    if (arr[0] == 0)
        return INT_MAX;

    for (int i = 1; i < n; i++) {
        if (i == n - 1)
            return jump;

        maxReach = max(maxReach, i + arr[i]);
        step--;
        if (step == 0) {
            jump++;
            if (i >= maxReach)
                return INT_MAX;
            step = maxReach - i;
        }
    }
    return INT_MAX;
}

int findWinner(int n, int arr[][n]) {
    int path[2][n], dist[2];
    omp_set_num_threads(n);
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
//        printf("%d\n", omp_get_thread_num());
        path[0][i] = arr[i][i];
        path[1][i] = arr[i][n - i - 1];
    }

    omp_set_num_threads(2);
    #pragma omp parallel for
    for (int i = 0; i < 2; i++) {
//        printf("%d\n", omp_get_thread_num());
        dist[i] = minJumpsArray(n, path[i]);
    }

    if (dist[0] == dist[1])
        return 0;
    else if (dist[0] < dist[1])
        return 1;
    else
        return -1;
}

int main() {
    int n, ans;
    scanf("%d", &n);
    int arr[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);

    ans = findWinner(n, arr);
    if (ans == 0)
        printf("DRAW");
    else if (ans == 1)
        printf("SAM");
    else
        printf("JOHN");
    return 0;
}