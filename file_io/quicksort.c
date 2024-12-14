#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int partition(int *arr, int left, int right);

void quickSort(int *arr, int left, int right);

int main(int argc, char *argv[])
{
    int arr[] = {6, 5, 5, 4, 3, 3, 0, 2, 1, -4, -1, 100, -1, -2};
    int len = sizeof(arr) / sizeof(int);
    printf("Len : %d\n", len);
    for (int i = 0; i < len; i++)
    {
        printf("%d,", arr[i]);
    }
    quickSort(arr, 0, len - 1);
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d,", arr[i]);
    }
}

int partition(int *arr, int left, int right)
{
    int pivotElement = arr[left];
    int n = (right - left) + 1;
    int tempArr[n];
    int i = 0;
    int temp = left;
    int equal = 0;
    while (temp <= right)
    {
        if (arr[temp] < pivotElement)
        {
            tempArr[i] = arr[temp];
            i++;
        }
        else if (arr[temp] == pivotElement)
            equal++;
        temp++;
    }
    while (equal > 0)
    {
        tempArr[i] = pivotElement;
        equal--;
        i++;
    }
    int pivotElementCorrectIndex = i - 1;
    temp = left;
    while (temp <= right)
    {
        if (arr[temp] > pivotElement)
        {
            tempArr[i] = arr[temp];
            i++;
        }
        temp++;
    }
    for (int i = 0; i < (right - left) + 1; i++)
    {
        arr[i + left] = tempArr[i];
    }
    return pivotElementCorrectIndex + left;
}

// int partition(int *arr, int left, int right)
// {
//     int pivotElement = arr[left];
//     int tempArr[right - left + 1]; // Allocate temp array to hold partitioned values
//     int i = 0;
//     int j = left;
//     int k = right;

//     // First loop to partition smaller and larger elements
//     while (j <= right)
//     {
//         if (arr[j] < pivotElement)
//         {
//             tempArr[i] = arr[j];
//             i++;
//         }
//         else if (arr[j] > pivotElement)
//         {
//             tempArr[k] = arr[j];
//             k--;
//         }
//         j++;
//     }

//     // Fill the pivot elements in the middle part of tempArr
//     while (i <= k)
//     {
//         tempArr[i] = pivotElement;
//         i++;
//     }

//     // Copy back the sorted values from tempArr[] to arr[]
//     for (int idx = 0; idx < (right - left + 1); idx++)
//     {
//         arr[left + idx] = tempArr[idx];
//     }

//     // Return the index of the pivot element in the partitioned array
//     return left + (i - 1);
// }

void quickSort(int *arr, int left, int right)
{

    if (left >= right) // one element is already considered sorted
        return;
    // for this implementation , we chose the first element as the pivot
    int pivotElementCorrectIndex = partition(arr, left, right);
    // now we recursively repeat the same procedure for the 2 arrays
    // the first array is from the left to the pivotElementCorrectIndex
    // the second array is from the pivotElementCorrectIndex + 1 to the right
    quickSort(arr, left, pivotElementCorrectIndex - 1);
    quickSort(arr, pivotElementCorrectIndex + 1, right);
}