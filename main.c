#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>


struct args {
    int *arg1;
    int arg2;
    int arg3;
};
int size = 0;

void merge(int arr[], int l, int m, int r);

void *arguments(void *args);

void *mergeSort(int arr[], int l, int r);

void printArray(int A[]);

int *readArray();

int main() {

    int *array = readArray();

    printf("Given array is \n");
    printArray(array);

    mergeSort(array, 0, size - 1);

    printf("\nSorted array is \n");
    printArray(array);

    return 0;
}

int *readArray() {
    char fname[100];
    printf("Enter file name: ");
    scanf("%s",&fname);
    FILE *fp = fopen(fname, "r");

    fscanf(fp, "%d\n", &size);
    int *array = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        fscanf(fp, "%d", &array[i]);
    }
    return array;
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;


    int L[n1], R[n2];       // temp arrays


    for (i = 0; i < n1; i++)        // copy data to temp arrays
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // merge the temp arrays back into array
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {        // copy the remaining elements of L[], if there are any
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2) {         // copy the remaining elements of R[], if there are any
        arr[k] = R[j];
        j++;
        k++;
    }
}


void *arguments(void *args) {
    struct args *arguments = args;
    mergeSort(arguments->arg1, arguments->arg2, arguments->arg3);
}

void *mergeSort(int arr[], int l, int r) {

    if (l < r) {
        int m = (l + r) / 2;
        struct args args1;
        args1.arg1 = arr;
        args1.arg2 = l;
        args1.arg3 = m;
        struct args args2;
        args2.arg1 = arr;
        args2.arg2 = m + 1;
        args2.arg3 = r;

        pthread_t th1;
        pthread_t th2;
        // Sort first and second halves
        pthread_create(&th1, NULL, &arguments, (void *) &args1);
        pthread_create(&th2, NULL, &arguments, (void *) &args2);


        pthread_join(th1, NULL);
        pthread_join(th2, NULL);
        merge(arr, l, m, r);
    }
}


void printArray(int A[]) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
