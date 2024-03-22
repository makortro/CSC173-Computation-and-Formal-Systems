/**
 * @file main.c
 * @author MaKayla Robinson - mrobin45
 */
#include "Database.h"
#include "CSG.h"
#include "CDH.h"
#include "CP.h"
#include "CR.h"
#include "SNAP.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_CHAR 20

void freeDB(Database db);

//fills database
Database fillDB(Database db);
Database part1(Database db);
void part2A(Database db);
void part2B(Database db);
void part3();

int main(int argc, const char * argv[]) {
    Database db = new_Database(5);
    fillDB(db);
    part1(db);
    Database db2 = new_Database(5);
    fillDB(db2);
    part2A(db2);
    part2B(db2);
}

Database fillDB(Database db) {
    printf("\nHere is the database...\n");
    /*
    Course StudentId Grade
    1 CSC171 12345 A
    2 CSC171 67890 B
    3 MATH150 12345 A
    4 DSCC201 12345 C
    5 DSCC201 11111 B+
    6 CSC172 98789 A
    7 MATH150 67890 C+
    8 CSC173 12321 B+
    9 CSC173 98789 A
    */
    insert_CSGDatabase("CSC171", 12345, "A", db);
    insert_CSGDatabase("CSC171", 67890, "B", db);
    insert_CSGDatabase("MATH150", 12345, "A", db);
    insert_CSGDatabase("DSCC201", 12345, "C", db);
    insert_CSGDatabase("DSCC201", 11111, "B+", db);
    insert_CSGDatabase("CSC172", 98789, "A", db);
    insert_CSGDatabase("MATH150", 67890, "C+", db);
    insert_CSGDatabase("CSC173", 12321, "B+", db);
    insert_CSGDatabase("CSC173", 98789, "A", db);

    /*
    StudentId Name Address Phone
    1 11111 M. Smith 1 Exchange Blvd 555-1212
    2 12345 B. Biro 2700 B-H Townline Rd 555-1111
    3 67890 L. Rousek 1 Exchange Blvd 555-1234
    4 12321 M. Pekar 80 Lyndon Rd 555-2222
    5 98789 M. Smith 123 Ling Rd 555-3333
    */
    insert_SNAPDatabase(11111, "M.Smith", "1 Exchange Blvd", "555-1212", db);
    insert_SNAPDatabase(12345, "B.Biro", "2700 B-H Townline Rd", "555-1212", db);
    insert_SNAPDatabase(67890, "L.Rousek", "1 Exchange Blvd", "555-1212", db);
    insert_SNAPDatabase(12321, "M.Pekar", "80 Lyndon Rd", "555-1212", db);
    insert_SNAPDatabase(98789, "M.Smith", "123 Ling Rd", "555-1212", db);

    /*
    Course Prerequisite
    1 CSC172 CSC171
    2 CSC172 MATH150
    3 CSC173 CSC172
    4 CSC252 CSC172
    5 CSC254 CSC252
    6 DSCC201 CSC171
    7 DSCC202 DSCC201
    8 DSCC265 CSC262
    9 DSCC265 CSC171
    */
    insert_CPDatabase("CSC172", "CSC171", db);
    insert_CPDatabase("CSC172", "MATH150", db);
    insert_CPDatabase("CSC173", "CSC172", db);
    insert_CPDatabase("CSC252", "CSC172", db);
    insert_CPDatabase("CSC254", "CSC252", db);
    insert_CPDatabase("DSCC201", "CSC171", db);
    insert_CPDatabase("DSCC202", "DSCC201", db);
    insert_CPDatabase("DSCC265", "CSC262", db);
    insert_CPDatabase("DSCC265", "CSC171", db);

    /*
    Course Day Hour
    1 CSC171 T 1400
    2 CSC171 R 1400
    3 CSC172 T 1525
    4 CSC172 R 1640
    5 CSC173 T 1400
    6 CSC173 R 1400
    7 CSC252 T 1230
    8 CSC252 R 1230
    9 DSCC201 M 900
    10 DSCC201 W 900
    11 DSCC202 M 1650
    12 DSCC202 W 1650
    13 DSCC265 M 1400
    14 DSCC265 W 1400
    */
    insert_CDHDatabase("CSC171", "T", "1400", db);
    insert_CDHDatabase("CSC171", "R", "1400", db);
    insert_CDHDatabase("CSC172", "T", "1525", db);
    insert_CDHDatabase("CSC172", "R", "1640", db);
    insert_CDHDatabase("CSC173", "T", "1400", db);
    insert_CDHDatabase("CSC173", "R", "1400", db);
    insert_CDHDatabase("CSC252", "T", "1230", db);
    insert_CDHDatabase("CSC252", "R", "1230", db);
    insert_CDHDatabase("DSCC201", "M", "900", db);
    insert_CDHDatabase("DSCC201", "W", "900", db);
    insert_CDHDatabase("DSCC202", "M", "1650", db);
    insert_CDHDatabase("DSCC202", "W", "1650", db);
    insert_CDHDatabase("DSCC265", "M", "1400", db);
    insert_CDHDatabase("DSCC265", "W", "1400", db);

    /*
    Course Room
    1 CSC171 Hutchison Hall 141
    2 CSC172 Hutchison Hall 141
    3 CSC173 Wegmans 1400
    4 CSC252 Wegmans 1400
    5 CSC254 Wegmans 1400
    6 DSCC201 Bausch & Lomb 109
    7 DSCC202 Dewey 2162
    8 DSCC265 Wegmans 1400
    9 MATH150 Harkness 115
    */
    insert_CRDatabase("CSC171", "Hutchison Hall 141", db);
    insert_CRDatabase("CSC172", "Hutchison Hall 141", db);
    insert_CRDatabase("CSC173", "Wegmans 1400", db);
    insert_CRDatabase("CSC252", "Wegmans 1400", db);
    insert_CRDatabase("CSC254", "Wegmans 1400", db);
    insert_CRDatabase("DSCC201", "Bausch & Lomb 109", db);
    insert_CRDatabase("DSCC202", "Dewey 2162", db);
    insert_CRDatabase("DSCC265", "Wegmans 1400", db);
    insert_CRDatabase("MATH150", "Harkness 115", db);

    print_Database(db);

    return db;
}

