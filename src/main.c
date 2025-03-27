#include <stdio.h>
#include "compiler.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file.mcc> <output_file.c>\n", argv[0]);
        return 1;
    }

    if (compile(argv[1], argv[2]) != 0) {
        fprintf(stderr, "Compilation failed.\n");
        return 1;
    }

    printf("Compilation successful.\n");
    return 0;
}