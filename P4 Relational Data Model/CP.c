/**
 * @file CP.c
 * @author MaKayla Robinson - mrobin45
 */
#include "CP.h"
#include <stdlib.h>
#include <string.h>

typedef struct CP{
    char* Course;
    char* Prereq;
    struct CP *next;
} CP;

struct CPList {
    struct CP* head;
    int size;
};

/*** CONSTRUCTORS ***/

static CP* new_CP(char* courseGiven, char* preReqGiven ){
    CP* list = (CP*)malloc(sizeof(CP));
    if(list == NULL){
        return NULL;
    }
    list->next = NULL;
    list->Course = courseGiven;
    list->Prereq = preReqGiven;
    
    return list;
};

CPList* new_CPList(){
    CPList *list = (CPList*)malloc(sizeof(struct CPList));
    list->head = NULL;
    list->size = 0;
    return list;
}

/*** ACCESSORS ***/

CPList* lookup_CPList(char* c, char* p, CPList* list) { //TODO UPDATE ALL LOOKUPS
    CP* temp = list->head;
    CPList* found = new_CPList();

    //check which value(s) passed in; c will always be passed in (hash key)
    if (strcmp(p, "*") == 0) { //course only
        while(temp != NULL) {           
            if(temp->Course == c) {
                insert_CPList(found, temp->Course, temp->Prereq);
            }
            temp = temp->next;
        }
    } else { //course, prereq
        while(temp != NULL) {           
            if(temp->Course == c && temp->Prereq == p) {
                insert_CPList(found, temp->Course, temp->Prereq);
            }
            temp = temp->next;
        }
    }

    return found;
}

/*** MUTATORS ***/

void insert_CPList(CPList* list,char* courseGiven, char* preReqGiven){
    CP* data = new_CP(courseGiven, preReqGiven);
    if(list->head == NULL){
        list->head = data;
        list->size++;
    }else{
        CP* temp = list->head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = data;
        list->size++;
    }
}

CPList* deleteElement_CPList(CPList* list, char* courseGiven, char* prereq ){
    CPList* todelete = lookup_CPList(courseGiven, prereq, list);
    CP* temp = list->head; //iterate OG list
    CP* delete = todelete->head; //iterate delete list

    if (temp->Course == delete->Course) { //item to delete is head
            list->head = list->head->next;
            temp = temp->next;
            delete = delete->next;
            list->size--;
    }
        
    for (int i = 0; i < todelete->size; i++) { //cycle thru todelete list
        if (temp->Course == delete->Course) {
            CP* newNext = temp->next->next;
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

void print_CPHeader() {
    printf("\n--------------------\n");
    printf("Course  Prerequisite");
    printf("\n--------------------\n");
}

void print_CPFooter() {
    printf("--------------------\n");
}

static void print_CP(CP* list){
    printf("%s\t", list->Course);
    printf("%s\n", list->Prereq);
}

void print_CPList(CPList* list){
    if(list->head != NULL){
        CP* temp = list->head;
        while(temp->next != NULL){
            print_CP(temp);
            temp = temp->next;
        }
        print_CP(temp);
    }
}