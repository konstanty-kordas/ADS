#include <iostream>
#include <chrono>
#include <thread>


void BubbleSort(int len, int*arr){
    int x;
    bool flag = false;
    for (int i=0;i<len;i++){
        for (int j=i+1;j<len;j++){
            if (arr[i]>arr[j]){
                x = arr[j];
                arr[j] = arr[i];
                arr[i] = x;
                flag=false;
            }
        }
        if (flag){
            break;
        }
    }
}

void ShellSort(int len, int*arr){

    int j,temp;
    for (int gap = len/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < len; i += 1)
        {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void InsertionSort(int len, int*arr){
    int x,j;
    for (int i = 1; i < len; i++){
        x = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > x)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = x;
    }
}

void SelectionSort(int len, int* arr){
    int k, x;
    for (int i=0;i<len;i++){
        x = arr[i];
        k = i;
        for (int j=i+1;j<len;j++){
            if (arr[j]<x){
                k=j;
                x = arr[k];
            }
        }
        arr[k] = arr[i];
        arr[i] = x;
    }
}

void heapify(int arr[], int n, int i)
{
    int x;
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        x = arr[largest];
        arr[i] = arr[largest];
        arr[largest] = x;
        heapify(arr, n, largest);
    }
}


void HeapSort(int len, int* arr){
    int x;
    for (int i = len / 2 - 1; i >= 0; i--)
        heapify(arr, len, i);
    for (int i = len - 1; i >= 0; i--) {
        // Move current root to end
        x = arr[0];
        arr[0] = arr[i];
        arr[i] = x;
        heapify(arr, i, 0);
    }
}



int HoarePartition (int* a,int p, int r) {
    int x=a[p],i=p-1,j=r;
    int temp;
    while (1) {
        do  {
            j--;
        } while (a[j] > x);
        do { 
            i++;
        } while (a[i] < x);
        if  (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        else {
            return j+1;
        }
    }
}
void quickSortR(int* a,int start,int end) {
    int q;
    if (end-start<2) {
        return;
    }
    q=HoarePartition(a,start,end);
    quickSortR(a,start,q);
    quickSortR(a,q,end);
}


void QuickSort(int len, int*arr){
    quickSortR(arr,0,len);
}


void merge(int* array, int left, int mid, int right)
{
    int subArrayOne =mid - left + 1 ;
    int subArrayTwo = right - mid;

    int *leftArray = (int*)malloc(sizeof(int) * subArrayOne);
    int *rightArray = (int*)malloc(sizeof(int) * subArrayTwo);

    for ( int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for ( int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    int index1 = 0,index2 = 0;
    int indexMerged = left;
 
    while (index1 < subArrayOne && index2 < subArrayTwo) {
        if (leftArray[index1] <= rightArray[index2]) {
            array[indexMerged] = leftArray[index1];
            index1++;
        }
        else {
            array[indexMerged] = rightArray[index2];
            index2++;
        }
        indexMerged++;
    }

    while (index1 < subArrayOne) {
        array[indexMerged] = leftArray[index1];
        index1++;
        indexMerged++;
    }

    while (index2 < subArrayTwo) {
        array[indexMerged] = rightArray[index2];
        index2++;
        indexMerged++;
    }
}

void MergeSortR(int* array, int start, int end) {
    if ( start >= end)
        return;
    int mid =  start + (end -  start) / 2;
    MergeSortR(array,  start, mid);
    MergeSortR(array, mid + 1, end);
    merge(array,  start, mid, end);
}


void MergeSort(int len, int* arr){
    MergeSortR(arr, 0,len-1);
}

int getMax(int* array, int len) {
    int max = array[1];
    for(int i = 2; i<=len; i++) {
        if(array[i] > max)
            max = array[i];
    }

    return max; 
}
void CountingSort(int len,int *array) {
    int *output = (int*)(malloc(sizeof(int)* (len+1)));
    int max = getMax(array, len);
    int *count = (int*)(malloc(sizeof(int)* (max+1))); 

    for(int i = 0; i<=max; i++)
        count[i] = 0; 
    for(int i = 1; i <=len; i++)
        count[array[i]]++; 
    for(int i = 1; i<=max; i++)
        count[i] += count[i-1]; 

    for(int i = len; i>=1; i--) {
        output[count[array[i]]] = array[i];
        count[array[i]] -= 1; 
    }

    for(int i = 1; i<=len; i++) {
        array[i] = output[i];
    }
}


