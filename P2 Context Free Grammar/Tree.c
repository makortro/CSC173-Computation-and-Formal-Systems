#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

#define FAILED NULL

typedef struct NODE *TREE;

struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

char *nextTerminal; //current position in input string

/**
 *  makeNode0(x) creates a node with zero children, that is, a leaf,
 *  and labels that leaf with the symbol x. The tree consisting of this one
 *  node is returned.
 */
TREE makeNode0(char x) {
    TREE root;
    root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

/**
 *  makeNode1(x, t) creates a node with one child. The label of the
 *  new node is x, and the child is the root of the tree t. The tree whose root
 *  is the created node is returned. Note that makeNode1 uses makeNode0 to
 *  create the root node and then makes the root of tree t be the leftmost child
 *  of the root. We assume that all leftmost-child and right-sibling pointers are
 *  NULL initially, as they will be because they are all created by makeNode0,
 *  which explicitly NULL’s them. Thus, it is not mandatory that makeNode1
 *  to store NULL in the rightSibling field of the root of t, but it would be a
 *  wise safety measure to do so.
 */
TREE makeNode1(char* x, TREE t) {
    TREE root;
    root = makeNode0(x);
    root->leftmostChild = t;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode2(char* x, TREE t1, TREE t2) {
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = NULL;
    return root;
}

TREE makeNode3(char* x, TREE t1, TREE t2, TREE t3) {
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = NULL;
    return root;
}

/**
 *  makeNode4(x, t1, t2, t3, t4) creates a node with four children. The
 *  label of the node is x, and the children are the roots of the trees t1, t2, t3,
 *  and t4, from the left. The tree whose root is the created node is returned.
 *  Note that makeNode4 uses makeNode1 to create a new root and attach t1
 *  to it, then strings the remaining trees together with right-sibling pointers.
 */
TREE makeNode4(char* x, TREE t1, TREE t2, TREE t3, TREE t4) {
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    t4->rightSibling = NULL;
    return root;
}

/**
 * GRAMMAR:
 *
 * E = EXPRESSION
 * A = ATOMIC
 * E_TAIL = EXPRESSION TAIL
 * S = SET
 * S_TAIL = SET TAIL
 * Ls = ELEMENTS (plural)
 * L = ELEMENT (singular)
 * L_TAIL = ELEMENT TAIL
 * N = NUMBER
 * N_TAIL = NUMBER TAIL
 * D - DIGIT
 *
 * <E> -> <A> <E_TAIL>
 * <E_TAIL> -> U <E> | ^ <E> | e
 * <A> -> ( <E> ) | <S>
 * <S> -> { <S_TAIL>
 * <S_TAIL> -> } | <Ls> }
 * <Ls> -> <L> <L_TAIL>
 * <L_TAIL> -> , <Ls> | e
 * <L> -> <N>
 * <N> -> <D> <N_TAIL>
 * <N_TAIL> -> <N> | e
 * <D> -> 0 | ... | 9
 */



/**
 * prod 1: <B> -> e
 *      B
 *      |
 *      e
 * prod 2: <B> -> (<B>)<B>
 * rule = first b, second b
 *      B
 *   /  |  \   \
 *  (   B   )  B
 *      |      |
 *      e      e
 */
/*TREE B() {
    TREE firstB, secondB;
    if(*nextTerminal == '(') { // follow production 2
        nextTerminal++;
        firstB = B();
        if(firstB != FAILED && *nextTerminal == ')') {
            nextTerminal++;
            secondB = B();
            if(secondB == FAILED) {
                return FAILED;
            } else{
                return makeNode4('B', makeNode0('('), firstB, makeNode0(')'), secondB));
            }
        } else {//first call to B failed
            return FAILED;
        }
    } else {//follow production 1
        return makeNode1('B', makeNode0('e'));
    }
}*/

/**
 * <E> -> <A> <E_TAIL>
 * <E_TAIL> -> U <E> | ^ <E> | e
 * <A> -> ( <E> ) | <S>
 * <S> -> { <S_TAIL>
 * <S_TAIL> -> } | <Ls> }
 * <Ls> -> <L> <L_TAIL>
 * <L_TAIL> -> , <Ls> | e
 * <L> -> <N>
 * <N> -> <D> <N_TAIL>
 * <N_TAIL> -> <N> | e
 * <D> -> 0 | ... | 9
 *
 * start in E()
 *      check for atomic -- that is any acceptable char in grammar
 *      if pass, send to E_TAIL()
 * now in E_TAIL()
 *      check for U, ^, e
 *
 *
 * input: {123,e} U {e}
 *
 * start in E(); if
 * NT is {, so call S()
 *
 *
 *
*/