#include "main.h"

DosatoFunctionMapList functions;
void* main_vm;

void init(void* vm) {
    main_vm = vm;

    init_DosatoFunctionMapList(&functions);

    write_DosatoFunctionMapList(&functions, (DosatoFunctionMap){"markdown_to_html", markdown_to_html});
}

char* output = NULL;

void md_callback(const MD_CHAR* text, MD_SIZE size, void* userdata) {
    output = realloc(output, strlen(output) + size + 1);
    strncat(output, text, size);
    output[strlen(output)] = '\0';
}

Value markdown_to_html(ValueArray args, bool debug) {
    if (args.count != 1) {
        return BUILD_EXCEPTION(E_WRONG_NUMBER_OF_ARGUMENTS);
    }

    Value arg = GET_ARG(args, 0);
    CAST_TO_STRING(arg);

    char* input = AS_STRING(arg);
    
    int size = strlen(input);
    if (size == 0) {
        return BUILD_STRING(COPY_STRING(""));
    }

    output = malloc(1);
    output[0] = '\0';

    int error_code = md_html(input, size, md_callback, NULL, 0, 0);

    if (error_code != 0) {
        PRINT_ERROR("Error parsing markdown: %d", error_code);
        return BUILD_EXCEPTION(E_EMPTY_MESSAGE);
    }

    return BUILD_STRING(output);
}