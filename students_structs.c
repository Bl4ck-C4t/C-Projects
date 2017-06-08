#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
    char name[50];
    int num;
    float avg;
    int grades[69];

}Student;


float average(Student);
void Make_students();
void Read_students();
void sorter(Student students[], int ln);
void add_student();
void edit_students();
void change_file();
Student create_student();

int main()
{
    int choice;
    do{
        printf("\n1. Make students\n2. Add student\n3. Show students\n4. Edit\n5. Change file\n6. Exit");
        printf("\nEnter number: ");
        scanf("%d", &choice);
        getchar();
        switch(choice){
            case 1: Make_students(); break;
            case 2: add_student(); break;
            case 3: Read_students(); break;
            case 4: edit_students(); break;
            case 5: change_file(); break;
            case 6: printf("\nOk bye."); break;
        }

    }while(choice != 6);
    return 0;
}

float average(Student std){
    float sm = 0;
    int i = 0;
    int grade;
    while(1){
        grade = std.grades[i];
        if(grade == 0) break;
        sm += grade;
        i++;
    }
    sm /= i;
    return sm;
}

void Make_students(){
    Student st;
    FILE *f;
    FILE *con;
    f = fopen("students.dat", "wb");
    int i,k,j = 0;
    int ln;
    i = 0;
    while(1){
        st = create_student();
        printf("\nEnter name of student[%d]('END' to stop): ", i+1);
        gets(st.name);
        if(strcmp(st.name, "END") == 0){
            break;
        }
        printf("\nEnter number of %s: ", st.name);
        scanf("%d", &st.num);
        getchar();
        int grade;
        j = 0;
        while(1){
            printf("Enter grade[%d]: ", j+1);
            scanf("%d", &grade);
            getchar();
            st.grades[j] = grade;
            if(grade == 0) break;
            j++;
        }
        st.avg = average(st);
        fwrite(&st, sizeof(Student), 1, f);
        i++;
    }
    fclose(f);
    printf("\nStudents written.");
    //For read
}

void sorter(Student students[], int ln){
    int term;
    int i;
    Student st;
    while(1){
        term = 0;
        for(i = 0; i < ln-1; i++){
            if(strcmp(students[i].name, students[i+1].name) == 1){
                st = students[i];
                students[i] = students[i+1];
                students[i+1] = st;
                term = 1;
            }
        }
        if(term == 0){
            break;
        }
    }
}


void Read_students(){
    Student st;
    Student poprawka[40];
    int k = 0;
    int nm = 0;
    FILE *f;
    int j;
    f = fopen("students.dat", "rb");
    float class_average = 0;
    int grade;
    printf("\nName   Number   Grades       Average");
    while(!feof(f)){
        fread(&st, sizeof(st), 1, f);
        nm++;
        class_average += st.avg;
        printf("\n%s    %d    ", st.name, st.num);
        j = 0;
        while(1){
            grade = st.grades[j];
            if(grade == 0) break;
            printf("%d, ", st.grades[j]);
            j++;
        }
        printf("     %.2f\n", st.avg);
        if(st.avg < 3){
            poprawka[k] = st;
            k++;
        }

    }
    class_average /= nm;
    printf("Class average: %.2f", class_average);
    printf("\nNa poprawitelen: ");
    for(j = 0; j < k; j++){
        printf("\n%s", poprawka[j].name);
    }
    fclose(f);

}

void add_student(){ // Still in development
    Student st;
    FILE *f;
    int i = 0;
    int j = 0;
    f = fopen("students.dat", "ab");
    printf("\nEnter name of student: ");
    gets(st.name);
    printf("\nEnter number of %s: ", st.name);
    scanf("%d", &st.num);
    getchar();
    int grade;
    while(1){
        printf("Enter grade[%d]: ", j+1);
        scanf("%d", &grade);
        getchar();
        st.grades[j] = grade;
        if(grade == 0) break;
        j++;
    }
    st.avg = average(st);
    fwrite(&f, sizeof(st), 1, f);
    printf("\nStudent added.");
    fclose(f);
}
void edit_students(){
    int nm;
    FILE *f;
    FILE *f2;
    int j;
    int grade;
    Student st;
    Student st_new;
    f = fopen("student.dat", "rb");
    f2 = fopen("temp.tmp", "wb");
    printf("\nEnter number of student: ");
    scanf("%d", &st_new.num);
    getchar();
    printf("\nEnter name of student: ");
    gets(st_new.name);
    j = 0;
    while(1){
        printf("Enter grade[%d]: ", j+1);
        scanf("%d", &grade);
        getchar();
        if(grade == 0) break;
        st_new.grades[j] = grade;
        j++;
    }
    st.avg = average(st);
    while(!feof(f)){
        st = create_student();
        fread(&st, sizeof(Student),1, f);
        if(st.num == st_new.num) fwrite(&st_new, sizeof(Student), 1, f2);
        else fwrite(&st, sizeof(Student), 1, f2);
    }
    fclose(f);
    fclose(f2);
    f = fopen("student.dat", "wb");
    f2 = fopen("temp.tmp", "rb");
    while(!feof(f2)){
        st = create_student();
        fread(&st, sizeof(Student),1, f2);
        fwrite(&st, sizeof(Student), 1, f);
    }
    printf("Record updated.");
}

void change_file(){

}

Student create_student(){
    Student st;
    return st;
}
