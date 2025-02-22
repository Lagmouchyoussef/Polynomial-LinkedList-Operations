#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
    short int part;
    struct List *next;
} NumberList;

NumberList *groupDigits(char *S) {
    int len = strlen(S);
    int start = len % 4;
    if (start == 0) start = 4;

    NumberList *head = NULL;
    NumberList *current = NULL;

    while (*S != '\0') {
        char temp[5] = {0};
        strncpy(temp, S, start);
        S += start;
        start = 4;

        NumberList *newNode = (NumberList *)malloc(sizeof(NumberList));
        newNode->part = atoi(temp);
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            current->next = newNode;
        }
        current = newNode;
    }

    return head;
}

void printList(NumberList *list) {
    while (list != NULL) {
        printf("%d ", list->part);
        list = list->next;
    }
    printf("\n");
}

int main() {
    char S[] = "330104660000027";
    NumberList *list = groupDigits(S);

    printf("List representing the number: ");
    printList(list);

    return 0;
}