#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quiz.h"

void addQuestion() {
    FILE *fp = fopen("questions.txt", "ab");
    if (!fp) return;

    struct Quiz *q = (struct Quiz*)malloc(sizeof(struct Quiz));

    printf("\nEnter Question: ");
    getchar();
    fgets(q->question, sizeof(q->question), stdin);

    printf("Option A: ");
    fgets(q->optionA, sizeof(q->optionA), stdin);

    printf("Option B: ");
    fgets(q->optionB, sizeof(q->optionB), stdin);

    printf("Option C: ");
    fgets(q->optionC, sizeof(q->optionC), stdin);

    printf("Option D: ");
    fgets(q->optionD, sizeof(q->optionD), stdin);

    printf("Correct Option: ");
    scanf(" %c", &q->correct);

    fwrite(q, sizeof(struct Quiz), 1, fp);

    free(q);
    fclose(fp);

    printf("Question Added!\n");
}

void takeQuiz(int id) {
    FILE *fp = fopen("questions.txt", "rb");
    FILE *res = fopen("result.txt", "a");

    if (!fp || !res) return;

    struct Quiz *q = (struct Quiz*)malloc(sizeof(struct Quiz));

    int score = 0;
    char ans;

    while (fread(q, sizeof(struct Quiz), 1, fp)) {
        printf("\n%s", q->question);
        printf("A. %s", q->optionA);
        printf("B. %s", q->optionB);
        printf("C. %s", q->optionC);
        printf("D. %s", q->optionD);

        printf("Ans: ");
        scanf(" %c", &ans);

        if (ans == q->correct)
            score++;
    }

    fprintf(res, "%d %d\n", id, score);

    free(q);
    fclose(fp);
    fclose(res);

    printf("Score: %d\n", score);
}

void viewAllResults() {
    FILE *fp = fopen("result.txt", "r");
    if (!fp) {
        printf("No records found\n");
        return;
    }

    int id, score;
    printf("\n--- ALL RESULTS ---\n");

    while (fscanf(fp, "%d %d", &id, &score) != EOF) {
        printf("ID: %d -> Score: %d\n", id, score);
    }

    fclose(fp);
}

void viewMyResult(int id) {
    FILE *fp = fopen("result.txt", "r");
    if (!fp) return;

    int fileID, score, found = 0;

    while (fscanf(fp, "%d %d", &fileID, &score) != EOF) {
        if (fileID == id) {
            printf("Your Score: %d\n", score);
            found = 1;
        }
    }

    if (!found)
        printf("No result found\n");

    fclose(fp);
}

void editQuestion() {
    FILE *fp = fopen("questions.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");

    if (!fp || !temp) return;

    struct Quiz *q = (struct Quiz*)malloc(sizeof(struct Quiz));

    int count = 0, choice;

    printf("\nQuestions:\n");
    while (fread(q, sizeof(struct Quiz), 1, fp)) {
        count++;
        printf("%d. %s", count, q->question);
    }

    printf("Select question no: ");
    scanf("%d", &choice);

    rewind(fp);
    count = 0;

    while (fread(q, sizeof(struct Quiz), 1, fp)) {
        count++;

        if (count == choice) {
            printf("\nNew Question: ");
            getchar();
            fgets(q->question, sizeof(q->question), stdin);
        }

        fwrite(q, sizeof(struct Quiz), 1, temp);
    }

    free(q);
    fclose(fp);
    fclose(temp);

    remove("questions.txt");
    rename("temp.txt", "questions.txt");

    printf("Updated!\n");
}