Database part1(Database db) {
    printf("\n\n*** PART 1 START ***\n\n");

    //(a) lookup(⟨“CSC172”, 98789, ∗⟩, Course-StudentId-Grade)
    printf("(a) lookup(⟨“CSC172”, 98789, ∗⟩, Course-StudentId-Grade):\n");
    lookup_CSGDatabase("CSC172", 98789, "*", db);
    printf("(aa) lookup(⟨*, 98789, ∗⟩, Course-StudentId-Grade):\n");
    lookup_CSGDatabase("*", 98789, "*", db);

    //(b) lookup(⟨“CSC173”, “CSC172”⟩, Course-Prerequisite)
    printf("\n\n(b) lookup(⟨“CSC173”, *, Course-Prerequisite):\n");
    lookup_CPDatabase("CSC173", "*", db);

    //(c) delete(⟨“DSCC201”, ∗, ∗⟩, Course-Day-Hour)
    printf("\n\n(c) delete(⟨“DSCC201”, *, *⟩, Course-Day-Hour):\n");
    printf("\n~ before delete ~ ");
    print_CDHHeader();
    for(int i = 0; i < TABLE_SIZE; i++){
        print_CDHList(db->cdhBuckets[i]);
    }
    print_CDHFooter();
    delete_CDHDatabase("DSCC201", "*", "*", db);
    printf("~ after delete ~ ");
    print_CDHHeader();
    for(int i = 0; i < TABLE_SIZE; i++){
        print_CDHList(db->cdhBuckets[i]);
    }
    print_CDHFooter();
    // TODO --- only deleting 1 thing

    //(d) insert(⟨“CSC280”, “CSC173”⟩, Course-Prerequisite)
    printf("\n\n(d) insert(⟨“CSC280”, “CSC173”⟩, Course-Prerequisite):\n");
    printf("\n~ before insert ~ ");
    print_CPHeader();
        for(int i = 0; i < TABLE_SIZE; i++){
            print_CPList(db->cpBuckets[i]);
        }
    print_CPFooter();
    printf("~ after insert ~ ");
    print_CPHeader();
    insert_CPDatabase("CSC280", "CSC173", db);
    for(int i = 0; i < TABLE_SIZE; i++){
        print_CPList(db->cpBuckets[i]);
    }
    print_CPFooter();

    //(e) insert(⟨“DSCC202”, “DSCC201”⟩, Course-Prerequisite)
    printf("\n\n(e) insert(⟨“DSCC202”, “DSCC201”⟩, Course-Prerequisite):\n");
    printf("\n~ before insert ~ ");
    print_CPHeader();
        for(int i = 0; i < TABLE_SIZE; i++){
            print_CPList(db->cpBuckets[i]);
        }
    print_CPFooter();
    insert_CPDatabase("DSCC202", "DSCC201", db);
    printf("~ after insert ~ ");
    print_CPHeader();
    for(int i = 0; i < TABLE_SIZE; i++){
        print_CPList(db->cpBuckets[i]);
    }
    print_CPFooter();

    printf("\n*** PART 1 END ***\n\n");
    freeDB(db);

    return db;
}

    /*
    Name
    1 M. Smith
    2 B. Biro
    3 L. Rousek
    4 M. Pekar
    5 M. Smith
    
    Course
    1 CSC171
    2 CSC172
    3 CSC173
    4 CSC252
    5 CSC254
    6 DSCC201
    7 DSCC202
    8 DSCC265
    9 MATH150
    */
