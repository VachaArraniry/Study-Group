#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adminTest();
void teacherTest();
void adminTest();

void main () {

    int inp_choice;

    while (1)
    {
        printf("\nHello, are you a ... \n");

        printf("  1. Student\n");
        printf("  2. Professor\n");
        printf("  3. Admin\n");

        printf("Your selection \t : ");
        scanf("%d", &inp_choice);

        switch (inp_choice)
        {
        case 1:
            studentMenu();
            break;

        case 2:
            teacherTest();
            break;

        case 3:
            adminTest();
            break;
        
        default:
            system("cls");
            printf("\t  Oops Error 404\n");
            printf("\tYour selected page\n\t  does not exist");
            printf("\n\n");
            printf("      Press any key to go back");
            getchar();
            getchar();
        }
    }
}

struct Login_and_Registration
{
    char name[100], year[100], password[100];
    int nim;
};

void newStudentData (struct Login_and_Registration lrVar) {

    FILE *fileData = fopen("studentData.bin", "ab");

    if (fileData == NULL)
    {
        printf("Error Saving File");
        return;
    }
    
    fwrite(&lrVar, sizeof(struct Login_and_Registration), 1, fileData);
    fclose(fileData);
}

void studentsData (char *name, char *password) {

    FILE *fileData = fopen("studentData.bin", "ab");

    if (fileData == NULL)
    {
        printf("Error Data Not Found\n");
        return 0;
    }
    
    struct Login_and_Registration lrVar;
    while (fread(&lrVar, sizeof(struct Login_and_Registration), 1, fileData))
    {
        if (strcmp(lrVar.name, name) == 0 && strcmp(lrVar.name, name) == 0)
        {
            fclose(fileData);
            return 1;
        }
    }
    
    fclose(fileData);
    return 0;
}

void studentMenu () {

    int inp_choice;

    while (1)
    {
        printf("\nWhat would you like to do\n");

        printf("   1. Login");
        printf("   2. Registration");

        printf("Your choice \t : "); scanf("%d", &inp_choice);

        switch (inp_choice)
        {
        case 1:
            studentRegistration();
            break;

        case 2:
            studentLogin ();
            break;
        
        default:
            break;
        }
    }
}

void studentRegistration () {

}

void studentLogin () {

    struct Login_and_Registration lrVar;

    int try = 3;
    while (try >= 1)
    {
        printf("\nHello, student\n");
        printf("Name \t : "); gets(lrVar.name);
        printf("password \t : "); gets(lrVar.password);
        try--;
    }
}

void teacherTest () {
    printf("this is teacher");
}

void adminTest () {
    printf("this is admin");
}