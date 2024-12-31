#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <conio.h>

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
typedef struct student student;
struct student
{
    int id;
    char name[100];
    int numberOfGrades;
    int *grades;
    int score;
};
void displayStudent(student *s)
{
    if (s)
    {
        printf("ID: %d\n", s->id);
        printf("Name: %s\n", s->name);
        printf("Grades: ");
        for (int i = 0; i < s->numberOfGrades; i++)
        {
            printf("%d ", s->grades[i]);
        }
        printf("the score: %d", s->score);
        printf("\n");
    }
}
char letterGrades(int score, int numberOfGrades)
{
    int avgScore = score / numberOfGrades;
    if (avgScore >= 90)
    {
        return 'A';
    }
    else if (avgScore >= 80)
    {
        return 'B';
    }
    else if (avgScore >= 70)
    {
        return 'C';
    }
    else if (avgScore >= 60)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}
int main()
{
    int choise=0,index=0,indexOfStudent=0;
    char ch;
    int sizeOfstudents=20;
    student **students = malloc(sizeOfstudents * sizeof(student *));

    do
    {
        system("cls");
        char arr[4][20]= {"1-add","2-update","3-display","4-exit"};
        // print menu
        for(int i=0; i<4; i++)
        {
            //change the color of row
            if(choise==i)
            {
                SetColor(1);
                printf("%s <-\n",arr[i]);
            }
            else
            {
                SetColor(255);
                printf("%s\n",arr[i]);
            }
        }
        ch=getch();
        // character is row or enter
        if(ch==-32)
        {
            ch=getch();
            switch(ch)
            {
            case(80):
            {
                if(choise<3)
                {
                    choise++;
                }
                else
                {
                    choise=0;
                }
            }
            break;
            case(72):
            {
                if(choise>0)
                {
                    choise--;
                }
                else
                {
                    choise=3;
                }
            }
            break;

            }
        }
        else
        {
            int c;
            system("cls");
            // add stuent
            if(choise==0)
            {

                students[indexOfStudent] = malloc(sizeof(student));

                students[indexOfStudent]->id = indexOfStudent+1;

                char name[100];
                printf("enter name of student : ");
                scanf("%s", name);
                strcpy(students[indexOfStudent]->name, name);

                int numberOfGrades;
                printf("enter the number of subjects : ");
                scanf("%d",&numberOfGrades);
                students[indexOfStudent]->numberOfGrades = numberOfGrades;

                students[indexOfStudent]->grades = malloc(numberOfGrades * sizeof(int));

                int score=0;
                for (int j = 0; j < students[indexOfStudent]->numberOfGrades; j++)
                {
                    int grades;
                    printf("enter the grade of subject %d : ",j+1);
                    scanf("%d",&grades);
                    score+=grades;
                    students[indexOfStudent]->grades[j] = grades;
                }
                students[indexOfStudent]->score = score;
                indexOfStudent++;
                printf("\ncreate successful. press any key to finish");
                getch();

            }
            //updata data of student
            else if(choise==1)
            {
                int id;
                printf("enter student ID to update: ");
                scanf("%d", &id);
                if (id > 0 && id <= indexOfStudent)
                {
                    student *s = students[id - 1];
                    printf("student: %s\n", s->name);
                    printf("do you want to updating this student ?(Y/N)");
                    char select;
                    scanf(" %c",&select);
                    if(select=='Y'||select=='y')
                    {
                        printf("enter new number of subjects: ");
                        scanf("%d", &s->numberOfGrades);

                        s->grades = realloc(s->grades, s->numberOfGrades * sizeof(int));
                        int score=0;
                        for (int j = 0; j < s->numberOfGrades; j++)
                        {
                            int grades;
                            printf("enter the grade of subject %d : ",j+1);
                            scanf("%d",&grades);
                            score+=grades;
                            s->grades[j] = grades;
                        }
                        s->score = score;
                        printf("\nstudent updated successfully. press any key to finish");
                    }

                }
                else
                {
                    printf("invalid ID press any key to finish");
                }
                getch();

            }

            else if (choise==2)
            {
                int choise2=0;
                do
                {
                    system("cls");
                    char arr2[6][50]= {"1-display all student","2-display student with highest averager score","3-display average score of all student","4-display a list of student pass","5-display a list of student fail","6-exit"};
                    // print menu
                    for(int i=0; i<6; i++)
                    {
                        //change the color of row
                        if(choise2==i)
                        {
                            SetColor(1);
                            printf("%s <-\n",arr2[i]);
                        }
                        else
                        {
                            SetColor(255);
                            printf("%s\n",arr2[i]);
                        }
                    }
                    ch=getch();
                    // character is row or enter
                    if(ch==-32)
                    {
                        ch=getch();
                        switch(ch)
                        {
                        case(80):
                        {
                            if(choise2<5)
                            {
                                choise2++;
                            }
                            else
                            {
                                choise2=0;
                            }
                        }
                        break;
                        case(72):
                        {
                            if(choise2>0)
                            {
                                choise2--;
                            }
                            else
                            {
                                choise2=5;
                            }
                        }
                        break;

                        }
                    }
                    else
                    {
                        int c;
                        system("cls");
                        // add stuent
                        if(choise2==0)
                        {
                            if(indexOfStudent>0)
                            {
                                for (int i = 0; i < indexOfStudent; i++)
                                {
                                    printf("ID: %d\n", students[i]->id);
                                    printf("Name: %s\n", students[i]->name);
                                    printf("the Average score: %.2f\n", (float)(students[i]->score/students[i]->numberOfGrades));
                                    printf("the Grade: %c\n", letterGrades(students[i]->score,students[i]->numberOfGrades));
                                    char *status="fail";
                                    if((students[i]->score/students[i]->numberOfGrades)>60)
                                    {
                                        status="pass";
                                    }
                                    printf("the student is %s\n\n",status);
                                }
                            }
                            else
                            {
                                printf("the list of stuent is empty\n");
                            }

                            printf("press any key to finish");
                            getch();
                        }
                        else if(choise2==1)
                        {
                            if(indexOfStudent>0)
                            {
                                double hieghtScore=0,averageScore;
                                int indexHighestScore=0;
                                for (int i = 0; i < indexOfStudent; i++)
                                {
                                    averageScore = students[i]->score/students[i]->numberOfGrades;
                                    if(averageScore>hieghtScore)
                                    {
                                        indexHighestScore = i;
                                        hieghtScore = averageScore;
                                    }

                                }
                                printf("ID: %d\n", students[indexHighestScore]->id);
                                printf("Name: %s\n", students[indexHighestScore]->name);
                                printf("the Average score: %.2f\n", (float)(students[indexHighestScore]->score/students[indexHighestScore]->numberOfGrades));
                                printf("the Grade: %c\n", letterGrades(students[indexHighestScore]->score,students[indexHighestScore]->numberOfGrades));

                            }
                            else
                            {
                                printf("the list of stuent is empty\n");
                            }

                            printf("\npress any key to finish");
                            getch();

                        }
                        else if (choise2==2)
                        {
                            if(indexOfStudent>0)
                            {
                                double averageScoreOfAllStudents=0;
                                for (int i = 0; i < indexOfStudent; i++)
                                {
                                    averageScoreOfAllStudents += (students[i]->score/students[i]->numberOfGrades);

                                }
                                printf("the average score of all students %.2f", (float)(averageScoreOfAllStudents/indexOfStudent));

                            }
                            else
                            {
                                printf("the list of stuent is empty\n");
                            }

                            printf("\npress any key to finish");
                            getch();

                        }
                        else if (choise2==3)
                        {
                            if(indexOfStudent>0)
                            {
                                for (int i = 0; i < indexOfStudent; i++)
                                {
                                    if((students[i]->score/students[i]->numberOfGrades)>=60)
                                    {
                                        printf("ID: %d\n", students[i]->id);
                                        printf("Name: %s\n", students[i]->name);
                                        printf("the Average score: %.2f\n", (float)(students[i]->score/students[i]->numberOfGrades));
                                        printf("the Grade: %c\n", letterGrades(students[i]->score,students[i]->numberOfGrades));
                                        printf("the student is %s\n\n","pass");
                                    }
                                }
                            }
                            else
                            {
                                printf("the list of stuent is empty\n");
                            }

                            printf("\npress any key to finish");
                            getch();

                        }
                        else if (choise2==4)
                        {
                            if(indexOfStudent>0)
                            {
                                for (int i = 0; i < indexOfStudent; i++)
                                {
                                    if((students[i]->score/students[i]->numberOfGrades)<60)
                                    {
                                        printf("ID: %d\n", students[i]->id);
                                        printf("Name: %s\n", students[i]->name);
                                        printf("the Average score: %.2f\n", (float)(students[i]->score/students[i]->numberOfGrades));
                                        printf("the Grade: %c\n", letterGrades(students[i]->score,students[i]->numberOfGrades));
                                        printf("the student is %s\n\n","fail");
                                    }
                                }
                            }
                            else
                            {
                                printf("the list of stuent is empty\n");
                            }

                            printf("\npress any key to finish");
                            getch();


                        }
                    }


                }
                while(choise2!=5||ch!=13);

            }
        }
        if(sizeOfstudents==index)
        {
            sizeOfstudents +=5;
            students = realloc(students, sizeOfstudents * sizeof(student *));
        }

    }
    while(choise!=3||ch!=13);


    SetColor(255);

    return 0;
}







