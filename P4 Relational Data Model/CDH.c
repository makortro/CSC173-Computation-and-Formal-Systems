/**
 * @file CDH.c
 * @author MaKayla Robinson - mrobin45
 * 
 */
#include "CDH.h"
#include <stdlib.h>
#include <string.h>

typedef struct CDH{
    char* Course;
    char* Day;
    char* Hour;
    struct CDH *next;
} CDH;

struct CDHList {
    struct CDH* head;
    int size;
};

void print_CDH(CDH* list);

/*** CONSTRUCTORS ***/

static CDH* new_CDH(char* c, char* d, char* h){
    CDH* new = (CDH*)malloc(sizeof(CDH));
    if(new == NULL){
        return NULL;
    }
    new->Hour = h;
    new->Course = c;
    new->Day = d;
    new->next = NULL;
    
    return new;
};

CDHList* new_CDHList(){
    CDHList* list = (CDHList*)malloc(sizeof(struct CDHList));
    list->head = NULL;
    list->size = 0;
    return list;
}

/*** ACCESSORS ***/

CDHList* lookup_CDHList(char* c, char* d, char* h, CDHList* list) { //TODO UPDATE ALL LOOKUPS
    CDH* temp = list->head;
    CDHList* found = new_CDHList();

    //check which value(s) passed in; c will always be passed in (hash key)
    if (strcmp(d, "*") == 0 && strcmp(h, "*") == 0) { //course only
        while(temp != NULL) {           
            if(temp->Course == c) {
                insert_CDHList(found, temp->Course, temp->Hour, temp->Day);
            }
            temp = temp->next;
        }
    } else if (strcmp(h, "*") == 0) { //course and day
        while(temp != NULL) {           
            if(temp->Course == c && temp->Day == d) {
                insert_CDHList(found, temp->Course, temp->Hour, temp->Day);
            }
            temp = temp->next;
        }
    } else if (strcmp(d, "*") == 0) { //course and hour
        while(temp != NULL) {           
            if(temp->Course == c && temp->Hour == h) {
                insert_CDHList(found, temp->Course, temp->Day, temp->Hour);
            }
            temp = temp->next;
        }
    } else { //course, day, hour
        while(temp != NULL) {           
            if(temp->Course == c && temp->Day == d && temp->Hour == h) {
                insert_CDHList(found, temp->Course, temp->Day, temp->Hour);
            }
            temp = temp->next;
        }
    }

    return found;
}

/*** MUTATORS ***/

void insert_CDHList(CDHList* list, char* c, char* d, char* h){
    CDH* data = new_CDH(c, d, h);
    if(list->head == NULL){
        list->head = data;
        list->size++;
    }else{
        CDH* temp = list->head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = data;
        list->size++;
    }
}

CDHList* deleteElement_CDHList(CDHList* list, char* c, char* day, char* hour){
    CDHList* todelete = lookup_CDHList(c, day, hour, list);
    CDH* temp = list->head; //iterate OG list
    CDH* delete = todelete->head; //iterate delete list
    
    while (delete->next != NULL) { 
        if (list->head->Course == todelete->head->Course &&
            list->head->Day == todelete->head->Day &&
            list->head->Hour == todelete->head->Hour) { //properly removing head DON'T TOUCH
            list->head = list->head->next;
            delete = delete->next;
            temp = temp->next;
        }

        while(delete->next != NULL) {
            if (temp->next->Course != delete->Course &&
                    temp->next->Day != delete->Day &&
                    temp->next->Hour != delete->Hour) {
                temp = temp->next;
            } else {
                CDH* newNext = temp->next->next;
                temp->next = newNext;
                delete = delete->next;
            }
        }
    }

    
    return list;
}

/*** PRINT FUNCTIONS ***/

void print_CDHHeader() {
    printf("\n----------------\n");
    printf("Course  Day Hour");
    printf("\n----------------\n");
}

void print_CDHFooter() {
    printf("----------------\n");
}

void print_CDH(CDH* list){
    printf("%s\t", list->Course);
    printf("%s   ", list->Day);
    printf("%s\n", list->Hour);
}

void print_CDHList(CDHList* list){
    if(list->head != NULL){
        CDH* temp = list->head;
        while(temp->next != NULL){
            print_CDH(temp);
            temp = temp->next;
        }
        print_CDH(temp);
    }
}