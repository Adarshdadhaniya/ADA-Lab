#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int *arr, int low, int high, int key, int *count)
{
     
    if (low > high)
        return -1;
   (*count)++;
    int mid = low + (high - low) / 2;
    if (arr[mid] == key)
        return mid;
    else if (arr[mid] < key)
        return binarySearch(arr, mid + 1, high, key, count);
    else
        return binarySearch(arr, low, mid - 1, key, count);
}

void main()
{
    srand(time(NULL));
    int count = 0;
    int x, size = 1, key = 0;

    FILE *fptr = fopen("binary.txt", "w");           // For step count
    FILE *finput = fopen("binary_input.txt", "w");   // For array and key info

    if (!fptr || !finput)
    {
        printf("File open error.\n");
        return;
    }

    while (size < 1000)
    {
        size *=2;
        
        fprintf(fptr, "%d\t", size);
        fprintf(finput, "Size: %d\nArray: ", size);

        int *arr = (int *)malloc(sizeof(int) * size);
        for (int i = 0; i < size; i++)
        {
            arr[i] = i + 1;
            fprintf(finput, "%d ", arr[i]);
        }

        // Best case: key is the middle element
        key = arr[size / 2 -1 ];
        if(size%2 !=0)
        key = arr[size / 2];
        count = 0;
        x = binarySearch(arr, 0, size - 1, key, &count);
        fprintf(fptr, "%d\t", count);
        fprintf(finput, "\nBest case key: %d\n", key);

        // Worst case: key is not present (e.g., value > max)
        key = arr[size - 1] + 10;
        count = 0;
        x = binarySearch(arr, 0, size - 1, key, &count);
        fprintf(fptr, "%d\n", count);
        fprintf(finput, "Worst case key: %d\n\n", key);

        free(arr);
    }

    fclose(fptr);
    fclose(finput);
}
