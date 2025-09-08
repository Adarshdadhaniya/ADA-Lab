#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int insertionSort(int *arr, int n)
{
    int count = 0, flag = 0;
    for (int i = 1; i < n; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        if (arr[j] < temp)
            count++;
        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            count++;
        }
        // count++; // doubt between this line andline 19
        arr[j + 1] = temp;
    }
    return count;
}

void main()
{
    FILE *fp;
    srand(time(NULL));
    int count = 0, *arr = NULL;
    int size = 0;

    fp = fopen("ins.dat", "a");
    if (!fp)
    {
        printf("File open error.\n");
        return;
    }

    while (size < 1000)
    {
        size += 100;
        arr = (int *)malloc(size * sizeof(int));

        // Best case: ascending order
        for (int j = 0; j < size; j++)
            arr[j] = j + 1;
        count = insertionSort(arr, size);
        fprintf(fp, "%d\t%d\t", size, count);

        // Worst case: descending order
        for (int j = 0; j < size; j++)
            arr[j] = size - j;
        count = insertionSort(arr, size);
        fprintf(fp, "%d\n", count);

        free(arr);
    }

    fclose(fp);
}
