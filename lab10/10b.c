// Auto-test Floyd–Warshall Algorithm with Random Graphs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 100
#define INF 99

static int graph[MAXN+1][MAXN+1];
static int ct;   // count of candidate updates

// Generate random weighted graph (1..20 or INF), diagonal = 0
void generateRandomGraph(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else {
                int r = rand() % 4; // 1 in 4 chance = INF
                if (r == 0)
                    graph[i][j] = 99;
                else
                    graph[i][j] = rand() % 20 + 1;
            }
        }
    }
}

// Modified Floyd–Warshall with counting
void floydWarshall(int n) {
    ct = 0;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            int temp = graph[i][k];
            for (int j = 1; j <= n; j++) {
                if (graph[i][j] > temp) {
                    ct++;
                    if (temp + graph[k][j] < graph[i][j]) {
                        graph[i][j] = temp + graph[k][j];
                    }
                }
            }
        }
    }
}

// ——— Manual Tester ———
void tester() {
    int n, i, j;
    printf("\nEnter number of vertices:\n");
    scanf("%d", &n);

    printf("\nEnter adjacency matrix (%d x %d):\n", n, n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &graph[i][j]);

    floydWarshall(n);

    printf("\nAll-pairs shortest path matrix is:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            printf("%3d ", graph[i][j]);
        printf("\n");
    }
    printf("The count for %d vertices is %d\n", n, ct);
}

// ——— Auto Plotter ———
void plotter() {
    FILE *fptr = fopen("floyd.txt", "a");
    if (!fptr) {
        printf("Error opening floyd.txt\n");
        return;
    }


    // Loop over sizes n = 4 … 20
    for (int n = 4; n <= 20; n++) {
        generateRandomGraph(n);
        floydWarshall(n);
        fprintf(fptr, "%d\t%d\n", n, ct);
    }

    fclose(fptr);
}

void main() {
    srand(time(NULL));
    tester();
    plotter();
}
