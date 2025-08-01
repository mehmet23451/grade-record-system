#ifndef GRADERECORD_H
#define GRADERECORD_H

struct graderecord {
    int id;
    char name[30];
    char surname[30]; 
    char course_code[10];
    float midterm; 
    float lab; 
    float final_exam;
    float year_end_grade;
};

void addstudent();
void liststudents();
void modify();
void delete();
void search();
void display();
void sortanddisplay();

#endif
