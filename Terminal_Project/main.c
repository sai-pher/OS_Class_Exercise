//
// Created by sai-pher on 03/11/2019.
//

#include <stdio.h>  //the standard library file
#include <stdlib.h> //library file useful for dynamic allocation of memory
#include <string.h> //library file with functions useful to handle strings
#include <zconf.h>
#include <sys/wait.h>

#define COMMAND_LEN 6
#define EXIT 0

#define SELECT_COM_INT(com, com_i) {for (int i = 0; i < COMMAND_LEN; ++i) {if (strcmp(com, COMMANDS[i]) == 0){com_i = i;break;}}};
#define RESET_FLAGS {FLGS->MCMD = 0;FLGS->RDRT = 0;};

typedef struct {
    int MCMD;
    int RDRT;
} flags;

flags f = {0, 0};
flags *FLGS = &f;

static const char *COMMANDS[COMMAND_LEN] = {"exit", "ls", "cd", "path", "where", ">"};

//the function
char *get_line(char *string) {
    int c; //as getchar() returns `int`
    string = malloc(sizeof(char)); //allocating memory
    string[0] = '\0';

    for (int i = 0; (c = getchar()) != '\n' && c != EOF; i++) {
        if (c == '&')
            FLGS->MCMD = 1;
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

void execute_process(const char *command, char **args, int exf) {
    // Process tree

    int child_process = fork();


    if (child_process < 0) {
        printf("Error: Child process could not be created.\n");
        exit(1);
    } else if (child_process == 0) {
        // Do magic
//                printf("\nSuccess: In child\n");

        if (exf == 0) {
            execvp(command, args);
            exit(0);
        } else {
            chdir(args[1]);
            exit(0);
        }
    } else {
        // Complete
        wait(NULL);
//                printf("\ncomplete: \nParent: %d\nChild: %d\n", (int) getpid(), child_process);
    }

}

void where() {
    char cwd[1024];
    printf(""
           "\n============================\n"
           "User: %s\n"
           "Cur path: %s"
           "\n============================\n", getenv("USER"), getcwd(cwd, sizeof(cwd)));
}

void path(char **path_var, char **args) {
    path_var = args++;

    int i = 0;
    while (args[i] != NULL) {
        printf("%s ", path_var[i]);
        i += 1;
    }
    printf("\n");
}

void interpreter(char *s_args) {
    char **args;
    char *com = "";
    args = split(s_args, ' ');
    com = args[0];

    //TODO: Read command
    int com_i = -1;
    SELECT_COM_INT(com, com_i)

    switch (com_i) {
//        case -1:
//            printf("unknown command\n");
//            break;
        case 0:
            exit(0);
            break;
        case 1:
            execute_process(COMMANDS[1], args, 0);
            break;
        case 2:
            execute_process(COMMANDS[2], args, 1);
            break;
        case 3:
//            path(path_var, args);
            printf("pathing\n");
            break;
        case 4:
            where();
            break;
        default:
            execute_process(com, args, 0);
            break;
    }

}


int main(void) {

    RESET_FLAGS
    char *buf = NULL; //pointer to hold base address of string
    char **args;
    char *com = "";
    char **path_var = NULL;

    where();

    while (strcmp(com, COMMANDS[EXIT]) != 0) {
        printf("~> ");

        buf = get_line(buf);
        args = split(buf, ' ');
        com = args[0];

        //TODO: Read command
        int com_i = -1;
        SELECT_COM_INT(com, com_i)

        switch (com_i) {
//            case -1:
//                printf("unknown command\n");
//                break;
            case 0:
                exit(0);
                break;
            case 1:
                execute_process(COMMANDS[1], args, 0);
                break;
            case 2:
                execute_process(COMMANDS[2], args, 1);
                break;
            case 3:
                path(path_var, args);
                break;
            case 4:
                where();
                break;
            default:
//                printf("\ncom = %s\nargs = %s\n", com, (char *) args);
                execute_process(com, args, 0);
                break;
        }


//        if (strcmp(com, "ls") == 0){
//
//            // Process tree
//
//            int child_process = fork();
//
//
//            if (child_process < 0) {
//                printf("Error: Child process could not be created.\n");
//                exit(1);
//            } else if (child_process == 0) {
//                // Do magic
////                printf("\nSuccess: In child\n");
//
//                execvp(com, args);
//            } else {
//                // Complete
//                wait(NULL);
////                printf("\ncomplete: \nParent: %d\nChild: %d\n", (int) getpid(), child_process);
//            }
//
//        } else if(strcmp(com, "cd") == 0){
//            // Process tree
//
//            int child_process = fork();
//
//
//            if (child_process < 0) {
//                printf("Error: Child process could not be created.\n");
//                exit(1);
//            } else if (child_process == 0) {
//                // Do magic
//                printf("\nSuccess: In child\n");
//
//                chdir(args[1]);
//                printf(""
//                       "\n============================\n"
//                       "User: %s\n"
//                       "Cur path: %s"
//                       "\n============================\n", getenv("USER"), getcwd(cwd, sizeof(cwd)));
//            } else {
//                // Complete
//                wait(NULL);
////                printf("\ncomplete: \nParent: %d\nChild: %d\n", (int) getpid(), child_process);
//            }
//        }

        //TODO: Check command exists
        //TODO: Functions:
        // ls
        // cd
        // exit
        // path
        // redirect (>)
        //TODO: Pass it through switch statement
        //TODO: Execute in-house functions
        //TODO: Spawn a child process to handle that command
        //TODO: Support redirect
        //TODO: Support running parallel programs

        free(buf); //freeing `buf` for last input i.e, `end`
        free(args);

    }

}


