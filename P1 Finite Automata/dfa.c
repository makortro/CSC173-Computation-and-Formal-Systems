/**
 * Project 1 - Automata
 * @file dfa.c
 * @author Adarsh Kumar, Jacob Banc, MaKayla Robinson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfa.h"

/**
 * @brief Allocate and return a new DFA containing the given number of states.
 * 
 * @param nstates - total num of states in DFA
 * @return DFA* 
 */
DFA* new_DFA(int nstates) {
    DFA* newDFA = (DFA*)malloc(sizeof(DFA));
    if(newDFA == NULL){
        return NULL;
    }
    
    newDFA->nStates = nstates;
    newDFA->states = (DFAState*)malloc(nstates*sizeof(DFAState));
    newDFA->currState = 0;
    
    //set all states to not-accepting and transitions as -1
    for (int i = 0; i < nstates; i++){
        newDFA->states[i].isAccepting = false;
        for (int j = 0; j < 128; j++){
            newDFA->states[i].transitions[j] = -1;
        }
    }
    
    return newDFA;
}

/**
 * @brief frees DFA and states from memory
 * 
 * @param dfa
 */
void DFA_free(DFA *dfa){
    free(dfa->states);
    free(dfa);
}

/**
 * @brief Free the given DFA.
 * 
 * @param dfa 
 * @return int 
 */
int DFA_get_size(DFA *dfa){
    return dfa->nStates;
}

/**
 * @brief Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 * 
 * @param dfa 
 * @param src - state
 * @param sym - char
 * @return int 
 */
int DFA_get_transition(DFA *dfa, int src, char sym){
    return dfa->states[src].transitions[(int)sym];
}

/**
 * @brief For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 * 
 * @param dfa 
 * @param src - beginning state
 * @param sym - char
 * @param dst - next state
 */
void DFA_set_transition(DFA *dfa, int src, char sym, int dst){
    dfa->states[src].transitions[(int)sym] = dst;
}

/**
 * @brief Set whether the given DFA's state is accepting or not.
 * 
 * @param dfa 
 * @param state 
 * @param value - T/F
 */
void DFA_set_accepting(DFA *dfa, int state, bool value){
    dfa->states[state].isAccepting = value;
}

/**
 * @brief Return true if the given DFA's state is an accepting state.
 * 
 * @param dfa 
 * @param state 
 * @return true 
 * @return false 
 */
bool DFA_get_accepting(DFA *dfa, int state){
    return dfa->states[state].isAccepting;
}

/**
 * @brief Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 * 
 * @param dfa 
 * @param input 
 * @return true 
 * @return false 
 */
bool DFA_run(DFA *dfa, char *input){
    for (int i = 0; i < strlen(input); i++) {
        int nextSt = dfa->states[dfa->currState].transitions[(int)input[i]];
        if (nextSt == -1) { 
            dfa->currState = 0;
            return false;
        } else {
            dfa->currState = nextSt;
        }
    }
    
    int finalState = dfa->currState;
    dfa->currState = 0;
    if (DFA_get_accepting(dfa, finalState)) {
        return true;
    } else {
        return false;
    }
}