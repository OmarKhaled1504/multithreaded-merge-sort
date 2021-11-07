#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>

int i = 0;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;


    int L[n1], R[n2];       // temp arrays


    for (i = 0; i < n1; i++)        // copy data to temp arrays
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // merge the temp arrays back into arr
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

void *mergeSort(int arr[], int l, int r, pthread_t *tharr) {
    printf("alo2");
    if (l < r) {

        int m = (l + r) / 2;

        // Sort first and second halves

        pthread_create(tharr+(i++), NULL, mergeSort(arr, l, m, tharr), NULL);
        pthread_create(tharr+(i++), NULL, mergeSort(arr, m + 1, r, tharr), NULL);
        for (int j = 0; j < i; j++)
            pthread_join(tharr[j], NULL);

        merge(arr, l, m, r);
    }
}

void *routine() {

    printf("hello\n");
    sleep(3);
    printf("bye\n");
}
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
int main() {
//    int n;
//    scanf("%d", &n);
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    pthread_t *tharr = (pthread_t *) malloc(arr_size * sizeof(pthread_t));

    printf("Given array is \n");
    printArray(arr, arr_size);
    printf("alo1");
    mergeSort(arr, 0, arr_size - 1,tharr);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);

    return 0;
}
