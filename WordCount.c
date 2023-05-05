#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 100
#define MAX_WORD_LEN 1000

void print_usage()
{
    printf("Usage: WordCount.exe [-c | -w] [input_file_name]\n");
}

int main(int argc, char* argv[])
{
    char* file;
    char buffer[MAX_WORD_LEN];
    int i, len, start, count, word_count;
    FILE* fp;
    int mode = 0; // 0: count characters, 1: count words

    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_usage();
        return 0;
    }

    if (argc < 2 || argc > 3) {
        printf("Error: Invalid arguments.\n");
        print_usage();
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        mode = 0;
    }
    else if (strcmp(argv[1], "-w") == 0) {
        mode = 1;
    }
    else {
        printf("Error: Invalid argument %s.\n", argv[1]);
        print_usage();
        return 1;
    }

    if (argc == 3) {
        file = argv[2];
    }
    else {
        file = "input.txt";
    }

    if (fopen_s(&fp, file, "r") != 0) {
        printf("Error: Failed to open file %s.\n", file);
        return 1;
    }

    count = 0;
    word_count = 0;
    while (!feof(fp)) {
        len = fread(buffer, 1, MAX_WORD_LEN, fp);
        start = 0;
        for (i = 0; i < len; i++) {
            count++;
            if (mode == 1 && (buffer[i] == ' ' || buffer[i] == ',')) {
                if (i > start) {
                    word_count++;
                }
                start = i + 1;
            }
        }
        if (mode == 0) {
            word_count += len;
        }
        else if (len > start) {
            word_count++;
        }
    }

    printf("%s count: %d\n", mode == 0 ? "Character" : "Word", word_count);

    fclose(fp);
    return 0;
}
