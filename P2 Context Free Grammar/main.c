/**
 * CSC 173 PROJECT 2 - Context Free Grammar
 * Author: MaKayla Robinson [mrobin45 @ u.rochester.edu]
 */

#include "RDP.h"
#include "Tree.h"

#include <stdbool.h>
#include <stdio.h>

void printIndentedTree(TREE node);
int height; //used in printing method to keep track of tree height

/**
 * GRAMMAR:
 * <E> -> <E>U<E> | <E>^<E> | (<E>) | <S>       //check for U ^ ( ) { } e
 * <S> -> {} | {<L>}                            //check for {e} {digit}
 * <L> -> <L> | <L>,<L> | <N>                   //know digit exists, send to N(); once returned check for ,
 * <N> -> <D> | <N>,<D>                         //know digit exists, send to D(); check for more digits or e
 * <D> -> 0|1|...|9                             //create node for digit and root label, return to N()
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

int main(int argc, char **argv) {
    char userInput[100];

    TREE h = makeNode0('H');
    TREE g = makeNode1('G', h);
    TREE d = makeNode1('D', g);
    TREE c = makeNode2('C', makeNode0('E'), makeNode0('F'));
    TREE a = makeNode4('A', makeNode0('B'), c, d);

    printIndentedTree(a);

    /*
    //loop for user input; x or X to quit
    do {
        printf("Please enter your input (or 'X' to quit): ");
        gets(userInput);

        //check if well-formed grammar
        int isWellFormed = isWellFormed(userInput);
        if (isWellFormed != 0) {

        } else {
            printf("Input isn't well-formed. Please try again.");
        }

        //send array to E() to create root of expression tree

    } while (strcmp(userInput[0], 'X') != 0 || strcmp(userInput[0], 'x') != 0);
    */
}

//check if input matches grammar
bool isWellFormed(char *c[]) { //takes array of string
    for (int i = 0; i < c.length; i++) {
        switch (c[i]) {
            case '':
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
}

/**
 * DON'T FORGET TO DELETE THIS CODE TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
 */
/*
#include "ParseTable.h"
#include "RecursiveParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Convert.h"

int prettyPrinter = 0;//Used by Pretty Printer

#define MAX_INPUT_LEN 1024


void printTree(TREE root){
    if(!root){
        return;
    }
    prettyPrinter++;
    for(int i=0;i<prettyPrinter;i++) printf("  ");
    printf("%s\n",(root->label));
    if(root->leftmostChild){
        printTree(root->leftmostChild);
        if(root->leftmostChild->rightSibling){
            printTree(root->leftmostChild->rightSibling);
            if(root->leftmostChild->rightSibling->rightSibling){
                printTree(root->leftmostChild->rightSibling->rightSibling);
            }
        }

    }

    prettyPrinter--;
}


void REPL(){
    char input[MAX_INPUT_LEN];
    while(1 == 1){
        printf("Enter an input ('q' to quit): ");
        scanf("%s",input);
        if(!strcmp(input,"q")){
            printf("\n");
            return;
        }
        printf("Generating Parse Tree From Input....\n");
        TREE parseTree = generateParseTree(input);
        if(parseTree == NULL){
            printf("Invalid Input\n");
        } else {
            printf("Parse Tree Generated Successfully\n");
            TREE parseRecursiveTree = getRecursiveParseTree(input);
            printf("Recursive Tree:\n");
            printTree(parseRecursiveTree);
            printf("Table Parser Tree:\n");
            printTree(parseTree);
            TREE final = buildExpressionTree(parseTree);
            printf("Expression Tree: \n");
            printTree(final);
            printf("Expression Prefix Notation: \n");
            printPrefix(final);
            printf("\n");
        }

    }
}

int main(){
    REPL();
}*/


/*
 * pre-order printing (print, go left, go right)
 * print
 *      check if left child
 *          if true: height++, visit left child
 *          if false: height--, return to parent
 *      check if right sib (LOOP UNTIL RIGHT SIB == NULL)
 *          if true, then height++, visit right sib
 *          if false: height--, return to parent
 *
 */

/**
 * pre-order print will print node, then check for left child, then right sibling.
 * each time a child is found the height will be incremented for appropriate tree height.
 * each time a child returns to its parent the height will be decremented.
 */
void printIndentedTree(TREE node) {
    if (node == NULL) {
        printf("Sorry, tree is null. Cannot print.");
        return;
    }

    //printf("%*d",b,a); Print in 'b' spaces, 'a' is variable to print
    printf("%*c",height,node->label);
    if (node->leftmostChild != NULL) { //has left child
        height++;
        printIndentedTree(node->leftmostChild);
    } else {
        height--;
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (node->rightSibling != NULL) { //has right child
            height++;
            printIndentedTree(node->rightSibling);
        } else {
            height--;
            return;
        }
    }
}