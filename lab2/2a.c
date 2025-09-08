#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int linearSearch(int* arr, int key, int len){
    int count = 0;
    for(int i = 0; i < len; i++){
        count++;
        if(arr[i] == key) return count;
    }
    return count;
}

void main(){
    srand(time(NULL));
    int x, size = 1;
    FILE* fptr = fopen("linear.txt", "a");          // Performance file
    FILE* farr = fopen("linear_input.txt", "a");    // Array + key log file

    if (!fptr || !farr) {
        printf("Error opening files.\n");
        return;
    }

    while(size <= 10000){
        size *= 10;
        fprintf(fptr, "%d\t", size);
        fprintf(farr, "Size: %d\nArray: ", size);

        int *arr = (int *)malloc(sizeof(int) * size);
        for(int i = 0; i < size; i++) {
            arr[i] = rand() % 1000;
            fprintf(farr, "%d ", arr[i]);
        }

        // Best case
        int key_best = arr[0];
        x = linearSearch(arr, key_best, size);
        fprintf(fptr, "%d\t", x);
        fprintf(farr, "\nBest case key: %d\n", key_best);

        // Worst case
        int key_worst = arr[size];
        x = linearSearch(arr, key_worst, size);
        fprintf(fptr, "%d\n", x);
        fprintf(farr, "Worst case key: %d\n\n", key_worst);

        free(arr);
    }

    fclose(fptr);
    fclose(farr);
}
