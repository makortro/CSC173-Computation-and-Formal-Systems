/**
 * @file SNAP.h
 * @author MaKayla Robinson - mrobin45
 */
#ifndef _SNAPList_h
#define _SNAPList_h

#include <stdio.h>

//typedef struct SNAP SNAP;
typedef struct SNAPList SNAPList;

extern SNAPList* new_SNAPList(void);
extern void insert_SNAPList(SNAPList* list,int idGiven, char* nameGiven, char* addressGiven, char* phoneGiven);
extern SNAPList* deleteElement_SNAPList(SNAPList* list, int idGiven, char* nameGiven, char* addressGiven, char* phoneGiven);
extern SNAPList* lookup_SNAPList(int s, char* n, char* a, char* p, SNAPList* list);

extern void print_SNAPList(SNAPList* list);
void print_SNAPHeader();
void print_SNAPFooter();

void print_SNHeader();
void print_SNFooter();
extern void print_SNList(SNAPList* list);

#endif