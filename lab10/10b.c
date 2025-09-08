#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
int graph[MAX][MAX];
int cnt = 0;

int minimum(int a, int b)
{
    return (a < b) ? a : b;
}

void floyd(int n)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            int T = graph[i][k];
            for (int j = 0; j < n; j++)
            {
                
                if (graph[i][j] > T + graph[k][j])
                {
                    graph[i][j] = minimum(graph[i][j], T + graph[k][j]);
                    cnt++;
                }
            }
        }
    }
}

void generateRandomGraph(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
            {
                int r = rand() % 4; // 1 out of 4 chance to be infinity
                if (r == 0)
                    graph[i][j] = 99;
                else
                    graph[i][j] = rand() % 20 + 1; // weights 1 to 20
            }
        }
    }
}

void printMatrix(int n)
{
    printf("All pair shortest distance matrix is:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", graph[i][j]);
        }
        printf("\n");
    }
}

void main()
{
    srand(time(NULL)); // Seed RNG once
    for (int n = 4; n <= 20; n += 1)
    {
        cnt = 0;
        printf("\n=== Graph with %d vertices ===\n", n);

        generateRandomGraph(n);

        printf("Initial graph:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                printf("%3d ", graph[i][j]);
            printf("\n");
        }

        floyd(n);

        printMatrix(n);

        printf("The count of updates for %d vertices is: %d\n", n, cnt);
    }
}
