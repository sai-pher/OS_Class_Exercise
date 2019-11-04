//
// Created by sai-pher on 03/11/2019.
//

#include <stdio.h>  //the standard library file
#include <stdlib.h> //library file useful for dynamic allocation of memory
#include <string.h> //library file with functions useful to handle strings

//the function
char *scan(char *string) {
    int c; //as getchar() returns `int`
    string = malloc(sizeof(char)); //allocating memory
    char *command;
    string[0] = '\0';

    for (int i = 0; (c = getchar()) != '\n' && c != EOF; i++) {
        string = realloc(string, (i + 2) * sizeof(char)); //reallocating memory
        string[i] = (char) c; //type casting `int` to `char`
        string[i + 1] = '\0'; //inserting null character at the end
    }

    return string;
}

char **split(char *string, char del) {
    int size = 0;
    int n = 0;
    char **arr = calloc(size, sizeof(char *));
    char *temp = NULL;

    for (unsigned long i = 0; i < strlen(string); i += 1) {

        if (string[i] == del) {
            arr = realloc(arr, (size + 2) * sizeof(char *));
            arr[size + 1] = NULL;
            size += 1;
            temp = NULL;
            n = 0;
        } else {
            temp = realloc(temp, (n + 2) * sizeof(char));
            temp[n] = string[i];
            temp[n + 1] = '\0';
            n += 1;
        }
        arr[size] = temp;
    }

    return arr;
}

int main(void) {
    char *buf = NULL; //pointer to hold base address of string
    char **arr;

//    while (strcmp((buf = scan(buf)), "end") != 0) //this loop will continue till you enter `end`
//    {
//        //do something with the string
//
//        printf("you entered : %s\n", buf);
//        printf("size        : %lu\n", strlen(buf));
//
//        printf("\n-------------------\n");
//
//        free(buf); //don't forget to free the buf at the end of each iteration
//    }


    char *com = "";
    while (strcmp(com, "/exit") != 0) {
        printf(">>> ");

        buf = scan(buf);
        arr = split(buf, ' ');
        com = arr[0];

        printf("you entered : %s\n", buf);
        printf("size        : %lu\n", strlen(buf));

        printf("\n-------------------\n");

        char *r = arr[0];

        printf("your args   : 1: %s 1: %s 2: %s\n", arr[0], arr[1], arr[2]);
        printf("size        : %lu\n", strlen(*arr));

        //TODO: Read command
        //TODO: Pass it through switch statement
        //TODO: Check command exists
        //TODO: Execute in-house functions
        //TODO: Spawn a child process to handle that command
        //TODO: Support redirect
        //TODO: Support running parallel programs

        free(buf); //freeing `buf` for last input i.e, `end`
        free(arr);

    }

}
