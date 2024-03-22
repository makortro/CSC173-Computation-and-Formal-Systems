/**
 * Project 1 - Automata
 * @file main.c
 * @author Adarsh Kumar, Jacob Banc, MaKayla Robinson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"
#include "LinkedList.h"

/*** PART 1: DFA ***/
// (a) Exactly the string "automaton"
DFA* automaton() {
    DFA* automaton_DFA = new_DFA(10);
    DFA_set_transition(automaton_DFA, 0, 'a', 1);
    DFA_set_transition(automaton_DFA, 1, 'u', 2);
    DFA_set_transition(automaton_DFA, 2, 't', 3);
    DFA_set_transition(automaton_DFA, 3, 'o', 4);
    DFA_set_transition(automaton_DFA, 4, 'm', 5);
    DFA_set_transition(automaton_DFA, 5, 'a', 6);
    DFA_set_transition(automaton_DFA, 6, 't', 7);
    DFA_set_transition(automaton_DFA, 7, 'o', 8);
    DFA_set_transition(automaton_DFA, 8, 'n', 9);
    DFA_set_accepting(automaton_DFA, 9, true);
    return automaton_DFA;
}

// (b) Strings ending with 'ed', such as “Fred”
DFA* endingED() {
    DFA* ed_DFA = new_DFA(3);
    DFA_set_transition(ed_DFA, 0, 'e', 1);
    DFA_set_transition(ed_DFA, 1, 'd', 2);
    DFA_set_accepting(ed_DFA, 2, true);
    return ed_DFA;
}

// (c) Strings containing exactly two 2’s, such as “21a72”
DFA* containsTwo2s() {
    DFA* two2s_DFA = new_DFA(3);
    DFA_set_transition(two2s_DFA, 0, '2', 1);
    DFA_set_transition(two2s_DFA, 1, '2', 2);
    DFA_set_accepting(two2s_DFA, 2, true);
    return two2s_DFA;
}

// (d) Binary input with an odd number of both 0’s and 1’s
DFA* oddZerosAndOnes() {
    DFA* oddBin_DFA = new_DFA(4);
    DFA_set_transition(oddBin_DFA, 0, '0', 1);
    DFA_set_transition(oddBin_DFA, 0, '1', 2);
    DFA_set_transition(oddBin_DFA, 1, '0', 0);
    DFA_set_transition(oddBin_DFA, 1, '1', 3);
    DFA_set_transition(oddBin_DFA, 2, '0', 3);
    DFA_set_transition(oddBin_DFA, 2, '1', 0);
    DFA_set_transition(oddBin_DFA, 3, '0', 2);
    DFA_set_transition(oddBin_DFA, 3, '1', 1);
    DFA_set_accepting(oddBin_DFA, 3, true);
    return oddBin_DFA;
}

// (e) At least one other interesting pattern: exactly the string "csc173""
DFA* csc173() {
    DFA* csc173_DFA = new_DFA(7);
    DFA_set_transition(csc173_DFA, 0, 'c', 1);
    DFA_set_transition(csc173_DFA, 1, 's', 2);
    DFA_set_transition(csc173_DFA, 2, 'c', 3);
    DFA_set_transition(csc173_DFA, 3, '1', 4);
    DFA_set_transition(csc173_DFA, 4, '7', 5);
    DFA_set_transition(csc173_DFA, 5, '3', 6);
    DFA_set_accepting(csc173_DFA, 6, true);
    return csc173_DFA;
}



/*** PART 2: NFA ***/
// (a) Strings ending in 'head', such as “ahead”
NFA* endingHEAD() {
    NFA* head_NFA = new_NFA(5);
    NFA_add_transition_all(head_NFA, 0, 0);
    NFA_add_transition(head_NFA, 0, 'h', 1);
    NFA_add_transition(head_NFA, 1, 'a', 2);
    NFA_add_transition(head_NFA, 2, 'e', 3);
    NFA_add_transition(head_NFA, 3, 'd', 4);
    NFA_set_accepting(head_NFA, 4, true);
    return head_NFA;
}

