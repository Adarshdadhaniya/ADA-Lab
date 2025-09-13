


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

// Generates worst-case for merge sort by interleaving elements
void genWorst(int arr[], int n)    //here n is the size
{
    if (n <= 1)
        return;

    int mid = n / 2;
    int *left = (int *)malloc((n-mid) * sizeof(int));
    int *right = (int *)malloc((mid) * sizeof(int));
    int j=0,k=0,l=0;
    // Pick alternate elements for left and right
    for (int i = 0; i < n; i++){
    if(i%2==0)
        left[j++] = arr[i];
    else
        right[k++] = arr[i];
    }
    genWorst(left, n-mid);
    genWorst(right, mid);

    // Combine left and right back into arr
    for (int i = 0; i <n- mid; i++)
      arr[l++] = left[i];
    for (int i = 0; i < mid; i++)
        arr[l++] = right[i];

    free(left);
    free(right);
}

void merge(int a[], int b[], int c[], int blen, int clen)
{
    int i = 0, j = 0, k = 0;
    while (i < blen && j < clen)
    {
        count++;
        if (b[i] <= c[j])
            a[k++] = b[i++];
        else
            a[k++] = c[j++];
        
    }
    while (i < blen)
        a[k++] = b[i++];
    while (j < clen)
        a[k++] = c[j++];
}

void mergeSort(int A[], int n)
{
    if (n <= 1)
        return;

    int mid = n / 2;
    int *B = (int *)malloc(mid * sizeof(int));
    int *C = (int *)malloc((n - mid) * sizeof(int));
    int i=0;
    for (int j = 0; j < mid; j++)
        B[j] = A[i++];
    for (int j = 0; j < n-mid; j++)
        C[j] = A[i++];

    mergeSort(B, mid);
    mergeSort(C, n - mid);
    merge(A, B, C, mid, n - mid);

    free(B);
    free(C);
}

int main()
{
    int *arr = NULL;
    srand(time(NULL));
    FILE *fp = fopen("merge.txt", "w");
    FILE *arrFile = fopen("merge_arrays.txt", "w");

    if (fp == NULL)
    {
        printf("File open error!\n");
        return 1;
    }
    for (int n = 2; n <= 1024; n *= 2)
    {
        arr = (int *)malloc(sizeof(int) * n);

        // best
        count = 0;
        for (int i = 0; i < n; i++)
            arr[i] = i;
        fprintf(arrFile, "BEST CASE - Size: %d\nInput: ", n+1);
        for (int i = 0; i < n; i++)
            fprintf(arrFile, "%d ", arr[i]);
        fprintf(arrFile,"\n");
        mergeSort(arr, n);
        fprintf(arrFile, "BEST CASE - Size: %d\nOutput: ", n+1);
        for (int i = 0; i < n; i++)
            fprintf(arrFile, "%d ", arr[i]);
        fprintf(arrFile,"\n");
        fprintf(fp, "%d\t%d\t", n, count);

        // worst
        count = 0;
        for (int i = 0; i < n; i++)
            arr[i] = i;
        genWorst(arr, n);// Pass size, not indices
        fprintf(arrFile, "Worst CASE - Size: %d\nInput: ", n+1);
        for (int i = 0; i < n; i++)
            fprintf(arrFile, "%d ", arr[i]);
        fprintf(arrFile,"\n"); 
        mergeSort(arr, n);
        fprintf(arrFile, "Worst CASE - Size: %d\nOutput: ", n+1);
        for (int i = 0; i < n; i++)
            fprintf(arrFile, "%d ", arr[i]);
        fprintf(arrFile,"\n");
        fprintf(fp, "%d\n", count);

        free(arr);
    }
    fclose(fp);
    return 0;
}