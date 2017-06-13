#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern char filename[30] = "students.dat";




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
void delete_student();
void backup();
Student create_student();

int main()
{
    int choice = 0;
    char option;
    int ln = 7;
    int i;
    char options[50][50] = {"1. Make students", "2. Add student", "3. Show students", "4. Edit", "5. Delete student", "6. Change file", "7. Exit"};
    while(1){
        while(1){
            for(i = 0; i < ln; i++){
                printf("\n");
                if (choice == i){
                    printf("> ");
                }
                printf("%s", options[i]);
            }
            option = getche();
            if(option == 38 && choice > 0){// up arrow
                choice--;
            }
            if(option == 40 && choice < ln){ // down arrow
                choice++;
            }
            if(option == 13){
                break;
            }
            system("cls");
        }
        switch(choice){
            case 1: Make_students(); break;
            case 2: add_student(); break;
            case 3: Read_students(); break;
            case 4: edit_students(); break;
            case 5: delete_student(); break;
            case 6: change_file(); break;
            case 7: printf("\nOk bye."); break;
        }
    }
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
    f = fopen(filename, "wb");
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
    f = fopen(filename, "rb");
    float class_average = 0;
    int grade;
    printf("\nName   Number   Grades       Average");
    while(fread(&st, sizeof(st), 1, f)){
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
        printf("     %.2f", st.avg);
        if(st.avg < 3){
            poprawka[k] = st;
            k++;
        }

    }
    class_average /= nm;
    printf("\nClass average: %.2f", class_average);
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
    f = fopen(filename, "ab");
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
    fwrite(&st, sizeof(st), 1, f);
    printf("\nStudent added.");
    fclose(f);
}
void edit_students(){
    int nm;
    FILE *f;
    int j;
    int grade;
    Student st;
    Student st_new;
    f = fopen(filename, "rb+");
    printf("\nEnter number of student: ");
    scanf("%d", &st_new.num);
    getchar();
    printf("\nEnter name of student: ");
    gets(st_new.name);
    j = 0;
    int index;
    while(1){
        printf("Enter grade[%d]: ", j+1);
        scanf("%d", &grade);
        getchar();
        st_new.grades[j] = grade;
        if(grade == 0) break;
        j++;
    }
    st_new.avg = average(st_new);
    while(fread(&st, sizeof(st),1, f)){
        if(st.num == st_new.num){
            index = ftell(f) - sizeof(st);
            fseek(f, index, SEEK_SET);
            fwrite(&st_new, sizeof(Student), 1, f);
            break;
        }
    }
    fclose(f);
    printf("Record updated.");
}

void change_file(){
    printf("\nEnter filename: ");
    gets(filename);
    printf("\nFile updated.");
}

void delete_student(){
    int nm;
    int len = 0;
    int index;
    backup(); // backup for security
    printf("\nEnter student number to delete: ");
    scanf("%d", &nm);
    getchar();
    FILE *f;
    Student st;
    f = fopen(filename, "rb+");
    while(fread(&st, sizeof(st), 1, f)){
        len++;
    }
    len *= sizeof(st);
    len -= sizeof(st);
    fseek(f, SEEK_SET, 0);
    while(fread(&st, sizeof(st), 1, f)){
        if(st.num == nm){
            while(fread(&st, sizeof(st), 1, f)){
                index = ftell(f) - sizeof(st)*2;
                fseek(f, index, SEEK_SET);
                fwrite(&st, sizeof(st), 1, f);
                index = ftell(f) + sizeof(st);
                fseek(f, index, SEEK_SET);
            }
            break;
        }
    }
    chsize(fileno(f), len);
    fclose(f);
    printf("\nStudent deleted.");
}
void backup(){
    char fname[50];
    printf("\nEnter filename of backup: ");
    gets(fname);
    FILE *f;
    FILE *b;
    f = fopen(filename, "rb");
    b = fopen(fname, "wb");
    Student st;
    while(fread(&st, sizeof(st), 1, f)){
        fwrite(&st, sizeof(st), 1, b);
    }
    fclose(f);
    fclose(b);
    printf("\nStudents backed up to %s", fname);
}

Student create_student(){
    Student st;
    return st;
}
