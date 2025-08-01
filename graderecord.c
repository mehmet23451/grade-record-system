#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graderecord.h"

void addstudent(){
    struct graderecord record;
    printf("ID: ");
    scanf("%d", &record.id);
    printf("Name: ");
    scanf("%s", record.name);
    printf("Surname: ");
    scanf("%s", record.surname);
    printf("Course code: ");
    scanf("%s", record.course_code);
    printf("Midterm grade: ");
    scanf("%f", &record.midterm);
    printf("Lab grade: ");
    scanf("%f", &record.lab);
    printf("Final exam grade: ");
    scanf("%f", &record.final_exam);
    record.year_end_grade = record.midterm * 0.3f + record.lab * 0.2f + record.final_exam * 0.5f;
    FILE *fp = fopen("grades.bin", "ab"); 
    if (fp == NULL) {
        perror("Dosya açılamadı");
        return ;
    }
    fwrite(&record, sizeof(struct graderecord), 1, fp);
    fclose(fp);
    printf("Veri kaydedildi.\n");
    return ;
}
void liststudents(){
    struct graderecord a;
    FILE *fp=fopen("grades.bin","rb");
    if (fp==NULL){
        perror("dosya açılamadı.");
        return;
    }
    while (fread(&a,sizeof(struct graderecord),1,fp)){
        printf("id:%d name:%s surname:%s course code:%s midterm:%f lab:%f final:%f end grade:%f\n",a.id,a.name,a.surname,a.course_code,a.midterm,a.lab,a.final_exam,a.year_end_grade);
    }
    fclose(fp);
    return;
}


void modify(){
    struct graderecord a;
    FILE *fp=fopen("grades.bin","rb+");
    if (fp==NULL){
        perror("dosya açılamadı.");
        return;
    }
    int findid;
    int exist=0;
    printf("please enter id of student:");
    scanf("%d",&findid);
    while (fread(&a,sizeof(struct graderecord),1,fp)){
        if (a.id==findid){
        exist=1;
            printf("Name: ");
        scanf("%s", a.name);
        printf("Surname: ");
        scanf("%s", a.surname);
        printf("Course code: ");
        scanf("%s", a.course_code);
        printf("Midterm grade: ");
        scanf("%f", &a.midterm);
        printf("Lab grade: ");
        scanf("%f", &a.lab);
        printf("Final exam grade: ");
        scanf("%f", &a.final_exam);

        a.year_end_grade = a.midterm * 0.3f + a.lab * 0.2f + a.final_exam * 0.5f;

        fseek(fp, -sizeof(struct graderecord), SEEK_CUR);
        fwrite(&a, sizeof(struct graderecord), 1, fp);
    
        printf("Veri kaydedildi.\n");
        break;
        }
        
    }if(exist==0){
            printf("invalid input");
            return;
        }
        fclose(fp);
}
void delete(){
    struct graderecord a;
    FILE *fp=fopen("grades.bin","rb");
    FILE *temp=fopen("temp.bin","wb");
    if ( fp == NULL || temp==NULL){
        perror("cant open file");
        return;
    }
    int findid;
    int exist=0;
    printf("please enter id of student:");
    scanf("%d",&findid);
    while (fread(&a,sizeof(struct graderecord),1,fp)){
        if(findid==a.id){
            exist=1;
            continue;

        }
        fwrite(&a,sizeof(struct graderecord),1,temp);
    }
    fclose(fp);
    fclose(temp);
    if (exist==0){
        printf("doesnt exist.");
        remove("temp.bin");
    }
    else {
        remove("grades.bin");
        rename("temp.bin","grades.bin");
        printf("deleted succesfully!");
    }
}

void search(){
    struct graderecord a;
    FILE *fp=fopen("grades.bin","rb");
    if (fp==NULL){perror("cant open the file");return;}
    char given[20];
    int exist=0;
    printf("please enter the name or surname");
    scanf("%s",given);
    while (fread(&a,sizeof(struct graderecord),1,fp)){
        if (strstr(a.name,given)||strstr(a.surname,given)){
            exist=1;
            printf("id:%d name:%s surname:%s course code:%s midterm:%f lab:%f final:%f end grade:%f\n",a.id,a.name,a.surname,a.course_code,a.midterm,a.lab,a.final_exam,a.year_end_grade);
        }
    }
    if (exist==0){
        printf("doesnt exist");
    }
    fclose(fp);
    return;
}

void display(){
    struct graderecord a;
    char course[20];
    FILE* fp=fopen("grades.bin","rb");
    if (fp==NULL){
        printf("error opening file");
        return;
    }
    int min,max,answer;
    
    printf("what do you want to do? 1-Display failed students 2-Display in interval of grades 3- Display with course code");
    scanf("%d",&answer);
    if (answer==1){
        while (fread(&a,sizeof(struct graderecord),1,fp)){
            if (a.year_end_grade<30 ){
                printf("id:%d name:%s surname:%s course code:%s midterm:%f lab:%f final:%f end grade:%f\n",a.id,a.name,a.surname,a.course_code,a.midterm,a.lab,a.final_exam,a.year_end_grade);
            }
        }
    }
    if (answer==2){
        printf("please enter min");scanf("%d",&min);
    printf("please etner max:");scanf("%d",&max);
        while (fread(&a,sizeof(struct graderecord),1,fp)){
            if (a.year_end_grade<max && a.year_end_grade>min){
                printf("id:%d name:%s surname:%s course code:%s midterm:%f lab:%f final:%f end grade:%f\n",a.id,a.name,a.surname,a.course_code,a.midterm,a.lab,a.final_exam,a.year_end_grade);
            }
        }
    }
    if (answer==3){
        printf("enter course code:");scanf("%s",course);
        while (fread(&a,sizeof(struct graderecord),1,fp)){
            
            if (strcmp(a.course_code,course)==0 ){
                printf("id:%d name:%s surname:%s course code:%s midterm:%f lab:%f final:%f end grade:%f\n",a.id,a.name,a.surname,a.course_code,a.midterm,a.lab,a.final_exam,a.year_end_grade);
            }
        }
    }
    fclose(fp);
    return;
}

int sort(const void*a,const void*b){
    struct graderecord*s1=(struct graderecord*)a;
    struct graderecord*s2=(struct graderecord*)b;
    return s1->id - s2->id;
}

void sortanddisplay(){
    struct graderecord a;
    FILE *fp=fopen("grades.bin","rb");
    if (fp==NULL){perror("error opening filee");return;}
    fseek(fp,0,SEEK_END);
    long length=ftell(fp);
    int count=length/sizeof(struct graderecord);
    if (count==0){
        printf("no students to sort");
        fclose(fp);
        return;
    }
    struct graderecord *arr=(struct graderecord*) malloc (count * sizeof(struct graderecord));
    if (arr==NULL){
        perror("memory allocation failed");
        fclose(fp);
        return ;
    }
    fread(arr,sizeof(struct graderecord),count,fp);
    fclose(fp);
    qsort(arr,count,sizeof(struct graderecord),sort);

    fp=fopen("grades.bin","wb");
    if (fp==NULL){
        printf("error");
        free(arr);
        return;
    }
    fwrite(arr,sizeof(struct graderecord),count,fp);
    fclose (fp);
    free(arr);
    return;



}
