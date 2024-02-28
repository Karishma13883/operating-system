#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *pattern;
    int line_number = 0;


    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    pattern = argv[1];


    file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }


    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        if (strstr(line, pattern) != NULL) {
            printf("%s:%d:%s", argv[2], line_number, line);
        }
    }


    fclose(file);

    return 0;
}

