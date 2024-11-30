#include "main.h"

DosatoFunctionMapList functions;
void* main_vm;

void init(void* vm) {
    main_vm = vm;

    init_DosatoFunctionMapList(&functions);

    write_DosatoFunctionMapList(&functions, (DosatoFunctionMap){"markdown_parse", markdown_parse});
}

Value markdown_parse(ValueArray args, bool debug) {
    if (args.count != 1) {
        return BUILD_EXCEPTION(E_WRONG_NUMBER_OF_ARGUMENTS);
    }

    Value arg = GET_ARG(args, 0);
    CAST_TO_STRING(arg);

    char* input = AS_STRING(arg);
    
    char* output = markdown_parse_string(input);
    

    return BUILD_STRING(output);
}

#define SAFE_APPEND(output, str) do { \
    output = realloc(output, strlen(output) + strlen(str) + 1); \
    strcat(output, str); \
} while (0)


char* markdown_parse_string(char* input) {
    char* output = malloc(1);
    output[0] = '\0';

    char* line = strtok(input, "\n");

    // per line rules
    while (line != NULL) {
        if (line[0] == '#') {

            // check how many # there are
            int i = 0;
            while (line[i] == '#') {
                i++;
            }

            if (i > 6) {
                i = 6;
            }

            char* tag = malloc(3);
            tag[0] = 'h';
            tag[1] = '0' + i;
            tag[2] = '\0';

            SAFE_APPEND(output, "<");
            SAFE_APPEND(output, tag);
            SAFE_APPEND(output, ">");
            SAFE_APPEND(output, line + i);
            SAFE_APPEND(output, "</");
            SAFE_APPEND(output, tag);
            SAFE_APPEND(output, ">");

            free(tag);
        } else if (line[0] == '*' || line[0] == '+' || line[0] == '-') {
            SAFE_APPEND(output, "<ul><li>");
            SAFE_APPEND(output, line + 1);
            SAFE_APPEND(output, "</li></ul>");
        } else if (line[0] == '>') {
            SAFE_APPEND(output, "<blockquote>");
            SAFE_APPEND(output, line + 1);
            SAFE_APPEND(output, "</blockquote>");
        } else {
            SAFE_APPEND(output, "<p>");
            do {
                SAFE_APPEND(output, line);

                // check for line breaks
                int size = strlen(line);    
                if (size > 1) {
                    if (line[size - 1] == ' ' && line[size - 2] == ' ') {
                        SAFE_APPEND(output, "<br>");
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } while ((line = strtok(NULL, "\n")) != NULL);

            SAFE_APPEND(output, "</p>");
        }
        line = strtok(NULL, "\n");
    }

    return output;
}