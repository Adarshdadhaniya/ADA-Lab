#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

// Generate worst-case input for merge sort
void genWorst(int arr[], int l, int r) {
    if (r - l + 1 <= 1)
        return;

    int n = r - l + 1;
    int mid = (n + 1) / 2;

    int left[mid], right[n - mid];
    int li = 0, ri = 0;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            left[li++] = arr[l + i];
        else
            right[ri++] = arr[l + i];
    }

    genWorst(left, 0, li - 1);
    genWorst(right, 0, ri - 1);

    for (int i = 0; i < li; i++)
        arr[l + i] = left[i];
    for (int i = 0; i < ri; i++)
        arr[l + li + i] = right[i];
}

// Merge function with comparison count
void merge(int a[], int b[], int c[], int blen, int clen) {
    int i = 0, j = 0, k = 0;
    while (i < blen && j < clen) {
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

// Merge sort implementation
void mergeSort(int A[], int n) {
    if (n < 2)
        return;

    int B[n / 2], C[n-n / 2];
    int k = 0, i = 0;

    for (i = 0; i < n / 2; i++)
        B[i] = A[i];
    int blen = i;

    while (i < n)
        C[k++] = A[i++];
    int clen = k;

    mergeSort(B, blen);
    mergeSort(C, clen);
    merge(A, B, C, blen, clen);
}

int main() {
    int *arr = NULL;
    FILE *fp = fopen("merge2.dat", "a");
    FILE *arrFile = fopen("merge_arrays.txt", "a");

    srand(time(NULL));

    for (int n = 4; n <= 1024; n *= 2) {
        arr = (int *)malloc(sizeof(int) * (n ));

        // -------- BEST CASE --------
        count = 0;
        for (int i = 0; i <= n; i++)
            arr[i] = i;

        fprintf(arrFile, "BEST CASE - Size: %d\nInput: ", n+1);
        for (int i = 0; i <= n; i++)
            fprintf(arrFile, "%d ", arr[i]);

        mergeSort(arr, n+1);

        fprintf(arrFile, "\nSorted: ");
        for (int i = 0; i <= n; i++)
            fprintf(arrFile, "%d ", arr[i]);
        fprintf(arrFile, "\n\n");

        fprintf(fp, "%d\t%d\t", n, count);

        // -------- WORST CASE --------
        count = 0;
        genWorst(arr, 0, n );

        fprintf(arrFile, "WORST CASE - Size: %d\nInput: ", n);
        for (int i = 0; i <= n; i++)
            fprintf(arrFile, "%d ", arr[i]);

        mergeSort(arr, n+1);

        fprintf(arrFile, "\nSorted: ");
        for (int i = 0; i <= n; i++)
            fprintf(arrFile, "%d ", arr[i]);
        fprintf(arrFile, "\n\n");

        fprintf(fp, "%d\n", count);

        free(arr);
    }

    fclose(fp);
    fclose(arrFile);
    return 0;
}
