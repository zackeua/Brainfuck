#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int freeAll(char *data, char *instruction, int ret) {
    free(data);
    free(instruction);
    return ret;
}

int main(int argc, char const *argv[]) {
    if (argc < 2) { // basic error handling
        printf("No file to run\n");
        return 0;
    }
    else if (argc > 2) {
        printf("Too many input arguments\n");
        return 0;
    }
    else {
        int len = strlen(argv[1]);
        if (!((argv[1][len-2] == '.' && argv[1][len-1] == 'b') || (argv[1][len-3] == '.' && argv[1][len-2] == 'b' && argv[1][len-1] == 'f'))) {
            printf("Wrong filetype\n");
            return 0;
        }
    }

    FILE* fp;
    fp = fopen(argv[1],"r");
    if (fp == NULL) {
        printf("File not found\n");
        return 0;
    }

    int numberOfInstrunctions = 0;
    int instructionPointer = 0;
    int dataPointer = 0;
    int maximumMumberOfInstructions = 10;
    int maximumNumberOfData = 1024;
    char *instruction = calloc(maximumMumberOfInstructions, sizeof(*instruction));
    char *data = calloc(maximumNumberOfData, sizeof(*data));
    char buffer;
    while (fscanf(fp, " %c", &buffer)!= EOF) { // parse file
        if (buffer == '>' || buffer == '<' || buffer == '+' || buffer == '-' || buffer == '.' || buffer == ',' || buffer == '[' || buffer == ']') {
            instruction[numberOfInstrunctions] = buffer;
            numberOfInstrunctions++;
            if (numberOfInstrunctions == maximumMumberOfInstructions) {
                maximumMumberOfInstructions = maximumMumberOfInstructions * 2;
                instruction = realloc(instruction, maximumMumberOfInstructions*sizeof(*instruction));
                if (instruction == NULL) {
                    printf("Instruction register could not grow\n");
                    return freeAll(data, instruction, -1);
                }
            }
        }
    }
    fclose(fp);
    fp = NULL;

    while (instructionPointer < numberOfInstrunctions) { // run instructions
        if (instruction[instructionPointer] == '>')
            dataPointer++;
        if (dataPointer >= maximumNumberOfData) {
            maximumNumberOfData = maximumNumberOfData * 2;
            data = realloc(data, maximumNumberOfData * sizeof(*data));
        }
        if (data == NULL) {
            return freeAll(data, instruction, -1);
        }
        else if (instruction[instructionPointer] == '<')
            dataPointer--;
        else if (instruction[instructionPointer] == '+')
            (data[dataPointer])++;
        else if (instruction[instructionPointer] == '-')
            (data[dataPointer])--;
        else if (instruction[instructionPointer] == '.')
            printf("%c", data[dataPointer]);
        else if (instruction[instructionPointer] == ',') {
            scanf(" %c", &buffer);
            data[dataPointer] = buffer;
        }
        else if (instruction[instructionPointer] == '[') {
            if (data[dataPointer] == 0) {
                int count = 1;
                while (count != 0) {
                    instructionPointer++;
                    if (instruction[instructionPointer] == '[') {
                        count++;
                    }
                    else if (instruction[instructionPointer] == ']') {
                        count--;
                    }
                }
            }
        }
        else if (instruction[instructionPointer] == ']') {
            if (data[dataPointer] != 0) {
                int count = -1;
                while (count != 0) {
                    instructionPointer--;
                    if (instruction[instructionPointer] == '[') {
                        count++;
                    }
                    else if (instruction[instructionPointer] == ']') {
                        count--;
                    }
                }
            }
        }
        instructionPointer++;
    }


    return freeAll(data, instruction, 0);
}
