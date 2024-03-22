/**
 * Project 1 - Automata
 * @file main.c
 * @author Adarsh Kumar, Jacob Banc, MaKayla Robinson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nfa.h"
#include "LinkedList.h"

/**
 * @brief Allocate and return a new NFA containing the given number of states.
 * 
 * @param nstates - total num of states in NFA
 * @return NFA* 
 */
NFA* new_NFA(int nstates){
    NFA* newNFA = (NFA*)malloc(sizeof(NFA));
    if(newNFA == NULL){
        return NULL;
    }
    
    newNFA->nStates = nstates;
    newNFA->states = (NFAState*)malloc(nstates*sizeof(NFAState));
    IntHashSet* initialstate = new_IntHashSet(3);
    Set_insert(initialstate, 0);
    newNFA->currStates = initialstate;
    
    //set all states to not-accepting and create empty sets, which means no transition
    for (int i = 0; i < nstates; i++){
        newNFA->states[i].isAccepting = false;
        for (int j = 0; j < 128; j++){
            newNFA->states[i].transitions[j] = new_Set(50);
        }
    }
    
    return newNFA;
}

/**
 * @brief Free the given NFA.
 * 
 * @param nfa 
 */
void NFA_free(NFA *nfa){
    for (int i = 0; i < nfa->nStates; i++){
        NFAState *curr_state = &nfa->states[i];
        for (int j = 0; j < 128; j++){
            Set_free(curr_state->transitions[j]);
        }
    }
    if (!Set_isEmpty(nfa->currStates)){
        Set_free(nfa->currStates);
    }
    free(nfa->states);
    free(nfa);
}

/**
 * @brief Return the number of states in the given NFA.
 * 
 * @param nfa 
 * @return int 
 */
int NFA_get_size(NFA *nfa){
    return nfa->nStates;
}

/**
 * @brief retreives char transition at specific state
 * 
 * @param nfa 
 * @param state 
 * @param sym 
 * @return Set* 
 */
Set* NFA_get_transitions(NFA *nfa, int state, char sym){
    return nfa->states[state].transitions[(int)sym];
}

/**
 * @brief Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 * 
 * @param nfa 
 * @param src - beginning state
 * @param sym - char
 * @param dst - next state
 */
void NFA_add_transition(NFA *nfa, int src, char sym, int dst){
    Set_insert(nfa->states[src].transitions[(int)sym], dst);
}

/**
 * @brief For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 * 
 * @param nfa 
 * @param src 
 * @param dst 
 */
void NFA_add_transition_all(NFA *nfa, int src, int dst){
    for (int i = 0; i < 128; i++) {
        Set_insert(nfa->states[src].transitions[i], dst);
    }
}

/**
 * @brief Set whether the given NFA's state is accepting or not.
 * 
 * @param nfa 
 * @param state 
 * @param value 
 */
void NFA_set_accepting(NFA *nfa, int state, bool value){
    nfa->states[state].isAccepting = value;
}

/**
 * @brief Return true if the given NFA's state is an accepting state.
 * 
 * @param nfa 
 * @param state 
 * @return true 
 * @return false 
 */
bool NFA_get_accepting(NFA *nfa, int state){
    return nfa->states[state].isAccepting;
}

/**
 * @brief Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 * 
 * @param nfa 
 * @param input 
 * @return true 
 * @return false 
 */
bool NFA_run(NFA *nfa, char *input){
    //update set of states for each input char
    int i = 0; //input string iterator
    int state; //iterator for currStates
    
    LinkedList* tempSt = new_LinkedList(); //list of states to compare
    LinkedList_add_at_front(tempSt, nfa->currStates);
    
    while (input[i] != '\0') {
        Set* currStatesUpdate = new_Set(30);
        SetIterator* poss_states_it = Set_iterator(LinkedList_elementAt(tempSt, 0));
        while (SetIterator_hasNext(poss_states_it)){
            state = SetIterator_next(poss_states_it);
            Set_union(currStatesUpdate, nfa->states[state].transitions[(int)input[i]]);
        }
        Set* temp = new_Set(30);
        IntHashSet_union(temp, currStatesUpdate);
        LinkedList_add_at_front(tempSt, temp);
        IntHashSet_free(currStatesUpdate);
        i++;
        free(poss_states_it);
    }

    nfa->currStates = LinkedList_pop(tempSt);
    LinkedList_free(tempSt, true);
    
    
    //check final set of states for any accepting states
    int finalState;
    SetIterator *checkAccepting = Set_iterator(nfa->currStates);
    while (SetIterator_hasNext(checkAccepting)){
        finalState = SetIterator_next(checkAccepting);
        if (nfa->states[finalState].isAccepting){
            free(checkAccepting);
            return true;
        }
    }
    //not accepting
    free(checkAccepting);
    return false;
}
