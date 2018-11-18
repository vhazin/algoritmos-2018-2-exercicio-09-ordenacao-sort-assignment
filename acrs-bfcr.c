/*
 Created by:
 Bernardo Russo
 Arthur Carlos
 
 Copyright © 2018 Russo Company. All rights reserved
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RANDOM_INT 500
#define INSERTION_SORT 1
#define BUBBLE_SORT 2
#define SELECTION_SORT 3
#define MERGE_SORT 4
#define HEAP_SORT 5
#define QUICK_SORT 6
#define SIZE_OF_ARRAY 10

//Insertion Sort
void insertionSort(int *inputArray)
{
    int i = 0, j = 0, chave;
    while (i < SIZE_OF_ARRAY - 1)
    {
        chave = inputArray[i + 1];
        j = i;
        while (j >= 0 && inputArray[j] > chave)
        {
            inputArray[j + 1] = inputArray[j];
            j--;
        }
        inputArray[j + 1] = chave;
        i++;
    }
}

//Bubble Sort
void bubbleSort(int *inputArray)
{
    int i = 0, j = 0, temp;
    while (i < (SIZE_OF_ARRAY - 1))
    {
        for (j = 0; j < (SIZE_OF_ARRAY - i - 1); j++)
        {
            if (inputArray[j] > inputArray[j + 1])
            {
                temp = inputArray[j];
                inputArray[j] = inputArray[j + 1];
                inputArray[j + 1] = temp;
            }
        }
        i++;
    }
}

//Selection Sort
void selectionSort(int *inputArray)
{
    int i = 0, j, min, temp;
    while (i < (SIZE_OF_ARRAY - 1))
    {
        min = i;
        j = i + 1;
        while (j < SIZE_OF_ARRAY)
        {
            if (inputArray[j] < inputArray[min])
            {
                min = j;
            }
            j++;
        }
        temp = inputArray[i];
        inputArray[i] = inputArray[min];
        inputArray[min] = temp;
        i++;
    }
}

//Merge Sort
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

//Heap Sort
void swapElements(int *inputArray, int index1, int index2)
{
    int temporary = inputArray[index1];
    inputArray[index1] = inputArray[index2];
    inputArray[index2] = temporary;
}

void heapfy(int *inputHeap, int rootIndex, int sizeOfHeap)
{
    int maxValueIndex = rootIndex; //initialize max value as the root value
    int leftChildIndex = 2 * rootIndex + 1;
    int rightChildIndex = 2 * rootIndex + 2;

    if ((leftChildIndex < sizeOfHeap) && (inputHeap[leftChildIndex] > inputHeap[maxValueIndex]))
    {
        maxValueIndex = leftChildIndex;
    }

    if ((rightChildIndex < sizeOfHeap) && (inputHeap[rightChildIndex] > inputHeap[maxValueIndex]))
    {
        maxValueIndex = rightChildIndex;
    }

    if (maxValueIndex != rootIndex)
    {
        swapElements(inputHeap, rootIndex, maxValueIndex);
        heapfy(inputHeap, maxValueIndex, sizeOfHeap);
    }
}

void buildMaxHeap(int *inputArray, int sizeOfArray)
{
    for (int i = sizeOfArray / 2 - 1; i >= 0; i--)
    {
        heapfy(inputArray, i, sizeOfArray);
    }
}

void heapSort(int *inputArray, int sizeOfArray)
{
    buildMaxHeap(inputArray, sizeOfArray);
    for (int i = sizeOfArray - 1; i >= 0; i--)
    {
        swapElements(inputArray, 0, i);
        heapfy(inputArray, 0, i);
    }
}

// quick sort
int particao(int *inputArray, int low, int high)
{
    int eixo = inputArray[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (inputArray <= eixo)
        {
            i++;
            swapElements(inputArray, i + 1, j);
        }
    }
    swapElements(inputArray, i + 1, high);
    return (i + 1);
}

void quickSort(int *inputArray, int low, int high)
{
    if (low < high)
    {
        int indexP = particao(inputArray, low, high);
        quickSort(inputArray, low, indexP - 1);
        quickSort(inputArray, indexP + 1, high);
    }
}

//Base Code
int randInt()
{
    return rand() % (MAX_RANDOM_INT + 1);
}

void printArray(int *inputArray)
{
    printf("\n");
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
    {
        if (i < (SIZE_OF_ARRAY - 1)) //this is used to not print "," on the last element
        {
            printf("%d ", inputArray[i]);
        }
        else
        {
            printf("%d\n", inputArray[i]);
        }
    }
}

void initializeArray(int *inputArray)
{
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
    {
        inputArray[i] = randInt();
    }
}

void resetArray(int *array1, int *array2)
{
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
        array1[i] = array2[i];
}

void executeSort(int *inputArray, int sortAlgorithm)
{

    clock_t begin = clock();
    char *algorithmName = "";
    switch (sortAlgorithm)
    {
    case INSERTION_SORT:
        insertionSort(inputArray);
        algorithmName = "Insertion Sort";
        break;
    case BUBBLE_SORT:
        bubbleSort(inputArray);
        algorithmName = "Bubble Sort";
        break;
    case SELECTION_SORT:
        selectionSort(inputArray);
        algorithmName = "Selection Sort";
        break;
    case MERGE_SORT:
        mergeSort(inputArray, 0, SIZE_OF_ARRAY);
        algorithmName = "Merge Sort";
        break;
    case HEAP_SORT:
        heapSort(inputArray, SIZE_OF_ARRAY);
        algorithmName = "Heap Sort";
        break;
    case QUICK_SORT:
        quickSort(inputArray, 0, SIZE_OF_ARRAY - 1);
        algorithmName = "Quick Sort";
        break;
    default:
        printf("Invalid input \n");
        printf("------------------------------------------------- \n");
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nWith %s method the execution time was: %f\n", algorithmName, time_spent);
    printf("The array is now sorted: ");
    printArray(inputArray);
}

int main()
{
    int unsortedArray[SIZE_OF_ARRAY];
    int arrayToSort[SIZE_OF_ARRAY];
    initializeArray(unsortedArray);
    printf("The array of random int is: ");
    printArray(unsortedArray);

    resetArray(arrayToSort, unsortedArray);
    executeSort(arrayToSort, INSERTION_SORT);

    resetArray(arrayToSort, unsortedArray);
    executeSort(arrayToSort, BUBBLE_SORT);

    resetArray(arrayToSort, unsortedArray);
    executeSort(arrayToSort, SELECTION_SORT);

    resetArray(arrayToSort, unsortedArray);
    executeSort(arrayToSort, MERGE_SORT);

    resetArray(arrayToSort, unsortedArray);
    executeSort(arrayToSort, HEAP_SORT);

    resetArray(arrayToSort, unsortedArray);
    executeSort(arrayToSort, QUICK_SORT);

    printf("\nWith an array size of %d\n", SIZE_OF_ARRAY);
    return 0;
}
