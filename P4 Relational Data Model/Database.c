/**
 * @file Database.c
 * @author MaKayla Robinson - mrobin45
 */
#include "Database.h"
#include "CSG.h"
#include "CP.h"
#include "CDH.h"
#include "CR.h"
#include "SNAP.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct SNAP{
    int studentID;
    char* Name;
    char* Address;
    char* Phone;
    struct SNAP *next;
};

struct SNAPList {
    struct SNAP* head;
    int size;
};

struct CSG{
    char* Course;
    int studentID;
    char* Grade;
    struct CSG *next;
};

struct CSGList {
    struct CSG* head;
    int size;
};

struct CDH{
    char* Course;
    char* Day;
    char* Hour;
    struct CDH *next;
};

struct CDHList {
    struct CDH* head;
    int size;
};

struct CR{
    char* Course;
    char* Room;
    struct CR *next;
};

struct CRList {
    struct CR* head;
    int size;
};

void freeDB(Database db);

Database new_Database(int size){
    Database list = (Database)malloc(sizeof(struct Database));
    if(list == NULL){
        return NULL;
    }
    list->size = size;

    for(int i = 0; i < TABLE_SIZE; i++) {
        list->csgBuckets[i] = new_CSGList();
        list->cdhBuckets[i] = new_CDHList();
        list->snapBuckets[i] = new_SNAPList();
        list->crBuckets[i] = new_CRList();
        list->cpBuckets[i] = new_CPList();
    }

    return list;
}

void freeDB(Database db) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        db->csgBuckets[i] = NULL;
        db->cdhBuckets[i] = NULL;
        db->snapBuckets[i] = NULL;
        db->crBuckets[i] = NULL;
        db->cpBuckets[i] = NULL;
    }
    db->size = 0;
    db = NULL;
    free(db);
}

static int hashID(int s) { //used for csg
    return s % TABLE_SIZE;
}

static int hashCourse(char* c) { //used for cdh, cp, cr
    int index = 0;
    for(int i = 0; i < strlen(c); i++){
        index = index + (int) c[i];
    }
    return index % TABLE_SIZE;
}

static int hashName(char* n) {
    int index = 0;
    for(int i = 0; i < strlen(n); i++){ //used for snap
        index = index + (int) n[i];
    }
    return index % TABLE_SIZE;
}

//insert methods
void insert_CSGDatabase(char* c, int s, char* g, Database list){
    int index = hashID(s);
    insert_CSGList(list->csgBuckets[index], c, s, g);
}
void insert_SNAPDatabase(int s, char* n, char* a, char* p, Database list){
    int index = hashName(n);
    insert_SNAPList(list->snapBuckets[index], s, n, a, p);
}
void insert_CDHDatabase(char* c, char* d, char* h, Database list){
    int index = hashCourse(c);
    insert_CDHList(list->cdhBuckets[index], c, d, h);
}
void insert_CRDatabase(char* c, char* r, Database list){
    int index = hashCourse(c);
    insert_CRList(list->crBuckets[index], c, r);
}
void insert_CPDatabase(char* c, char* pr, Database list){
    int index = hashCourse(c);
    insert_CPList(list->cpBuckets[index], c, pr);
}

//delete methods
void delete_CSGDatabase(int s, char* c, char* g, Database list){
    int index = hashID(s);
    list->csgBuckets[index] = deleteElement_CSGList(list->csgBuckets[index], c, s, g);
}

void delete_SNAPDatabase(int s, char* n, char* a, char* p, Database list){
    int index = hashName(n);
    list->snapBuckets[index] = deleteElement_SNAPList(list->snapBuckets[index], s, n, a, p);
}

void delete_CDHDatabase(char* c, char* d, char* h, Database list){
    int index = hashCourse(c);
    list->cdhBuckets[index] = deleteElement_CDHList(list->cdhBuckets[index], c, d, h);
}

void delete_CRDatabase(char* c, char* r, Database list){
    int index = hashCourse(c);
    list->crBuckets[index] = deleteElement_CRList(list->crBuckets[index], c, r);
}

