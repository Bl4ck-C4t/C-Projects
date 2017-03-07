#include <stdio.h>
#include <stdlib.h>
int main() {
    char br;
    int i = 0;
    int j = 0;
    int len;
    int c = 1;
    int array[250];
    int indexes[250];
    int couples[250][2];
    int sm = 0;
    do{
        printf("\nEnter bracket: ");
        br = getche();
        if (br != 13){
            array[i] = br;
            if(br == '('){
                sm++;
            }
            else{
                sm--;
            }
            i++;
            if(sm < 0){
                c = 0;
                break;
            }
        }
    }while(br != 13);
    len = i;
    if(sm != 0){
        c = 0;
    }
    sm = -1;
    int len2;
    int tmp, tmp2;
    if(c){
      printf("\nCorrect!");
      for(i = 0; i < len; i++){
        if(array[i] == '('){
            sm++;
            indexes[sm] = i;
        }
        else{
            couples[j][0] = indexes[sm];
            couples[j][1] = i;
            sm--;
            j++;
        }
      }
      len2 = j;
      sm = 0;
      for(j = 0; j < len2-1; j++){
        for(i = sm; i < len2; i++){
            if(couples[i][0] < couples[sm][0]){
                tmp = couples[i][0];
                tmp2 = couples[i][1];
                couples[i][0] = couples[sm][0];
                couples[i][1] = couples[sm][1];
                couples[sm][0] = tmp;
                couples[sm][1] = tmp2;
            }

        }
        sm++;
      }
      printf("\nCouples:");
      for(i = 0; i < len2; i++){
        printf("\n%d, %d", couples[i][0], couples[i][1]);
      }
    }
    else{
        printf("\nIncorrect");
    }

   return 0;
}
