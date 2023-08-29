//wap to sort list of array elements using merge sort technique and calculate the execution time only to sort the elements. count the number of comparisions.
#include <stdio.h>
#include <stdlib.h>
 
//merges two subarrays of arr[] first subarray is arr[l..m]. second subarray is arr[m+1..r].
void merge(int arr[], int l, int m, int r)
{
 int i,j,k;
 int n1=m-l+1;
 int n2=r-m;
 
 //creating temp arrays
 int L[n1], R[n2];
   
  //copying data to temp arrays
  //L[] and R[]
  for (i = 0; i < n1; i++)
   L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
   R[j] = arr[m + 1 + j];
       
   //merging the temp arrays back
   //into arr[l..r]
   // Initial index of first subarray
   i = 0;
   
   //initial index of merged subarray
   k = l;
   while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    }
    else {
     arr[k] = R[j];
     j++;
   }
    k++;
 }
 
//copying the remaining elements of L[], if there are any.
    while (i < n1) {
     arr[k] = L[i];
     i++;
     k++;
}
 
//copying the remaining elements of R[], if there are any.
   
    while (j < n2) {
     arr[k] = R[j];
     j++;
     k++;
    }
}
//l is for left index and r is right index of the sub-array of arr to be sorted.
void MergeSort(int arr[],int l, int r)
{
if(l<r) {
{
        //same as (l+r)/2, but avoids overflow for large l and h
        int m = l + (r - l) / 2;
 
        //sorting first and second half.
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}

//function to print an array
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
