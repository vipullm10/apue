#include <stdio.h>
#include <unistd.h>

void merge(int *arr, int left, int mid, int right);

void mergeSort(int *arr, int left, int right);

int main(int argc, char *argv[])
{
    int arr[] = {6, 5, 4, 3, 2, 1};
    int len = sizeof(arr) / sizeof(int);
    for (int i = 0; i < len; i++)
    {
        printf("%d,", arr[i]);
    }
    mergeSort(arr, 0, len - 1);
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d,", arr[i]);
    }
}

void mergeSort(int *arr, int left, int right)
{
    if (left == right)
        return;
    int mid = (left + right) / 2;
    mergeSort(arr, 0, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void merge(int *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1; // Size of the left half
    int n2 = right - mid;    // Size of the right half

    // Create temporary arrays to hold the left and right halves
    int firstArr[n1], secondArr[n2];

    // Copy data into temp arrays
    for (int i = 0; i < n1; i++)
    {
        firstArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++)
    {
        secondArr[i] = arr[mid + 1 + i];
    }

    // Merge the temp arrays back into arr[]
    int i = 0, j = 0, k = left;

    // Merge until one of the arrays is exhausted
    while (i < n1 && j < n2)
    {
        if (firstArr[i] <= secondArr[j])
        {
            arr[k] = firstArr[i];
            i++;
        }
        else
        {
            arr[k] = secondArr[j];
            j++;
        }
        k++;
    }

    // If there are remaining elements in firstArr, copy them
    while (i < n1)
    {
        arr[k] = firstArr[i];
        i++;
        k++;
    }

    // If there are remaining elements in secondArr, copy them
    while (j < n2)
    {
        arr[k] = secondArr[j];
        j++;
        k++;
    }
}
