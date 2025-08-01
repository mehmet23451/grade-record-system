#include <stdio.h>
#include "graderecord.h"

int main() {
    int answer;
    do {
        printf("Menu\n What do you want to do?\n1-Add student 2- Display all students 3- Modify student 4- Delete student 5- Search for student 6-Display optional 7- Sort and display 8-Exit\n");
        scanf("%d", &answer);
        if (answer == 1) addstudent();
        if (answer == 2) liststudents();
        if (answer == 3) modify();
        if (answer == 4) delete();
        if (answer == 5) search();
        if (answer == 6) display();
        if (answer == 7) sortanddisplay();
    } while (answer != 8);
    return 0;
}