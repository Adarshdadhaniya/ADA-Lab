#include<stdio.h>
#include<stdlib.h>

void swap(int *x, int* y){
    int temp=*x;
    *x=*y;
    *y=temp;
}

int bubbleSort(int* arr, int n){
    int count=0, flag=0;
    for(int i=0; i<n-1; i++){
        flag=0;
        for(int j=0; j<n-i-1; j++){
            count++;
            if(arr[j]>arr[j+1]) {
                flag=1;
                swap(&arr[j],&arr[j+1]);
            }
        }
        if(flag==0) return count;
        
    }
    return count;
}

void main()
{
    FILE *fp;
    int count = 0, *arr = NULL;
    int size = 0;

    fp = fopen("bubble.dat", "a");
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

        // Best case: already sorted ascending
        for (int j = 0; j < size; j++)
            arr[j] = j + 1;
        count = bubbleSort(arr, size);
        fprintf(fp, "%d\t%d\t", size, count);

        // Worst case: sorted in descending order
        for (int j = 0; j < size; j++)
            arr[j] = size - j;
        count = bubbleSort(arr, size);
        fprintf(fp, "%d\n", count);

        free(arr);
    }

    fclose(fp);
}
