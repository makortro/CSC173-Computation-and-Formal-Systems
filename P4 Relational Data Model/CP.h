/**
 * @file CP.h
 * @author MaKayla Robinson - mrobin45
 */
#ifndef _CP_h
#define _CP_h

#include <stdio.h>

typedef struct CPList CPList;

extern CPList* new_CPList(void);
extern void insert_CPList(CPList* list,char* courseGiven, char* preReqGiven);
extern CPList* deleteElement_CPList(CPList* list, char* courseGiven, char* preReqGiven);
extern CPList* lookup_CPList(char* c, char* p, CPList* list);

extern void print_CPList(CPList* list);
void print_CPHeader();
void print_CPFooter();

#endif