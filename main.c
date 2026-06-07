#include <stdio.h>
#include "quiz.h"

int teacherLogin();
int studentLogin(char username[], int *id);
void signup();

int main() {
    int choice, ch, id;
    char student[50];

    printf("\n1. Teacher\n2. Student\nChoose: ");
    scanf("%d", &choice);

    if (choice == 1) {

        if (!teacherLogin()) {
            printf("Wrong login\n");
            return 0;
        }

        int ch;
        do {
            printf("\n1. Add Question\n2. Edit Question\n3. View Results\n4. Exit\n");
            scanf("%d", &ch);

            if (ch == 1) addQuestion();
            else if (ch == 2) editQuestion();
            else if (ch == 3) viewAllResults();

        } while (ch != 4);

    } else {

        printf("\n1. Signup\n2. Login\n");
        scanf("%d", &ch);

        if (ch == 1) signup();

        if (!studentLogin(student, &id)) {
            printf("Login Failed\n");
            return 0;
        }

        do {
            printf("\n1. Take Quiz\n2. View My Result\n3. Exit\n");
            scanf("%d", &ch);

            if (ch == 1) takeQuiz(id);
            else if (ch == 2) viewMyResult(id);

        } while (ch != 3);
    }

    return 0;
}