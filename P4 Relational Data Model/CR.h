/**
 * @file CR.h
 * @author MaKayla Robinson - mrobin45
 */
#ifndef _CR_h
#define _CR_h

#include <stdio.h>

typedef struct CRList CRList;

extern CRList* new_CRList(void);
extern void insert_CRList(CRList* list,char* courseGiven, char* roomGiven);
extern CRList* deleteElement_CRList(CRList* list,char* courseGiven, char* roomGiven);
extern CRList* lookup_CRList(char* c, char* r, CRList* list);

void print_CRHeader();
void print_CRFooter();
extern void print_CRList(CRList* list);

void print_CHeader();
void print_CFooter();
extern void print_CList(CRList* list);

#endif