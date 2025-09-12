// Knapsac problem bottom up
#include <stdio.h>
#include <stdlib.h>

int maximum(int a, int b)
{
    int max = (a > b) ? a : b;
    return max;
}

void composition(int n, int wt, int weight[], int knap[][wt + 1])
{
    int num = 0;
    int subset[n];
    int i = n, j = wt;

    while (i != 0 && j != 0)
    {
        if (knap[i][j] != knap[i - 1][j])
        {
            subset[num++] = i;       // include item i
            j -= weight[i];          // reduce remaining capacity
        }
        i--; // move to previous item
    }

    printf("Composition is : ");
    for (int k = 0; k < num; k++)
        printf("%d ", subset[k]);
    printf("\n");
}


int knapsac(int wt, int weight[], int value[], int n)
{
    int i, j;
    int knap[n + 1][wt + 1];
    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= wt; j++)
        {
            if (i == 0 || j == 0)
                knap[i][j] = 0;
            else if (j < weight[i])
                knap[i][j] = knap[i - 1][j];
            else
                knap[i][j] = maximum(value[i] + knap[i - 1][j - weight[i]], knap[i - 1][j]);
            printf("%d ", knap[i][j]);
        }
        printf("\n");
    }
    printf("\nThe optimum knapsac value is: %d\n", knap[n][wt]);
    composition(n, wt, weight, knap);
}
int main()
{
    int n, capacity, *value, *weight;
    printf("\nEnter number of items:\n");
    scanf("%d", &n);
    value = (int *)malloc(n * sizeof(int));
    weight = (int *)malloc(n * sizeof(int));
    printf("Enter capacity: \n");
    scanf("%d", &capacity);
    printf("\nEnter the weight and value of each item:\n");
    printf("Weight Value\n");
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &weight[i], &value[i]);
    }
    knapsac(capacity, weight, value, n);
    free(value);
    free(weight);
    return 0;
}
/*
output
Enter number of items:
4
Enter capacity: 
5

Enter the weight and value of each item:
Weight Value
2 12
1 10
3 20
2 15
0 0 0 0 0 0 
0 0 12 12 12 12 
0 10 12 22 22 22 
0 10 12 22 30 32 
0 10 15 25 30 37 

The optimum knapsac value is: 37
Composition is : 4 2 1 
*/