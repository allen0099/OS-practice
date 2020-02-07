#include <stdio.h>
#include <stdlib.h>

typedef struct reg {
    int ID;
    int score;
    struct reg *next;
} tReg;

tReg *AddStudent(tReg *p, int ID, int score) {
    p->next = (tReg *) malloc(sizeof(tReg));
    p->next->ID = ID;
    p->next->score = score;
    p->next->next = NULL;
    return (p->next);
}

tReg *rev(tReg *p) {
    tReg *current = p;
    tReg *tail = NULL;
    tReg *prev = NULL, *next = NULL;
    while (current != NULL) {
        if (current->next == NULL) {
            tail = current;
        }
        next = current->next; // Tmp
        current->next = prev; // Save prev
        prev = current; // Update prev
        current = next; // Update current
    }
    return tail;
}

int main(void) {
    tReg *pStudent;
    tReg *head;
    int i;
    pStudent = (tReg *) malloc(sizeof(tReg));
    head = pStudent; // 一定要先有頭
    pStudent->ID = 1;
    pStudent->score = 99;
    pStudent->next = NULL;
    pStudent = AddStudent(pStudent, 20, 40);
    pStudent = AddStudent(pStudent, 52, 100);
    pStudent = head;
    printf("Origin:\n");
    while (pStudent != NULL) {
        printf("ID: %d with score: %d \n",
               pStudent->ID, pStudent->score);
        pStudent = pStudent->next;
    }
    printf("Reverse:\n");
    pStudent = rev(head);
    while (pStudent != NULL) {
        printf("ID: %d with score: %d \n",
               pStudent->ID, pStudent->score);
        pStudent = pStudent->next;
    }
    return 0;
}