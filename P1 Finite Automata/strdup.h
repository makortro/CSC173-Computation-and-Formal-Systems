/*
 * File: strdup.h
 * Creator: George Ferguson
 *
 * Incredibly, strdup is in string.h but not part of ANSI standard C.
 */

#ifndef _strdup_h_gf
#define _strdup_h_gf

#include <string.h>

/**
 * From strdup(3): allocates sufficient memory for a copy of the
 * string s, does the copy, and returns a pointer to it.
 */
extern char* strdup(const char* s);

#endif