void delete_CPDatabase(char* c, char* pr, Database list){
    int index = hashCourse(c);
    list->cpBuckets[index] = deleteElement_CPList(list->cpBuckets[index], c, pr);
}

//lookup functions
void lookup_CSGDatabase(char* c, int s, char* g, Database list){
    int index = hashID(s);
    print_CSGList(lookup_CSGList(c, s, g, list->csgBuckets[index]));
}

void lookup_SNAPDatabase(int s, char* n, char* a, char* p, Database list){
    int index = hashName(n);
    print_SNAPList(lookup_SNAPList(s, n, a, p, list->snapBuckets[index]));
}

void lookup_CDHDatabase(char* c, char* h, char* d, Database list){
    int index = hashCourse(c);
    print_CDHList(lookup_CDHList(c, d, h, list->cdhBuckets[index]));
}

void lookup_CRDatabase(char* c, char* r, Database list){
    int index = hashCourse(c);
    print_CRList(lookup_CRList(c, r, list->crBuckets[index]));
}

void lookup_CPDatabase(char* c, char* p, Database list){
    int index = hashCourse(c);
    print_CPList(lookup_CPList(c, p, list->cpBuckets[index]));
}

void print_Database(Database list){
    printf("\nPrinting CSG tuple...");
    print_CSGHeader();
    for(int i = 0; i< TABLE_SIZE; i++){
        print_CSGList(list->csgBuckets[i]);
    }
    print_CSGFooter();

    printf("\nPrinting CDH tuple...");
    print_CDHHeader();
    for(int i = 0; i< TABLE_SIZE; i++){
        print_CDHList(list->cdhBuckets[i]);
    }
    print_CDHFooter();

    printf("\nPrinting CP tuple...");
    print_CPHeader();
    for(int i = 0; i< TABLE_SIZE; i++){
        print_CPList(list->cpBuckets[i]);
    }
    print_CPFooter();

    printf("\nPrinting CR tuple...");
    print_CRHeader();
    for(int i = 0; i< TABLE_SIZE; i++){
        print_CRList(list->crBuckets[i]);
    }
    print_CRFooter();

    printf("\nPrinting SNAP tuple...");
    print_SNAPHeader();
    for(int i = 0; i< TABLE_SIZE; i++){
        print_SNAPList(list->snapBuckets[i]);
    }
    print_SNAPFooter();
}

//name and course provided
CSGList* checkStudentGrade(Database list, char* n, char* c) {
    //“What grade did Name get in Course?”
    /*
        for each tuple t in SNAP {
            if (t.Name == “C. Brown”) {
                let i = t.StudentId
                for each tuple s in CSG {
                    if (s.Course == “CS101” && s.StudentId == i) {
                    print s.Grade (or save for result, etc.)
                    }
                }
            }
        }
    */

    CSGList* stuInfo = new_CSGList();
    SNAP* temp1;
    CSG* temp2;
    int nameIndex = hashName(n);
    int stuID;
    int idIndex;

    //for each tuple t in SNAP {
    while (list->snapBuckets[nameIndex] != NULL && temp1 != NULL) {
        temp1 = list->snapBuckets[nameIndex]->head;
        while (temp1 != NULL) {
            //if (t.Name == "C.Brown") {
            if (strcmp(temp1->Name, n) == 0) {
                //let i = t.StudentId
                stuID = temp1->studentID; //correct stuID
                idIndex = hashID(stuID); //correct index
                
                //for each tuple s in CSG {
                while (list->csgBuckets[idIndex] != NULL && temp2 != NULL) {
                    temp2 = list->csgBuckets[idIndex]->head;
                    while (temp2 != NULL) {
                        //if (s.Course == “CS101” && s.StudentId == i) {
                        if (strcmp(temp2->Course, c) == 0 && temp2->studentID == stuID) {
                            //print s.Grade (or save for result, etc.)
                            insert_CSGList(stuInfo, temp2->Course, temp2->studentID, temp2->Grade);
                        }
                        temp2 = temp2->next;
                    }
                }
                //temp1 = temp1->next;
            }
            temp1 = temp1->next;
        }
        //temp = temp->next; --- CAUSES SEGFAULT
    }

    return stuInfo;
}

