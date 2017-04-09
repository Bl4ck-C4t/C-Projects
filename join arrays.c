#include <stdio.h>
#include <stdlib.h>

int main()
{
    int j,i,k,len1,len2,to_move = 0;
    printf("\nHow long is the first array: ");
    scanf("%d",&len1);
    printf("\nHow long is the second array: ");
    scanf("%d",&len2);
    int arr1[len1];
    int arr2[len2];
    int comb[len1+len2];
    for(i=0;i < len1;i++){
        printf("\nEnter number[%d] of first array: ", i+1);
        scanf("%d",&to_move);
        arr1[i] = to_move;
    }
    for(j=0;j < len2;j++){
        printf("\nEnter number[%d] of second array: ", j+1);
        scanf("%d",&to_move);
        arr2[j] = to_move;
    }
    i = 0;
    j = 0;
    k = 0;
    while(i < len1 || j < len2){
        if(i < len1 && j < len2){
            if(arr1[i] < arr2[j]){
                to_move = arr1[i];
                i++;
            }
            else{
                to_move = arr2[j];
                j++;
            }

        }
        else{
            if(i >= len1){
                to_move = arr2[j];
                j++;
            }
            else if(j >= len2){
                to_move = arr1[i];
                i++;
            }
        }
        comb[k] = to_move;
        k++;

    }
    for(i=0; i < len1+len2; i++){
        printf("\n%d", comb[i]);
    }
    return 0;
}
