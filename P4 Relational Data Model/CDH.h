/**
 * @file CDH.h
 * @author MaKayla Robinson - mrobin45
 */
#ifndef _CDH_h
#define _CDH_h

#include <stdio.h>
typedef struct CDHList CDHList;

extern CDHList* new_CDHList(void);
extern void insert_CDHList(CDHList* list,char* c, char* d, char* h);
extern CDHList* deleteElement_CDHList(CDHList* list,char* c, char* d, char* h);
extern CDHList* lookup_CDHList(char* c, char* d, char* h, CDHList* list);

extern void print_CDHList(CDHList* list);
void print_CDHHeader();
void print_CDHFooter();

#endif