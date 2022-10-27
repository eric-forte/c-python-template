#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mynum.h"


int my_add(int input_one, int intput_two) {
    int result; 
    result = input_one + intput_two;
    //printf("Result: %d", result);
    return result;
}

/* Return by pointer */
Mynum* get_mynum(int in_num, char* in_desc) {
    Mynum* structptr = malloc(sizeof(Mynum));
    structptr->num = in_num;
    structptr->desc = malloc(sizeof(in_desc) / sizeof(char*));
    strcpy(structptr->desc, in_desc);
    //printf("%d: %s\n", structptr->num, structptr->desc);
    return structptr;
}

void free_mynum(Mynum* mynum) {
    free(mynum->desc);
    free(mynum);
}

void print_mynum(Mynum mynum) {
    printf("Object Mynum is: %d, %s \n", mynum.num, mynum.desc);
}

void print_mynum_pointer(Mynum* mynum) {
    printf("Object Mynum is: %d, %s \n", mynum->num, mynum->desc);
}

char* alloc_C_string(char* input) {
    char* phrase = strdup(input);
    return phrase;
}
