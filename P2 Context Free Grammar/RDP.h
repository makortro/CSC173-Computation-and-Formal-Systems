#inclue "Tree.h"

/**
 * lookahead functions and variable
 */
bool isDigit();
bool isEpsilon();
bool isOperator(); //non-digit terminal symbol
bool isTerminalSymbol();
char *nextTerminal; //current position in input string

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
 */
TREE E(), S(), L(), N(), D(), A();
TREE E_Tail(), S_Tail(), Ls(), L_Tail(), N_Tail();