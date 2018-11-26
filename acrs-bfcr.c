/*
 Created by:
 Bernardo Russo
 Arthur Carlos
 
 Copyright © 2018 Russo Company. All rights reserved
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_RANDOM_INT 500
#define INSERTION_SORT 1
#define BUBBLE_SORT 2
#define SELECTION_SORT 3
#define MERGE_SORT 4
#define HEAP_SORT 5
#define QUICK_SORT 6
#define QUICK_SORT_MID 7
#define SIZE_OF_ARRAY 5

//Insertion Sort
void insertionSort(int *inputArray)
{
    /*
    Insertion sort pega um pivo que inicialmente está em 0 e verifica todos os valores antes dele até encontrar um menor e coloca
    o pivo logo depois dele. Faz isso para todos os elementos
    */
    int i = 0, j = 0, chave; //insertion sort tem um "marcador" cujo VALOR nesse marcador é chamado de chave, começa no segundo elemento e vai até o último
    while (i < SIZE_OF_ARRAY - 1) //com i de 0 até o penúltimo valor (já que vai ser comparado par a par com o seguinte)
    {
        chave = inputArray[i + 1]; //observe que o útimo valor a ser a chave vai ser o último valor do array
        
        j = i; //loop de j index do valor antes da chave até o primeiro valor do array
        while (j >= 0 && inputArray[j] > chave) //equanto o valor inputArray[j] for maior que a chave e o início do array não foi atingido.. 
        {
            inputArray[j + 1] = inputArray[j]; //troca o valor nas posições inputArray[j + 1] e inputArray[j]
            j--;
        }
        inputArray[j + 1] = chave; //chave agora será o valor seguinte do array, e é repetido o procedimento
        i++;
    }
}

