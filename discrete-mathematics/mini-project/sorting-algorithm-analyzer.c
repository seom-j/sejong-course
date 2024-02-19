#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <Windows.h>
#pragma warning(disable:4996)

int* copyArray(int* A, int* cpyA); int* createArray();
void swap(int* a, int* b); void reverseArrayInt(int* A);
void ready_ar(); void cpy_ar(); void sort();
void shellSortforMostlySortedArray(int* A); void forShellSortInsertionSort(int* A, int start, int end, int gap);
void bubbleSort(int* A); void selectionSort(int*); void insertionSort(int*);
void quickSort(int* A, int left, int right);
void mergeSort(int* A, int start, int end); void merge(int* A, int start, int middle, int end);
void heapSort(int* A); void heapify(int* A, int n, int i);

int n, * tmpArray;
int* origin_ar;
int* ar1, * ar2, * ar3;
int* cpy1, * cpy2, * cpy3;

int main() {
    // case1 : N = 10
    n = 10;
    origin_ar = createArray();
    ready_ar();
    printf("\n   %-13s%25s%25s%25s\n", "N = 10", "Random Array", "Mostly Sorted Array", "Inversely Sorted Array");
    sort();

    printf("\n------------------------------------------------------------------------------------------------------------\n");

    // case1 : N = 100
    n = 100;
    origin_ar = createArray();
    ready_ar();
    printf("\n   %-13s%25s%25s%25s\n", "N = 100", "Random Array", "Mostly Sorted Array", "Inversely Sorted Array");
    sort();

    printf("\n------------------------------------------------------------------------------------------------------------\n");
    // case1 : N = 10000
    n = 10000;
    origin_ar = createArray();
    ready_ar();
    printf("\n   %-13s%25s%25s%25s\n", "N = 10000", "Random Array", "Mostly Sorted Array", "Inversely Sorted Array");
    sort();
}

