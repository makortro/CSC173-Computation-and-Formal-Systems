/**
 * @file CSG.h
 * @author MaKayla Robinson - mrobin45
 */
#ifndef _CSG_h
#define _CSG_h

#include <stdio.h>

typedef struct CSGList CSGList;

extern CSGList* new_CSGList(void);
extern void insert_CSGList(CSGList* list, char* courseGiven, int idGiven, char* gradeGiven );
extern CSGList* deleteElement_CSGList(CSGList* list, char* courseGiven, int idGiven, char* gradeGiven );
extern CSGList* lookup_CSGList(char* c, int s, char* g, CSGList* list);

void print_CSGHeader();
void print_CSGFooter();
extern void print_CSGList(CSGList* list);

#endif