//snap for name and stuID
//csg for stuID and course
//cdh for course, day, hour
//cr for course and room
void whereIsStudent(char* n, char* h, char* d, Database list) { //name, hour, day
/*
for each tuple s in SNAP { //matching name to stuID
    if (s.Name == n) {
        let stuID = s.studentID //get stuID

        for each tuple c in CSG { //matching stuID to courses
            if (c.studentID == stuID) {
                let course = c.course //get course
                
                for each tuple d in CDH { //matching course to day, hour
                    if (d.course == course){
                        let hour = d.hour //get hour
                        let day = d.day //get day
                        or
                        add CDH to CDHList for courseInfo
                    }

                    for each tuple r in CR {
                        if (r.course == course) {
                            let room = r.room //get room
                            or
                            add CR to CRList for courseInfo
                            or
                            print -- [name] is in [course] in [room] at [hour] on [day]
                        }
                    }
                }
            }
        }
    }
}
*/
/*
for each tuple s in SNAP { //match name to stuID
    if (s.Name == n) {
        let stuID = s.studentID //get stuID

        for each tuple c in CSG { //match stuID to courses
            if (c.studentID == stuID) {
                add to list of stuCourses

                for each course in stuCourses { //match stuCourses to course, day, time
                    for each tuple d in CDH {
                        if (d.course == stuCourses.course && d.hour == hour && d.day == day) { 
                            let course = d.course

                            for each tuple r in CR { //match course to room
                                if (r.course == course) {
                                    let room = r.room
                                }
                            }
                        }
                        next;
                    }
                }   
            }
            next;
        }
    }
    next;
}    
*/
    //CSGList* stuCourses = new_CSGList();
    SNAP* s;
    CSG* c;
    //CSG* t;
    CDH* x;
    CR* r;
    int nameIndex = hashName(n);
    int idIndex, courseIndex;
    int stuID;
    char* course;
    char* hour;
    char* day;
    char* room;
    
    /*
    //for each tuple s in SNAP { //match name to stuID
    while (list->snapBuckets[nameIndex] != NULL && s != NULL) {
        printf("made it past snap bucket\n");
        s = list->snapBuckets[nameIndex]->head;
        while (s != NULL) {
            printf("made it past s != null\n");
            //if (s.Name == n) {
            if (strcmp(s->Name, n) == 0) {
                //let stuID = s.studentID //get stuID
                stuID = s->studentID;
                idIndex = hashID(stuID);

                //for each tuple c in CSG { //match stuID to courses
                while (list->csgBuckets[idIndex] != NULL && c != NULL) {
                    printf("made it past csg bucket\n");
                    c = list->csgBuckets[idIndex]->head;
                    while (c != NULL) {
                        //if (c.studentID == stuID) {
                        if (c->studentID == stuID) {
                            //add matching courses to list of stuCourses
                            insert_CSGList(stuCourses, c->Course, stuID, c->Grade);
                        } else {
                            c = c->next;
                        }
                    }
                }
            }
        }
    }
    //for each tuple t in stuCourses {
    while (stuCourses != NULL && t != NULL) {
        printf("made it past stuCourses\n");
        t = stuCourses->head;
        //set hashCourse, go through cdh buckets
        courseIndex = hashCourse(t->Course);
        
        //for each tuple x in CDH { //match stuCourses to cdh
        while (list->cdhBuckets[courseIndex] != NULL && d != NULL && t != NULL) {
            printf("made it past cdh bucket\n");
            x = list->cdhBuckets[courseIndex]->head;
            while (d != NULL & t != NULL) {
                //if (x.course == stuCourses.course && x.hour == h && x.day == d) {
                if (strcmp(x->Course, t->Course) == 0 && strcmp(x->Hour, h) == 0 && strcmp(x->Day, d) == 0) {
                    //let course = d.course
                    course = x->Course;
                    hour = x->Hour;
                    day = x->Day;

                    //for each tuple r in CR { //match course to room
                    while (list->crBuckets[courseIndex] != NULL && r != NULL) {
                        printf("made it past cr bucket\n");
                        r = list->crBuckets[courseIndex]->head;
                        while (r != NULL) {
                            //if (r.course == course) {
                            if (strcmp(r->Course, course) == 0) {
                                //let room = r.room
                                room = r->Room;
                            }
                            r = r->next;
                        }
                    }
                }
                x = x->next;
            }
        }
    }
    */

    //for each tuple s in SNAP { //matching name to stuID
    while (list->snapBuckets[nameIndex] != NULL && s != NULL) {
        s = list->snapBuckets[nameIndex]->head;
        while (s != NULL) {
            //if (s.Name == n) {
            if (strcmp(s->Name, n) == 0) {
                //let stuID = s.studentID //get stuID
                stuID = s->studentID;
                idIndex = hashID(stuID);

                //for each tuple c in CSG { //matching stuID to course
                while (list->csgBuckets[idIndex] != NULL && c != NULL) {
                    c = list->csgBuckets[idIndex]->head;
                    while (c != NULL) {
                        //if (c.studentID == stuID) {
                        if (c->studentID == stuID) {
                            course = c->Course;
                            courseIndex = hashCourse(course);

                            //for each tuple d in CDH { //matching course to day, hour
                            while (list->cdhBuckets[courseIndex] != NULL && x != NULL) {
                                x = list->cdhBuckets[courseIndex]->head;
                                while (x != NULL) {
                                    //if (d.course == course){
                                    if (strcmp(x->Course, course) == 0) {
                                        //let hour = d.hour //get hour
                                        hour = x->Hour;
                                        //let day = d.day //get day
                                        day = x->Day;

                                        //for each tuple r in CR {
                                        while (list->crBuckets[courseIndex] != NULL && r != NULL) {
                                            r = list->crBuckets[courseIndex]->head;
                                            while (r != NULL) {
                                                //if (r.course == course) {
                                                if (strcmp(r->Course, course) == 0) {
                                                    //let room = r.room //get room
                                                    room = r->Room;
                                                }
                                                r = r->next;
                                            }
                                        }
                                        //x = x->next;
                                    }
                                    x = x->next;  
                                }
                            }
                            //c = c->next;
                        }
                        c = c->next;
                    }
                }
                //s = s->next;
            }
            s = s->next;
        }
    }

    //print -- [name] is in [course] in [room] at [hour] on [day]
    if (n != NULL && course != NULL && room != NULL && hour != NULL && day != NULL) { //input found
        printf("\nResults...\n%s is in %s in %s at %s on %s.\n\n", n, course, room, hour, day);
    } else {
        printf("\nSorry, student isn't enrolled in that class.\n\n");
    }
}

/*
testing on B.Biro... their info:
SNAP: 12345   B.Biro  2700 B-H Townline Rd    555-1212
CSG: CSC171  12345   A,     MATH150 12345   A,  DSCC201 12345   C
CDH: CSC171  T, R   1400                        DSCC201 M, W   900
CR:  CSC171  Hutchison Hall 141                 DSCC201 Bausch & Lomb 109
                            MATH150 Harkness 115

test: B.Biro 900 M
result: B.Biro is in DSCC201 in 90 at 1400 on R.
correct: B.Biro is in DSCC201 in Bausch & Lomb 109 at 900 on M.

B.BIRO TUPLE INFO --- hashID = 4; hashName = 4;
M.SMITH TUPLE INFO --- hashID = 5; hashName = 3;

DSCC201 hashCourse = 5;
CSC173 hashCourse = 1

M.Smith 98789 csc173 T,R 1400, Wegmans 1400

test: M.Smith 1400 T
result: M.Smith is in DSCC201 in � at 900 on W.
correct: M.Smith is in CSC173 in Wegmans 1400 at 1400 on T.

CSG-- hash ID
SNAP-- hash Name
rest -- hash Course
*/