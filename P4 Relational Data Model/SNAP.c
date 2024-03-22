/**
 * @file SNAP.c
 * @author MaKayla Robinson - mrobin45
 */
#include "SNAP.h"
#include <stdlib.h>
#include <string.h>

typedef struct SNAP{
    int StudentId;
    char* Name;
    char* Address;
    char* Phone;
    struct SNAP *next;
} SNAP;

struct SNAPList {
    struct SNAP* head;
    int size;
};

static void print_SN(SNAP* list);

/*** CONSTRUCTORS ***/

static SNAP* new_SNAP(int idGiven, char* nameGiven, char* addressGiven, char* phoneGiven ){
    SNAP* list = (SNAP*)malloc(sizeof(SNAP));
    if(list == NULL){
        return NULL;
    }
    list->next = NULL;
    list->StudentId = idGiven;
    list->Name = nameGiven;
    list->Address = addressGiven;
    list->Phone = phoneGiven;

    
    return list;
};

SNAPList* new_SNAPList(){
    SNAPList *list = (SNAPList*)malloc(sizeof(struct SNAPList));
    list->head = NULL;
    list->size = 0;
    return list;
}

/*** ACCESSORS ***/

//restricted to inquiring w/ stuId and/or name only
SNAPList* lookup_SNAPList(int s, char* n, char* a, char* p, SNAPList* list) { //TODO UPDATE ALL LOOKUPS
    SNAP* temp = list->head;
    SNAPList* found = new_SNAPList();

    //check which value(s) passed in; s will always be passed in (hash key)
    if (strcmp(n, "*") == 0 && strcmp(a, "*") == 0 && strcmp(p, "*") == 0) { // stuID only
        while(temp != NULL) {           
            if(temp->StudentId == s) {
                insert_SNAPList(found, temp->StudentId, temp->Name, temp->Address, temp->Phone);
            }
            temp = temp->next;
        }
    } else if (s == 0 && strcmp(a, "*") == 0 && strcmp(p, "*") == 0) { // name only (used for checkStudentGrade)
        while(temp != NULL) {           
            if(temp->Name == n) {
                insert_SNAPList(found, temp->StudentId, temp->Name, temp->Address, temp->Phone);
            }
            temp = temp->next;
        }
    } else if (strcmp(a, "*") == 0 && strcmp(p, "*") == 0) { //stuID and name
        while(temp != NULL) {           
            if(temp->StudentId == s && temp->Name == n) {
                insert_SNAPList(found, temp->StudentId, temp->Name, temp->Address, temp->Phone);
            }
            temp = temp->next;
        }
    } else { //stuID, name, address, phone
        while(temp != NULL) {           
            if(temp->StudentId == s && temp->Name == n && temp->Address == a && temp->Phone == p) {
                insert_SNAPList(found, temp->StudentId, temp->Name, temp->Address, temp->Phone);
            }
            temp = temp->next;
        }
    }

    return found;
}

/*** MUTATORS ***/

void insert_SNAPList(SNAPList* list,int idGiven, char* nameGiven, char* addressGiven, char* phoneGiven ){
    SNAP* data = new_SNAP(idGiven, nameGiven, addressGiven, phoneGiven);
    if(list->head == NULL){
        list->head = data;
        list->size++;
    }else{
        SNAP* temp = list->head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = data;
        list->size++;
    }
}

SNAPList* deleteElement_SNAPList(SNAPList* list, int idGiven, char* name, char* address, char* phone){
    SNAPList* todelete = lookup_SNAPList(idGiven, name, address, phone, list);
    SNAP* temp = list->head; //iterate OG list
    SNAP* delete = todelete->head; //iterate delete list

    if (temp->StudentId == delete->StudentId) { //item to delete is head
            list->head = list->head->next;
            temp = temp->next;
            delete = delete->next;
            list->size--;
    }
        
    for (int i = 0; i < todelete->size; i++) { //cycle thru todelete list
        if (temp->StudentId == delete->StudentId) {
            SNAP* newNext = temp->next->next;
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

void print_SNAPHeader() {
    printf("\n------------------------------------------------\n");
    printf("StuId   Name            Address            Phone");
    printf("\n------------------------------------------------\n");
}

void print_SNAPFooter() {
    printf("------------------------------------------------\n");
}

static void print_SNAP(SNAP* list){
    printf("%d\t", list->StudentId);
    printf("%s\t", list->Name);
    printf("%s\t", list->Address);
    printf("%s\n", list->Phone);
}

void print_SNAPList(SNAPList* list){
    if(list->head != NULL){
        SNAP* temp = list->head;
        while(temp->next != NULL){
            print_SNAP(temp);
            temp = temp->next;
        }
        print_SNAP(temp);
    }
}

void print_SNHeader() {
    printf("\n-----------------\n");
    printf("StuId   Name");
    printf("\n-----------------\n");
}

void print_SNFooter() {
    printf("-----------------\n");
}

static void print_SN(SNAP* list){
    printf("%d\t", list->StudentId);
    printf("%s\t\n", list->Name);
}

void print_SNList(SNAPList* list) {
    if(list->head != NULL){
        SNAP* temp = list->head;
        while(temp->next != NULL){
            print_SN(temp);
            temp = temp->next;
        }
        print_SN(temp);
    }
}