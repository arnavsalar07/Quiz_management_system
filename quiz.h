#ifndef QUIZ_H
#define QUIZ_H

struct Quiz {
    char question[200];
    char optionA[50];
    char optionB[50];
    char optionC[50];
    char optionD[50];
    char correct;
};

void addQuestion();
void takeQuiz(int id);
void viewAllResults();
void viewMyResult(int id);
void editQuestion();

#endif