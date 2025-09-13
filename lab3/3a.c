#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int selectionSort(int *arr, int n)
{
    int min = 0, count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            count++;
            if (arr[min] > arr[j])
                min = j;
        }
        swap(&arr[min], &arr[i]);
    }
    return count;
}
void main()
{
    FILE *fp;
    int count = 0;
    int size = 0;
    int *arr = NULL;

    fp = fopen("sel.dat", "w");
    if (!fp)
    {
        printf("Error opening file.\n");
        return;
    }

    size = 0;
    while (size < 1000)
    {
        size += 100;
        arr = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
            arr[j] = j + 1;  // Consecutive numbers: 1, 2, 3, ..., size

        count = selectionSort(arr, size);
        fprintf(fp, "%d\t%d\n", size, count);

        free(arr);
    }

    fclose(fp);
}