//Bubble Sort
void bubbleSort(int *inputArray)
{
    /*
    bubbleSort compara par a par os elementos do array, trocando caso o segundo seja menor. Executando isso N vezes
    */
    int i = 0, j = 0, temp;
    while (i < (SIZE_OF_ARRAY - 1))
    {
        for (j = 0; j < (SIZE_OF_ARRAY - i - 1); j++) //de j = 0 até o na posição final menos i ( valores acima da posição i já vão estar organizados )
        {
            if (inputArray[j] > inputArray[j + 1]) //compara os valores do array par a par até chegar o par na posição i-1 e i. Se o valor em j for menor, troca de posição com o j + 1
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
    /*
    Selection sort tem verifica qual o menor valor no array após o pivo e troca com ele, depois incrementa o pivo.
    */
    int i = 0, j, min, temp;
    while (i < (SIZE_OF_ARRAY - 1)) //faz varredura do array
    {
        min = i; //caso não se acha valor minimo no loop de procura a troca do array vai ocorrer com ele mesmo, não mudando nada na ordem.
        j = i + 1;
        while (j < SIZE_OF_ARRAY)
        {
            if (inputArray[j] < inputArray[min]) //caso valor do item atual seja menor que valor dado ao item em analise grava-se esse item na variavel mim
            {
                min = j;
            }
            j++;
        }
        temp = inputArray[i]; //faz a troca do item atual pelo item de valor minimo
        inputArray[i] = inputArray[min];
        inputArray[min] = temp;
        i++;
    }
}

//Merge Sort

void merge(int arr[], int esq[], int dir[], int n)
{
    int lenEsq, lenDir;
    lenEsq = n / 2;
    lenDir = n - lenEsq;
    int i = 0, j = 0, k = 0;         //i = index da lista esquerda sub-array ; j = index da lista direita sub-array ; k = index do array de output
    while (i < lenEsq && j < lenDir) //verifica se item da lista da esquerda é maior ou menor que item da lista esquerda, e insere na lista do output
    {
        if (esq[i] < dir[j])
        {
            arr[k] = esq[i];
            i++;
        }
        else
        {
            arr[k] = dir[j];
            j++;
        }
        k++;
    }
    while (i < lenEsq) //transfere items restantes na listas, como os items da esquerda são menores eles são passados primeiro para o array
    {
        arr[k] = esq[i];
        i++;
        k++;
    }

    while (j < lenDir)
    {
        arr[k] = dir[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int n)
{
    if (n <= 1)
        return;
    int mid = n / 2, i;
    int l[mid], r[n - mid];   //define arrays temporarios para manipulação de items
    for (i = 0; i < mid; i++) //copia-se dados de array origem ao arrays temporarios
        l[i] = arr[i];
    for (i = mid; i < n; i++) //copia-se dados de array origem ao arrays temporarios
        r[i - mid] = arr[i];
    mergeSort(l, mid);
    mergeSort(r, n - mid);
    merge(arr, l, r, n);
}

void copyArray(int *array1, int *array2)
{
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
    {
        array1[i] = array2[i];
    }
    return;
}

//Heap Sort
void swapElements(int *inputArray, int index1, int index2) // faz troca de items
{
    int temporary = inputArray[index1];
    inputArray[index1] = inputArray[index2];
    inputArray[index2] = temporary;
}

void heapfy(int *inputHeap, int rootIndex, int sizeOfHeap)
{
    int maxValueIndex = rootIndex; //inicia o index do maior valor como o da raiz, ele vai ser testado se merece a posição de "maior valor" (já que é um max heap) do array.
    int leftChildIndex = 2 * rootIndex + 1;
    int rightChildIndex = 2 * rootIndex + 2;

    if ((leftChildIndex < sizeOfHeap) && (inputHeap[leftChildIndex] > inputHeap[maxValueIndex])) //Se o final do array não tiver sido atingido e o filho da esquerda for maior que o maior valor do heap 
    {
        maxValueIndex = leftChildIndex; //o index o maior elemento do array é o index do filho da esquerda (ainda não foi trocado as posições dele no array)
    }

    if ((rightChildIndex < sizeOfHeap) && (inputHeap[rightChildIndex] > inputHeap[maxValueIndex]))
    {
        maxValueIndex = rightChildIndex; //o index o maior elemento do array é o index do filho da direita (ainda não foi trocado as posições dele no array)
    }

    if (maxValueIndex != rootIndex) //Se aconteceu alteração no index do maior elemento 
    {
        swapElements(inputHeap, rootIndex, maxValueIndex); //troca a posição do maior elemento com o antigo
        heapfy(inputHeap, maxValueIndex, sizeOfHeap); //organiza o heap com o novo index do maior elemento.
    }
}

void buildMaxHeap(int *inputArray, int sizeOfArray)
{
    for (int i = sizeOfArray / 2 - 1; i >= 0; i--) //para construir o heap só é necessário executar o loop nos valores da metade para baixo
    {
        heapfy(inputArray, i, sizeOfArray);
    }
}

void heapSort(int *inputArray, int sizeOfArray)
{
    buildMaxHeap(inputArray, sizeOfArray); //transforma o input array em um max heap
    for (int i = sizeOfArray - 1; i >= 0; i--) //Para i sendo o últmo index do array até chegar no primeiro..
    {
        swapElements(inputArray, 0, i); //troca o primeiro valor do heap (o maior valor) com o na posição i
        heapfy(inputArray, 0, i); //organiza o heap até o valor na posição i. Valores nas posições maiores que i são deixados sem alterar (pois já foram os maiores valores)
    }
}

// quick sort
int particao(int *inputArray, int low, int high)
{
    int eixo = inputArray[high];          //define eixo de comparação apartir do ultimo item da lista
    int i = low - 1;                      //define incio da lista a ser navegada
    for (int j = low; j <= high - 1; j++) //navega array
    {
        if (inputArray[j] <= eixo) //transfere todos os pontos do array menores que o eixo para a esquerda da posição do eixo no array
        {
            i++;
            swapElements(inputArray, i, j);
        }
    }
    swapElements(inputArray, i + 1, high); //caso o index do ultimo elemento navegado seja menor que o item passado como high, faz a troca dos dois
    return (i + 1);
}

void quickSort(int *inputArray, int low, int high)
{
    if (low < high)
    {
        int indexP = particao(inputArray, low, high); //particiona o array, passando para o indexP qual até que ponto andou o array na função partição.
        quickSort(inputArray, low, indexP - 1);       //chama recursivamente a função aplicando aos items mais a esquerda do array
        quickSort(inputArray, indexP + 1, high);      //chama recursivamente a função aplicando aos items mais a dirreita do array.
    }
}

// quick sort mid
int particaoMid(int *inputArray, int low, int high)
{
    int mid = (high + low) / 2; //pega o index do meio do array
    int eixo = inputArray[mid]; //coloca o eixo como item do meio do array
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    { //transfere todos os pontos do array menores que o eixo para a esquerda da posição do eixo no array
        if (inputArray[j] <= eixo)
        {
            i++;
            swapElements(inputArray, i, j);
        }
    }
    swapElements(inputArray, i + 1, high);
    return (i + 1);
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

void generateRandomIntArray(int *inputArray)
{

    time_t randomIntGenerator; //initializing random number generator
    srand((unsigned)time(&randomIntGenerator));

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
    char algorithmName[100];
    switch (sortAlgorithm)
    {
    case INSERTION_SORT:
        insertionSort(inputArray);
        strcpy(algorithmName, "Insertion Sort");
        break;
    case BUBBLE_SORT:
        bubbleSort(inputArray);
        strcpy(algorithmName, "Bubble Sort");
        break;
    case SELECTION_SORT:
        selectionSort(inputArray);
        strcpy(algorithmName, "Selection Sort");
        break;
    case MERGE_SORT:
        mergeSort(inputArray, SIZE_OF_ARRAY);
        strcpy(algorithmName, "Merge Sort");
        break;
    case HEAP_SORT:
        heapSort(inputArray, SIZE_OF_ARRAY);
        strcpy(algorithmName, "Heap Sort");
        break;
    case QUICK_SORT:
        quickSort(inputArray, 0, SIZE_OF_ARRAY - 1);
        strcpy(algorithmName, "Quick Sort");
        break;
    case QUICK_SORT_MID:
        quickSortMid(inputArray, 0, SIZE_OF_ARRAY - 1);
        strcpy(algorithmName, "Quick Sort Mid");
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

    generateRandomIntArray(unsortedArray);
    printf("The array of random int is: ");
    printArray(unsortedArray);

    resetArray(arrayToSort, unsortedArray);   //sets arrayToSort = unsortedArray
    executeSort(arrayToSort, INSERTION_SORT); //execute the Sort on arrayToSort and print outputs

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
