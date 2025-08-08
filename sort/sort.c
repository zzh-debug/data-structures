#include <stdio.h>

int arr[] = {1, 2, 4 , 8, 1, 3, 2, 8, 0, 1};

void bubbleSort(int arr[],int n);

void bubbleSort(int arr[],int n) {
    int temp;
    for(int i=0; i<n; i++) {
        for(int j=0;j<n;j++) {
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
}

int main(int argc,char* argv[]) {
    bubbleSort(arr[],10);
    int n = 10;
    for(int i;i <= n;i++) {
        printf("%d ",arr[i]);
        printf("\n");
    }
    return 0;
}
