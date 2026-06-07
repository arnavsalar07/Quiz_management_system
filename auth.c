#include <stdio.h>
#include <string.h>

void signup() {
    FILE *fp = fopen("users.txt", "a+");

    char user[20], pass[20], u[20], p[20];
    int id = 1000, exists = 0;

    printf("Username: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

    rewind(fp);

    while (fscanf(fp, "%s %s %d", u, p, &id) != EOF) {
        if (strcmp(user, u) == 0) {
            exists = 1;
            break;
        }
    }

    if (exists)
        printf("User already exists!\n");
    else {
        id++;
        fprintf(fp, "%s %s %d\n", user, pass, id);
        printf("Created! ID: %d\n", id);
    }

    fclose(fp);
}

int studentLogin(char username[], int *id) {
    FILE *fp = fopen("users.txt", "r");

    char u1[20], p1[20], u2[20], p2[20];
    int fileID;

    printf("Username: ");
    scanf("%s", u2);

    printf("Password: ");
    scanf("%s", p2);

    while (fscanf(fp, "%s %s %d", u1, p1, &fileID) != EOF) {
        if (strcmp(u1, u2) == 0 && strcmp(p1, p2) == 0) {
            strcpy(username, u2);
            *id = fileID;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int teacherLogin() {
    char u[20], p[20];

    printf("Teacher Username: ");
    scanf("%s", u);

    printf("Password: ");
    scanf("%s", p);

    return (strcmp(u, "admin") == 0 && strcmp(p, "1234") == 0);
}

