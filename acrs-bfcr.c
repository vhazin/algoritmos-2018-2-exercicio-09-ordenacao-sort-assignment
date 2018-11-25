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
#define QUICK_SORT_MID 7
#define SIZE_OF_ARRAY 10

//Insertion Sort
void insertionSort(int *inputArray)
{
    int i = 0, j = 0, chave;
    while (i < SIZE_OF_ARRAY - 1)//navege pelo array dado
    {
        chave = inputArray[i + 1];
        j = i;
        while (j >= 0 && inputArray[j] > chave)//equanto item for mnor que que a chave proximo item é trocado com item subsequente
        {
            inputArray[j + 1] = inputArray[j];
            j--;
        }
        inputArray[j + 1] = chave; //chave recebe o valor do proximo array a ser trabalhado
        i++;
    }
}

//Bubble Sort
void bubbleSort(int *inputArray)
{
    int i = 0, j = 0, temp;
    while (i < (SIZE_OF_ARRAY - 1))
    {
        for (j = 0; j < (SIZE_OF_ARRAY - i - 1); j++)//navega array
        {
            if (inputArray[j] > inputArray[j + 1])//caso o item seguinte seja maior que item anterior faz-se a troca dos valores.
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
    while (i < (SIZE_OF_ARRAY - 1))//faz varredura do array
    {
        min = i;//caso não se acha valor minimo no loop de procura a troca do array vai ocorrer com ele mesmo, não mudando nada na ordem.
        j = i + 1;
        while (j < SIZE_OF_ARRAY)
        {
            if (inputArray[j] < inputArray[min])//caso valor do item atual seja menor que valor dado ao item em analise grava-se esse item na variavel mim
            {
                min = j;
            }
            j++;
        }
        temp = inputArray[i];//faz a troca do item atual pelo item de valor minimo
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
    
    int L[n1], R[n2]; //define arrays temporarios para manipulação de items
    
    for (i = 0; i < n1; i++)//copia-se dados de array origem ao arrays temporarios
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    i = 0;//index da lista esquerda sub-array
    j = 0;//index da lista direita sub-array
    k = l;//index do array de output
    
    while (i < n1 && j < n2)//verifica se item da lista da esquerda é maior ou menor que item da lista esquerda, e insere na lista do output
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
    
    while (i < n1)//transfere items restantes na listas, como os items da esquerda são menores eles são passados primeiro para o array
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
        mergeSort(arr, l, m);//aplica mergeSort para partição inicial a partição final -- função vai ser chamada recursivamente até o l == m
        mergeSort(arr, m + 1, r);//aplica o mesmo para partição inferior, mesmo principio da recursão da primeira será aplicada a essa
        merge(arr, l, m, r);//faz a junção dos dos arrays, organizando os items
    }
}

//Heap Sort
void swapElements(int *inputArray, int index1, int index2)// faz troca de items
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
    int eixo = inputArray[high];//define eixo de comparação apartir do ultimo item da lista
    int i = low - 1;//define incio da lista a ser navegada
    for (int j = low; j <= high - 1; j++)//navega array
    {
        if (inputArray[j] <= eixo)//transfere todos os pontos do array menores que o eixo para a esquerda da posição do eixo no array
        {
            i++;
            swapElements(inputArray, i, j);
        }
    }
    swapElements(inputArray, i + 1, high);//caso o index do ultimo elemento navegado seja menor que o item passado como high, faz a troca dos dois
    return (i + 1);
}

void quickSort(int *inputArray, int low, int high)
{
    if (low < high)
    {
        int indexP = particao(inputArray, low, high); //particiona o array, passando para o indexP qual até que ponto andou o array na função partição.
        quickSort(inputArray, low, indexP - 1);//chama recursivamente a função aplicando aos items mais a esquerda do array
        quickSort(inputArray, indexP + 1, high);//chama recursivamente a função aplicando aos items mais a dirreita do array.
    }
}

// quick sort mid
int particaoMid(int *inputArray, int low, int high){
    int mid = (high+low)/2;//pega o index do meio do array
    int eixo= inputArray[mid];//coloca o eixo como item do meio do array
    int i = low -1;
    for (int j=low; j<=high-1; j++){//transfere todos os pontos do array menores que o eixo para a esquerda da posição do eixo no array
        if (inputArray[j]<=eixo){
            i++;
            swapElements(inputArray,i,j);
        }
    }
    swapElements(inputArray,i+1,high);
    return (i+1);
}
void quickSortMid(int *inputArray, int low, int high)
{
    if (low < high)
    {
        int indexP = particao(inputArray, low, high);
        quickSortMid(inputArray, low, indexP - 1);
        quickSortMid(inputArray, indexP + 1, high);
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
        case QUICK_SORT_MID:
            quickSortMid(inputArray, 0, SIZE_OF_ARRAY-1);
            algorithmName = "Quick Sort Mid";
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
    
    resetArray(arrayToSort, unsortedArray);
    executeSort(arrayToSort, QUICK_SORT_MID);
    
    printf("\nWith an array size of %d\n", SIZE_OF_ARRAY);
    return 0;
}
