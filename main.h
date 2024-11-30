#ifndef MAIN_H
#define MAIN_H

#include "dosato_source/dosato.h" // Include the dosato library API
#include "src/md4c-html.h" // Include the markdown parser library


void init(void* vm);

DosatoFunctionMapList functions;


Value markdown_to_html(ValueArray args, bool debug);
Value markdown_parse_html(ValueArray args, bool debug);

#endif // MAIN_H