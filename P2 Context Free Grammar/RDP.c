#include "Tree.h"
#include "RDP.h"

char *nextTerminal; //current position in input string

/**
 * checks if nextTerminal is a digit (0-9)
 * @return 0 for false; 1 for true
 */
bool isDigit() {
    switch (*nextTerminal) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
    }
    return false;
}

/**
 * checks if nextTerminal is 'e' for epsilon
 * @return 0 for false; 1 for true
 */
bool isEpsilon() {
    if (*nextTerminal == 'e') {
        return true;
    } else {
        return false;
    }
}

/**
 * checks if nextTerminal is a non-digit terminal symbol
 * @return 0 for false; 1 for true
 */
bool isOperator() {
    switch (*nextTerminal) {
        case ',':
        case '{':
        case '}':
        case '(':
        case ')':
        case 'U':
        case '^':
            return true;
    }
    return false;
}

/**
 * checks if nextTerminal is a terminal symbol in grammar
 * @return 0 for false; 1 for true
 */
bool isTerminalSymbol() {
    switch (*nextTerminal) {
        case 'e':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ',':
        case '{':
        case '}':
        case '(':
        case ')':
        case 'U':
        case '^':
            return true;
    }
    return false;
}

/**
 * A = ATOMIC
 * <A> -> ( <E> ) | <S>
 */
TREE A() {

    TREE e; //rule 1: (<E>)
    TREE s; //rule 2: <S>

    if (*nextTerminal == '{') { //follow prod 2; send to S()
        s = S();
        if (s != FAILED) {
            return makeNode1('E', s);
        } else { return FAILED; }
    } else if (*nextTerminal == '(') { //follow prod 1; advance NT, send to E()
        nextTerminal++;
        e = E();
        if (e != FAILED) {
            if (nextTerminal == ')') {
                nextTerminal++;
                return makeNode3('A', makeNode0('('), e, makeNode0(')'));
            } else { return FAILED; }
        } else { return FAILED; }
    } else { return FAILED; } //doesn't match production
}

/**
 * E = EXPRESSION
 * <E> -> <A> <E_TAIL>
 */
TREE E() {

    TREE a; //rule 1: <A>
    TREE et; //rule 2: <E_TAIL>

    if (*nextTerminal == 'U' || *nextTerminal == '^' || *nextTerminal == 'e') { //follow prod 2; send to E_TAIL()
        et = E_Tail();
        if (et != FAILED) {
            nextTerminal++;
            return makeNode1('E', et);
        } else { return FAILED; }
    } else if (*nextTerminal == '(' || *nextTerminal == "{") { //follow prod 1; send to A()
        a = A();
        if (a != FAILED) {
            nextTerminal++;
            return makeNode1('E', a);
        } else { return FAILED; }
    } else { return FAILED; }
}

/**
 * <E_TAIL> -> U <E> | ^ <E> | e
 */
TREE E_Tail() {

    TREE u; //rule 1: U <E>
    TREE c; //rule 2: ^ <E>

    if (*nextTerminal == 'e') { //follow prod 3, return epsilon leaf
        nextTerminal++;
        return makeNode1('ET', makeNode0('e'));
    } else if (*nextTerminal == '^') { //follow prod 2; send to E()
        nextTerminal++;
        c = E();
        if (c != FAILED) {
            return makeNode2('ET', makeNode0('^'), c);
        } else { return FAILED; }
    } else if (*nextTerminal == 'U') { //follow prod 1; send to E()
        nextTerminal++;
        u = E();
        if (u != FAILED) {
            return makeNode2('ET', makeNode0('U'), u);
        } else { return FAILED; }
    } else {return FAILED; }
}

/**
 * S = SET
 * <S> -> { <S_TAIL>
 */
TREE S() {

    TREE st; //rule 1: { <S_TAIL>

    if (*nextTerminal == '{') { //follow only prod
        nextTerminal++;
        st = S_Tail();
        if (st != FAILED) {
            return makeNode2('S', makeNode0('{'), st);
        } else { return FAILED; }
    } else { return FAILED; }
}

/**
 * <S_TAIL> -> } | <Ls> }
 */
TREE S_Tail() {

    TREE ls; //rule 2: <Ls> }

    if (*nextTerminal == '}') { //follow prod 1; return empty set node
        nextTerminal++;
        return makeNode2('ST', makeNode0('e'), makeNode0('}'));
    } else if (isDigit() != 0) { //follow prod 2; number found, send to Ls()
        ls = Ls();
        if (ls != FAILED && *nextTerminal == '}') {
            nextTerminal++;
            return makeNode2('ST', ls, makeNode0('}'));
        } else { return FAILED; }
    } else { return FAILED; }
}

/**
 * Ls = ELEMENTS
 * <Ls> -> <L> <L_TAIL>
 */
TREE Ls() {

    TREE l; //rule 1: <L>
    TREE lt; //rule 2: <L_TAIL>

    if (*nextTerminal == ',') { //follow prod 2; comma found (multiple elements detected), send to L_TAIL()
        nextTerminal++;
        lt = L_Tail();
        if (lt != FAILED) {
            nextTerminal++;
            return makeNode2('Ls', makeNode0(','), lt);
        } else { return FAILED; }
    } else if (isDigit() != 0) { //follow prod 1; number found, sent to L()
        l = L();
        if (l != FAILED) {
            nextTerminal++;
            return makeNode1('Ls', l);
        } else { return FAILED; }
    } else { return FAILED; }
}

/**
 * L = ELEMENT
 * <L> -> <N>
 */
TREE L() {

    TREE n; //rule 1: <N>

    if (isDigit() != 0) { //follow only prod
        n = N();
        if (n != FAILED) {
            nextTerminal++;
            return makeNode1('L', n);
        } else { return FAILED; }
    } else { return FAILED; }
}

/**
 * <L_TAIL> -> , <Ls> | e
 */
TREE L_Tail() {

    TREE ls; //rule 1: , <Ls>

    if (*nextTerminal == ',') { //follow prod 1; multiple elements, send to Ls()
        ls = Ls();
        if (ls != FAILED) {
            nextTerminal++;
            return makeNode1('LT', ls);
        } else { return FAILED; }
    } else if (*nextTerminal == 'e') { //follow prod 2; return epsilon node
        nextTerminal++;
        return makeNode1('LT', makeNode0('e'));
    } else { return FAILED; }
}

/**
 * N = NUMBER
 * <N> -> <D> <N_TAIL>
 */
TREE N() {

    TREE d; //rule 1: <D>
    TREE nt; //rule 2: <N_TAIL>

    if (isDigit() != 0) { //follow prod 1; send to D()
        d = D();
        if (d != FAILED) { //follow prod 2; send to N_TAIL() to check for additional numbers
            nextTerminal++;
            nt = N_Tail();
            if (nt != FAILED) {
                return makeNode2('N', d, nt);
            } else { return FAILED; }
        } else { return FAILED; }
    } else { return FAILED; }
}

/**
 * <N_TAIL> -> <N> | e
 */
TREE N_Tail() {

    TREE n; //rule 1: <N>

    if (*nextTerminal == 'e') { //follow prod 2; return empty node
        return makeNode1('NT', makeNode0('e'));
    } else if (isDigit() != 0) { //follow prod 1, send to N()
        n = N();
        if (n != FAILED) {
            nextTerminal++;
            return makeNode1('NT', n);
        } else { return FAILED; }
    } else { return FAILED; }
}

/**
 * D = DIGIT
 * <D> -> 0 | ... | 9
 */
TREE D() {
    return makeNode1('<D>', makeNode0(*nextTerminal));
}