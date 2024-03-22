/**
 * @file Database.h
 * @author MaKayla Robinson - mrobin45
 */
#ifndef Database_h
#define Database_h

#include <stdio.h>

#include "CSG.h"
#include "CP.h"
#include "SNAP.h"
#include "CDH.h"
#include "CR.h"

#define TABLE_SIZE 7

typedef struct CSG CSG;
typedef struct CP CP;
typedef struct CDH CDH;
typedef struct CR CR;
typedef struct SNAP SNAP;
typedef struct Database* Database;

struct Database{
    int size;
    int count;
  
    CSGList* csgBuckets[TABLE_SIZE];
    SNAPList* snapBuckets[TABLE_SIZE];
    CDHList* cdhBuckets[TABLE_SIZE];
    CRList* crBuckets[TABLE_SIZE];
    CPList* cpBuckets[TABLE_SIZE];
};

extern Database new_Database(int size);

//insert functions
extern void insert_CSGDatabase(char* c, int s, char* g, Database list);
extern void insert_SNAPDatabase(int s, char* n, char* a, char* p, Database list);
extern void insert_CDHDatabase(char* c, char* d, char* h, Database list);
extern void insert_CRDatabase(char* c, char* r, Database list);
extern void insert_CPDatabase(char* c, char* pr, Database list);

//delete functions
extern void delete_CSGDatabase(int s, char* c, char* g, Database list);
extern void delete_SNAPDatabase(int s, char* n, char* a, char* p, Database list);
extern void delete_CDHDatabase(char* c, char* d, char* h, Database list);
extern void delete_CRDatabase(char* c, char* r, Database list);
extern void delete_CPDatabase(char* c, char* pr, Database list);

//lookup functions
extern void lookup_CSGDatabase(char* c, int s, char* g, Database list);
extern void lookup_SNAPDatabase(int s, char* n, char* a, char* p, Database list);
extern void lookup_CDHDatabase(char* c, char* h, char* d, Database list);
extern void lookup_CRDatabase(char* c, char* r, Database list);
extern void lookup_CPDatabase(char* c, char* p, Database list);

//Part 2 methods
extern CSGList* checkStudentGrade(Database list, char* n, char* c);
extern void whereIsStudent(char* n, char* h, char* d, Database list);

//Print Database
extern void print_Database(Database list);

#endif