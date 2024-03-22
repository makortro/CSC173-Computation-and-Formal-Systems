/**
 * @file CR.c
 * @author MaKayla Robinson - mrobin45
 */
#include "CR.h"
#include <stdlib.h>
#include <string.h>

typedef struct CR{
    char* Course;
    char* Room;
    struct CR *next;
} CR;

struct CRList {
    struct CR* head;
    int size;
};

static void print_C(CR* list);

/*** CONSTRUCTORS ***/

static CR* new_CR(char* courseGiven, char* roomGiven){
    CR* list = (CR*)malloc(sizeof(CR));
    if(list == NULL){
        return NULL;
    }
    list->next = NULL;
    list->Course = courseGiven;
    list->Room = roomGiven;
    
    return list;
};

CRList* new_CRList(){
    CRList *list = (CRList*)malloc(sizeof(struct CRList));
    list->head = NULL;
    list->size = 0;
    return list;
}

/*** ACCESSORS ***/

CRList* lookup_CRList(char* c, char* r, CRList* list) { //TODO UPDATE ALL LOOKUPS
    CR* temp = list->head;
    CRList* found = new_CRList();

    //check which value(s) passed in; c will always be passed in (hash key)
    if (strcmp(r, "*") == 0) { //course only
        while(temp != NULL) {           
            if(temp->Course == c) {
                insert_CRList(found, temp->Course, temp->Room);
            }
            temp = temp->next;
        }
    } else { //course, prereq
        while(temp != NULL) {           
            if(temp->Course == c && temp->Room == r) {
                insert_CRList(found, temp->Course, temp->Room);
            }
            temp = temp->next;
        }
    }

    return found;
}

/*** MUTATORS ***/

void insert_CRList(CRList* list,char* courseGiven, char* roomGiven){
    CR* data = new_CR(courseGiven, roomGiven);
    if(list->head == NULL){
        list->head = data;
        list->size++;
    }else{
        CR* temp = list->head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = data;
        list->size++;
    }
}

CRList* deleteElement_CRList(CRList* list, char* courseGiven, char* room){
    CRList* todelete = lookup_CRList(courseGiven, room, list);
    CR* temp = list->head; //iterate OG list
    CR* delete = todelete->head; //iterate delete list

    if (temp->Course == delete->Course) { //item to delete is head
            list->head = list->head->next;
            temp = temp->next;
            delete = delete->next;
            list->size--;
    }
        
    for (int i = 0; i < todelete->size; i++) { //cycle thru todelete list
        if (temp->Course == delete->Course) {
            CR* newNext = temp->next->next;
            temp->next = newNext;
            delete = delete->next;
            list->size--;
        } else {
            temp = temp->next;      
        }
    }

    return list;  
}

/*** PRINT FUNCTIONS ***/

void print_CRHeader() {
    printf("\n--------------------------\n");
    printf("Course  Room");
    printf("\n--------------------------\n");
}

void print_CRFooter() {
    printf("--------------------------\n");
}

static void print_CR(CR* list){
    printf("%s\t", list->Course);
    printf("%s\n", list->Room);
}

void print_CRList(CRList* list){
    if(list->head != NULL){
        CR* temp = list->head;
        while(temp->next != NULL){
            print_CR(temp);
            temp = temp->next;
        }
        print_CR(temp);
    }
}

void print_CHeader() {
    printf("\n-------\n");
    printf("Course");
    printf("\n-------\n");
}

void print_CFooter() {
    printf("-------\n");
}

static void print_C(CR* list){
    printf("%s\n", list->Course);
}

void print_CList(CRList* list){
    if(list->head != NULL){
        CR* temp = list->head;
        while(temp->next != NULL){
            print_C(temp);
            temp = temp->next;
        }
        print_C(temp);
    }
}