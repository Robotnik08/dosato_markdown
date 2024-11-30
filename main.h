#ifndef MAIN_H
#define MAIN_H

#include "dosato_source/dosato.h" // Include the dosato library API


void init(void* vm);

DosatoFunctionMapList functions;


Value markdown_parse(ValueArray args, bool debug);

char* markdown_parse_string(char* input);

#endif // MAIN_H