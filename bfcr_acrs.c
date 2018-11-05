/*
Created by:
 Bernardo Russo 
 Arthur Carlos 

Copyright © 2018 Russo Company. All rights reserved
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_RANDOM_INT 50
#define INSERTION_SORT 1
#define BUBBLE_SORT 2
#define SELECTION_SORT 3
#define MERGE_SORT 4
#define HEAP_SORT 5
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
void merge(int *inputArray, int esq, int meio, int dir)
{
    int i = esq;
    int j = meio + 1;
    int count;
    int aux[SIZE_OF_ARRAY];
    for (count = i; count < SIZE_OF_ARRAY; count++)
    {
        if (i >= meio + 1)
        {
            aux[count] = inputArray[j];
            j++;
        }
        else if (j >= dir + 1)
        {
            aux[count] = inputArray[i];
            i++;
        }
        else if (inputArray[i] < inputArray[j])
        {
            aux[count] = inputArray[i];
            i++;
        }
        else if (inputArray[j] <= inputArray[i])
        {
            aux[count] = inputArray[j];
            j++;
        }
    }
    for (count = esq; count <= dir; count++)
        inputArray[count] = aux[count];
}

void mergeSort(int *inputArray, int esq, int dir)
{
    if (dir <= esq)
        return;
    int meio = (esq + dir) / 2;
    mergeSort(inputArray, esq, meio);
    mergeSort(inputArray, meio + 1, dir);
    merge(inputArray, esq, meio, dir);
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

//Base Code
void printMenu()
{
    printf("Input the number corresponding to the sort you want to use:\n");
    printf("1 : Insertion Sort \n");
    printf("2 : Bubble Sort\n");
    printf("3 : Selection rootIndexSort\n");
    printf("4 : Merge Sort\n");
    printf("5 : Heap Sort\n");
    return;
}

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

int main()
{
    int arrayToSort[SIZE_OF_ARRAY];
    int choice;
    char useAnotherSort = 'y';
    while (useAnotherSort == 'y')
    {
        initializeArray(arrayToSort);
        printf("The array of random int is: ");
        printArray(arrayToSort);
        printMenu();
        printf("Enter your sort algorithm: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case INSERTION_SORT:
            insertionSort(arrayToSort);
            break;
        case BUBBLE_SORT:
            bubbleSort(arrayToSort);
            break;
        case SELECTION_SORT:
            selectionSort(arrayToSort);
            break;
        case MERGE_SORT:
            mergeSort(arrayToSort, 0, SIZE_OF_ARRAY);
            break;
        case HEAP_SORT:
            heapSort(arrayToSort, SIZE_OF_ARRAY);
            break;
        default:
            printf("Invalid input \n");
            printf("------------------------------------------------- \n");
            continue;
        }
        printf("The array is now sorted: ");
        printArray(arrayToSort);
        printf("\nTest another sort algorithm? (y/n): ");
        scanf(" %c", &useAnotherSort);
        printf("------------------------------------------------- \n");
    }

    return 0;
}