void sort() {
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    QueryPerformanceFrequency(&ticksPerSec);
    double time1, time2, time3;
    // 1. bubblesort
    cpy_ar();
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    bubbleSort(cpy1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    bubbleSort(cpy2);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    bubbleSort(cpy3);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;
    printf("   %-13s%23.6lfms%23.6lfms%23.6lfms\n", "BubbleSort", time1, time2, time3);

    // 2. selectionSort
    cpy_ar();
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    selectionSort(cpy1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    selectionSort(cpy2);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    selectionSort(cpy3);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;
    printf("   %-13s%23.6lfms%23.6lfms%23.6lfms\n", "SelectionSort", time1, time2, time3);

    // 3. insertionSort
    cpy_ar();
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    insertionSort(cpy1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    insertionSort(cpy2);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    insertionSort(cpy3);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;
    printf("   %-13s%23.6lfms%23.6lfms%23.6lfms\n", "InsertionSort", time1, time2, time3);

    // 4. heapSort
    cpy_ar();
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    heapSort(cpy1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    heapSort(cpy2);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    heapSort(cpy3);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;
    printf("   %-13s%23.6lfms%23.6lfms%23.6lfms\n", "HeapSort", time1, time2, time3);

    // 5. mergeSort
    tmpArray = (int*)calloc(n, sizeof(int)); // Temporary array initialization according to n
    cpy_ar();
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    mergeSort(cpy1, 0, n - 1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    mergeSort(cpy2, 0, n - 1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    mergeSort(cpy3, 0, n - 1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;
    printf("   %-13s%23.6lfms%23.6lfms%23.6lfms\n", "MergeSort", time1, time2, time3);

    // 6. quickSort
    cpy_ar();
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    quickSort(cpy1, 0, n - 1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    quickSort(cpy2, 0, n - 1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    quickSort(cpy3, 0, n - 1);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    time3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;
    printf("   %-13s%23.6lfms%23.6lfms%23.6lfms\n", "QuickSort", time1, time2, time3);
}



int* createArray() { // make random array
    srand(time(NULL));
    int* A = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) A[i] = rand() % n + 1;
    return A;
}

int* copyArray(int* A, int* cpyA) {
    for (int i = 0; i < n; i++) cpyA[i] = A[i];
    return cpyA;
}

void ready_ar() {
    ar1 = (int*)malloc(sizeof(int) * n);
    ar2 = (int*)malloc(sizeof(int) * n);
    ar3 = (int*)malloc(sizeof(int) * n);
    ar1 = copyArray(origin_ar, ar1);
    ar2 = copyArray(origin_ar, ar2);
    shellSortforMostlySortedArray(ar2); // make mostly sorted array
    ar3 = copyArray(origin_ar, ar3);
    bubbleSort(ar3);
    reverseArrayInt(ar3); // make inversely sorted array
}

void cpy_ar() {
    cpy1 = (int*)malloc(sizeof(int) * n);
    cpy2 = (int*)malloc(sizeof(int) * n);
    cpy3 = (int*)malloc(sizeof(int) * n);
    copyArray(ar1, cpy1);
    copyArray(ar2, cpy2);
    copyArray(ar3, cpy3);
}

void shellSortforMostlySortedArray(int* A) {
    int i, gap;
    for (gap = n / 2; gap > 0; gap = gap / 2) {
        if ((gap % 2) == 0) {
            gap++;// gap to odd
        }
        if (gap == 1) return; // to most sorted
        for (i = 0; i < gap; i++) {
            forShellSortInsertionSort(A, i, n - 1, gap);
        }
    }
}
void forShellSortInsertionSort(int* A, int first, int last, int gap) {
    int i, j, key;

    for (i = first + gap; i <= last; i = i + gap) {
        key = A[i];
        for (j = i - gap; j >= first && A[j] > key; j = j - gap) {
            A[j + gap] = A[j];
        }
        A[j + gap] = key;
    }
}

void reverseArrayInt(int* A) {
    for (int i = 0; i < n / 2; i++) swap(&A[i], &A[(n - 1) - i]);
}

void swap(int* a, int* b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
} // swap two integers
// auziliary function



void bubbleSort(int* A) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                swap(&A[j + 1], &A[j]);
            }
        }
    }
} // O(n^2)

void selectionSort(int* A) {
    int i, j, * min;
    for (i = 0; i < n - 1; i++) {
        min = &A[i];
        for (j = i + 1; j < n; j++) {
            if (*min > A[j]) {
                min = &A[j];
            } // find minimum address
        }
        swap(&A[i], min); // swap with i's index
    }
} // O(n^2)

void insertionSort(int* A) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = A[i];
        for (j = i - 1; j >= 0 && A[j] > key; j--) {
            A[j + 1] = A[j];
        }
        A[j + 1] = key;
    }
} // O(n^2)

void heapSort(int* A) { // Max Heap
    int i;
    for (i = (n / 2) - 1; i >= 0; i--) {
        heapify(A, n, i);
    }
    // Heap reconstruction by exchanging the maximum value located at the root with the last node
    // As the size of the heap is reduced, elements with higher values are taken sequentially
    for (i = n - 1; i > 0; i--) {
        swap(&A[0], &A[i]);
        heapify(A, i, 0); // heapify
    }
} // O(nlogn)
void heapify(int* A, int n, int i) {
    int parentNode = i;
    int leftChildNode = i * 2 + 1;
    int rightChildNode = i * 2 + 2;
    if (leftChildNode < n && A[parentNode] < A[leftChildNode]) {
        parentNode = leftChildNode;
    }
    if (rightChildNode < n && A[parentNode] < A[rightChildNode]) {
        parentNode = rightChildNode;
    }
    if (i != parentNode) {
        swap(&A[parentNode], &A[i]); // Douwn until the initial parent node is in place.
        heapify(A, n, parentNode);
    }
}

void mergeSort(int* A, int start, int end) {
    int middle;
    if (start < end) {
        middle = (start + end) / 2; // find middle index
        mergeSort(A, start, middle); // mergeSort (start ~ middle)
        mergeSort(A, middle + 1, end); // mergeSort (middle+1 ~ end)
        merge(A, start, middle, end); // merge
    }
} // O(nlogn)
void merge(int* A, int start, int middle, int end) {
    int i = start, j = middle + 1, k = start;
    while (i <= middle && j <= end) {
        if (A[i] <= A[j]) tmpArray[k++] = A[i++];
        else tmpArray[k++] = A[j++];
    } // assign from smallest number
    while (i <= middle) {
        tmpArray[k++] = A[i++];
    }
    while (j <= end) {
        tmpArray[k++] = A[j++];
    } // assign the remaining number
    for (int a = start; a <= end; a++) {
        A[a] = tmpArray[a];
    } // copy to original array
}

void quickSort(int* A, int left, int right) {
    int L = left, R = right;
    int pivotIdx = rand() % (R - L + 1) + L;
    swap(&A[(left + right) / 2], &A[pivotIdx]); // set random pivot to middle
    int pivot = A[(left + right) / 2];
    do {
        while (A[L] < pivot)
            L++;
        while (A[R] > pivot)
            R--;
        if (L <= R) {
            swap(&A[R], &A[L]);
            L++;
            R--;
        }
    } while (L <= R);
    /* recursion */
    if (left < R)
        quickSort(A, left, R);
    if (L < right)
        quickSort(A, L, right);
}// O(n^2) but guaranteed O(nlogn) if the pivot is random, so O(nlogn)
//sort function