// (b) Strings containing zz, such as “jazzy” and “zzz”
NFA* containsZZ() {
    NFA* zz_NFA = new_NFA(3);
    NFA_add_transition_all(zz_NFA, 0, 0);
    NFA_add_transition(zz_NFA, 0, 'z', 1);
    NFA_add_transition(zz_NFA, 1, 'z', 2);
    NFA_set_accepting(zz_NFA, 2, true);
    return zz_NFA;
}

// (d) At least one other interesting pattern: string "exactly"
NFA* exactly() {
    NFA* exactly_NFA = new_NFA(8);
    NFA_add_transition_all(exactly_NFA, 0, 0);
    NFA_add_transition(exactly_NFA, 0, 'e', 1);
    NFA_add_transition(exactly_NFA, 1, 'x', 2);
    NFA_add_transition(exactly_NFA, 2, 'a', 3);
    NFA_add_transition(exactly_NFA, 3, 'c', 4);
    NFA_add_transition(exactly_NFA, 4, 't', 5);
    NFA_add_transition(exactly_NFA, 5, 'l', 6);
    NFA_add_transition(exactly_NFA, 6, 'y', 7);
    NFA_set_accepting(exactly_NFA, 7, true);
    return exactly_NFA;
}

//REPL: DFA
void DFA_repl(char* function, DFA* dfa, char* c, char* exit, char* userInput) {
    bool test;
    printf("\nTesting DFA: %s\n", function);
    DFA* this_DFA = dfa;
    do {
        printf("%s", userInput);
        scanf("%255s", c);
        if (strcmp(c, exit) == 0){
            DFA_free(this_DFA);
            break;
        }
        test = DFA_run(this_DFA, c);
        if (test) {
            printf("        RESULTS: \"%s\" is TRUE\n", c);
        } else {
            printf("        RESULTS: \"%s\" is FALSE\n", c);
        }   
    } while (strcmp(c, exit) != 0);
}

//REPL: NFA
void NFA_repl(char* function, NFA *nfa, char* c, char* exit, char* userInput) {
    bool test;
    printf("\nTesting NFA: %s\n", function);
    NFA* this_NFA = nfa;
    do {
        printf("%s", userInput);
        scanf("%255s", c);
        if (strcmp(c, exit) == 0){
            NFA_free(this_NFA);
            break;
        }
        test = NFA_run(this_NFA, c);
        if (test) {
            printf("        RESULTS: \"%s\" is TRUE\n", c);
        } else {
            printf("        RESULTS: \"%s\" is FALSE\n", c);
        }
    } while (strcmp(c, exit) != 0);
}

int main(int argc, char **argv) {
    char input[255];
    char userInput[50];
    char exit[8];
    
    strcpy(exit, "exit");
    strcpy(userInput, "    Please enter a string (type \'exit\' to exit): ");
    
    printf("\n\n*** CSC173 Project 1 - Finite Automata ***\n");
    printf("Adarsh Kumar, Jacob Banc, MaKayla Robinson\n");
    
    //Question 1: DFA
    printf("\n- - Part 1: DFA - -\n");
    DFA_repl("(a) Exactly the string \"automaton\"", automaton(), input, exit, userInput);
    DFA_repl("(b) Strings ending with \'ed\', such as \"Fred\"", endingED(), input, exit, userInput);
    DFA_repl("(c) Strings containing exactly two 2\'s, such as \"21a72\"", containsTwo2s(), input, exit, userInput);
    DFA_repl("(d) Binary input with an odd number of both 0\'s and 1\'s", oddZerosAndOnes(), input, exit, userInput);
    DFA_repl("(e) At least one other interesting pattern: exactly the string \"csc173\"", csc173(), input, exit, userInput);

    //Question 2: NFA
    printf("\n- - Part 2: NFA - -\n");
    NFA_repl("(a) Strings ending in \'head\', such as \"ahead\"", endingHEAD(), input, exit, userInput);
    NFA_repl("(b) Strings containing \'zz\', such as \"jazzy\" and \"zzz\"", containsZZ(), input, exit, userInput);
    NFA_repl("(d) At least one other interesting pattern: string \"exactly\"", exactly(), input, exit, userInput);
}