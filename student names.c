#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char students[100][100];
    int ln,i;
    printf("How much students will you add?: ");
    scanf("%d", &ln);
    for(i=0; i < ln; i++){
        printf("\nEnter student name: ");
        gets(students[i]);
    }

    int terminate;
    int j = 0;
    char swap[100];
    while(1){
        terminate = 1;
        for(i=0; i < strlen(students)-1; i++){
            if(strcmp(students[i], students[i+1]) == 1){
                strcpy(swap, students[i]);
                strcpy(students[i], students[i+1]);
                strcpy(students[i+1], swap);
                terminate = 0;
            }
        }
        j++;
        if(terminate) break;
    }
    for(i=0; i < ln; i++){
        puts(students[i]);
    }



    return 0;
}
