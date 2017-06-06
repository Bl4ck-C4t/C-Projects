#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
    char name[50];
    int num;
    int grd;
    float avg;
    int grades[69];

}Student;

typedef struct{
    int students;
    float average;

}Options;

float average(Student);
void Make_students();
void Read_students();
void sorter(Student students[], int ln);
void add_student();
Student create_student();

int main()
{
    int choice;
    do{
        printf("\n1. Make students\n2. Add student\n3. Show students\n4. Exit");
        printf("\nEnter number: ");
        scanf("%d", &choice);
        getchar();
        switch(choice){
            case 1: Make_students(); break;
            case 2: add_student(); break;
            case 3: Read_students(); break;
            case 4: printf("\nOk bye."); break;
        }

    }while(choice != 3);
    return 0;
}

float average(Student std){
    float sm = 0;
    int i;
    for(i = 0; i < std.grd; i++){
        sm += std.grades[i];
    }
    sm /= std.grd;
    return sm;
}

void Make_students(){
    Student st;
    FILE *f;
    f = fopen("students.dat", "wb");
    int i,k,j = 0;
    int ln;
    int grd;
    printf("How many students will you add: ");
    scanf("%d", &ln);
    getchar();
    Options opts;
    opts.students = ln;
    fwrite(&opts, sizeof(Options), 1, f);
    float class_average = 0;
    for(i = 0; i < ln; i++){
        st = create_student();
        printf("\nEnter name of student[%d]: ", i+1);
        gets(st.name);
        printf("\nEnter number of %s: ", st.name);
        scanf("%d", &st.num);
        getchar();
        int grade;
        j = 0;
        while(1){
            printf("Enter grade[%d]: ", j+1);
            scanf("%d", &grade);
            getchar();
            if(grade == 0) break;
            st.grades[j] = grade;
            j++;
        }
        st.avg = average(st);
        class_average += st.avg;
        fwrite(&st, sizeof(Student), 1, f);
    }
    class_average /= ln;
    Options opts2;
    opts2.average = class_average;
    fwrite(&opts2, sizeof(Options), 1, f);
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
    FILE *f;
    int i = 0;
    int j;
    f = fopen("students.dat", "rb");
    float class_average;
    Options opts;
    fread(&opts, sizeof(opts), 1, f);
    int ln = opts.students;
    int grade;
    printf("\nName   Number   Grades       Average");
    while(i < ln){
        st = create_student();
        fread(&st, sizeof(st), 1, f);
        printf("\n%s    %d    ", st.name, st.num);
        while(1){
            grade = st.grades[j];
            if(grade == 0) break;
            printf("%d, ", st.grades[j]);
        }
        printf("     %.2f\n", st.avg);
        if(st.avg < 3){
            poprawka[k] = st;
            k++;
        }
        i++;

    }
    Options opts2;
    fread(&opts2, sizeof(opts2), 1, f);
    class_average = opts2.average;
    printf("Class average: %.2f", class_average);
    printf("\nNa poprawitelen oswen Mihael: \n");
    for(i = 0; i < k; i++){
        printf("\n%s", poprawka[i].name);
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
        if(grade == 0) break;
        st.grades[j] = grade;
        j++;
    }
    st.avg = average(st);
    fwrite(&f, sizeof(st), 1, f);
    printf("\nStudent added.");
}

Student create_student(){
    Student st;
    return st;
}