void part2A(Database db) {
    printf("\n\n*** PART 2 START ***\n\n");
    
    CSGList* result = new_CSGList();
    bool running1 = true;

    //“What grade did Name get in Course?”
    while(running1) {
        printf("\n(2a) What grade did [name] get in [course]?");
        printf("\n\nChoose a student from the following list...");
        print_SNHeader();
        for(int i = 0; i < TABLE_SIZE; i++){
            print_SNList(db->snapBuckets[i]);
        }
        print_SNFooter();

        char* inputName = malloc(sizeof(char));
        printf("\nEnter student's name (NO SPACE after period; e.g. M.Smith): ");
        scanf("%s", inputName);

        printf("\nChoose which course...");
        print_CHeader();
        for(int i = 0; i< TABLE_SIZE; i++){
            print_CList(db->crBuckets[i]);
        }
        print_CFooter();

        char* inputCourse = malloc(sizeof(char));
        printf("\nEnter the course (CSC171): ");
        scanf("%s", inputCourse);
        //fgets(inputCourse, MAX_CHAR, stdin);

        printf("\nSending to database to get results...\n");

        result = checkStudentGrade(db, inputName, inputCourse);
        if (result != NULL) {
            printf("\nResults...");
            //[name] got a [grade] in [course]
            print_CSGHeader();
            print_CSGList(result);
            print_CSGFooter();
        } else {
            printf("Sorry, student isn't enrolled in that class.");
            continue;
        }

        printf("Would you like to check another student?\n");
        printf("Enter Y or N: ");
        char* inputContinue = malloc(sizeof(char));
        scanf("%s", inputContinue);
        if (strcmp(inputContinue, "N") == 0 || strcmp(inputContinue, "n") == 0) {
            printf("\n\n~~~~~~~~~~ Moving on to part 2b... ~~~~~~~~~~\n");
            running1 = false;
        }
    }
}

void part2B(Database db) {
//“Where is Name at Hour on Day?”
    bool running2 = true;

    while (running2) {
        printf("\n\n(2b) Where is [name] at [hour] on [day]?");
        printf("\n\nChoose a student from the following list...");
        print_SNHeader();
        for(int i = 0; i < TABLE_SIZE; i++){
            print_SNList(db->snapBuckets[i]);
        }
        print_SNFooter();

        char* inputN = malloc(sizeof(char));
        printf("\nEnter student's name (NO SPACE after period; e.g. M.Smith): ");
        scanf("%s", inputN);

        /*
         Course Day Hour
        1 CSC171 T 1400
        2 CSC171 R 1400
        3 CSC172 T 1525
        4 CSC172 R 1640
        5 CSC173 T 1400
        6 CSC173 R 1400
        7 CSC252 T 1230
        8 CSC252 R 1230
        9 DSCC201 M 900
        10 DSCC201 W 900
        11 DSCC202 M 1650
        12 DSCC202 W 1650
        13 DSCC265 M 1400
        14 DSCC265 W 1400
        */
        
        char* inputH = malloc(sizeof(char));
        printf("\nChoose which hour from the following options...\n");
        printf("---------------------------------\n");
        printf("900, 1230, 1400, 1525, 1640, 1650\n");
        printf("---------------------------------\n");
        printf("\nEnter the time (900): ");
        scanf("%s", inputH);

        char* inputD = malloc(sizeof(char));
        printf("\nChoose what day from the following options...\n");
        printf("-------------\n");
        printf("M - Monday\nT - Tuesday\nW - Wednesday\nR - Thursday\n");
        printf("-------------\n");
        printf("\nEnter the day (M): ");
        scanf("%s", inputD);

        printf("\nSending to database to get results...\n");
        
        whereIsStudent(inputN, inputH, inputD, db);

        char* inputCont = malloc(sizeof(char));
        printf("Would you like to check another student?\n");
        printf("Enter Y or N: ");
        scanf("%s", inputCont);
        if (strcmp(inputCont, "N") == 0 || strcmp(inputCont, "n") == 0) {
            printf("\nQuitting... goodbye!");
            running2 = false;
        }
    }

    printf("\n\n*** PART 2 END ***\n\n");
}