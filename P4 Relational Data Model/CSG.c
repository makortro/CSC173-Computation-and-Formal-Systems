/**
 * @file CSG.c
 * @author MaKayla Robinson - mrobin45
 */
#include "CSG.h"
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 7

typedef struct CSG{
    char* Course;
    int StudentId;
    char* Grade;
    struct CSG *next;
} CSG;

struct CSGList {
    struct CSG* head;
    int size;
};

static void print_CSG(CSG* list);

/*** CONSTRUCTORS ***/

static CSG* new_CSG(char* courseGiven, int idGiven, char* gradeGiven ){
    CSG* list = (CSG*)malloc(sizeof(CSG));
    if(list == NULL){
        return NULL;
    }
    list->next = NULL;
    list->StudentId = idGiven;
    list->Course = courseGiven;
    list->Grade = gradeGiven;
    
    return list;
};

CSGList* new_CSGList(){
    CSGList *list = (CSGList*)malloc(sizeof(struct CSGList));
    list->head = NULL;
    list->size = 0;
    return list;
}

/*** ACCESSORS ***/

CSGList* lookup_CSGList(char* c, int s, char* g, CSGList* list) { //TODO UPDATE ALL LOOKUPS
    CSG* temp = list->head;
    CSGList* found = new_CSGList();

    //check which value(s) passed in; s will always be passed in (hash key)
    if (strcmp(c, "*") == 0 && strcmp(g, "*") == 0) { //stuID only
        while(temp != NULL) {           
            if(temp->StudentId == s) {
                insert_CSGList(found, temp->Course, temp->StudentId, temp->Grade);
            }
            temp = temp->next;
        }
    } else if (strcmp(g, "*") == 0) { //course and stuID
        while(temp != NULL) {           
            if(temp->Course == c && temp->StudentId == s) {
                insert_CSGList(found, temp->Course, temp->StudentId, temp->Grade);
            }
            temp = temp->next;
        }
    } else if (strcmp(c, "*") == 0) { //stuID and grade
        while(temp != NULL) {           
            if(temp->StudentId == s && temp->Grade == g) {
                insert_CSGList(found, temp->Course, temp->StudentId, temp->Grade);
            }
            temp = temp->next;
        }
    } else { //course, stuID, grade
        while(temp != NULL) {           
            if(temp->Course == c && temp->StudentId == s && temp->Grade == g) {
                insert_CSGList(found, temp->Course, temp->StudentId, temp->Grade);
            }
            temp = temp->next;
        }
    }

    return found;
}

/*** MUTATORS ***/

void insert_CSGList(CSGList* list, char* c, int s, char* g ){
    CSG* new = new_CSG(c, s, g);

    if(list->head == NULL){
        list->head = new;
        list->size++;
    } else {
        CSG* temp = list->head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new;
        list->size++;
    }
}

CSGList* deleteElement_CSGList(CSGList* list, char* courseGiven, int idGiven, char* gradeGiven ){
    CSGList* todelete = lookup_CSGList(courseGiven, idGiven, gradeGiven, list);
    CSG* temp = list->head; //iterate OG list
    CSG* delete = todelete->head; //iterate delete list
    
    while (delete->next != NULL) { 
        if (list->head->StudentId == todelete->head->StudentId &&
            list->head->Course == todelete->head->Course &&
            list->head->Grade == todelete->head->Grade) { //properly removing head DON'T TOUCH
            list->head = list->head->next;
            delete = delete->next;
            temp = temp->next;
        }

        printf("\ntemp = ");
            print_CSG(temp);
            printf("delete = %s, %i, %s", delete->Course, delete->StudentId, delete->Grade);
            printf("\n");
        while(delete->next != NULL) {
            if (temp->next->StudentId != delete->StudentId &&
                    temp->next->Course != delete->Course &&
                    temp->next->Grade != delete->Grade) {
                temp = temp->next;
            } else {
                CSG* newNext = temp->next->next;
                temp->next = newNext;
                delete = delete->next;
            }
        }
    }

    /*
                                        newNext
                        temp            t.next  t.n.next
    list:       csg1    csg2    csg3    csg4    csg5    csg6    csg7    csg8    csg9
                        t.head  t.h.next
    todelete:   csg1    csg3    csg4    NULL                              
                                delete  r.next
    */

    return list;
}

/*** PRINT FUNCTIONS ***/

void print_CSGHeader() {
    printf("\n--------------------\n");
    printf("Course  StuID  Grade");
    printf("\n--------------------\n");
}

void print_CSGFooter() {
    printf("--------------------\n");
}

static void print_CSG(CSG* list){
    printf("%s\t", list->Course);
    printf("%i\t", list->StudentId);
    printf("%s\t\n", list->Grade);
}

void print_CSGList(CSGList* list){
    if(list->head != NULL){
        CSG* temp = list->head;
        while(temp->next != NULL){
            print_CSG(temp);
            temp = temp->next;
        }
        print_CSG(temp);
    }
}