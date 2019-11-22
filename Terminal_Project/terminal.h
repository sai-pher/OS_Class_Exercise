//
// Created by sai-pher on 17/11/2019.
//

#ifndef TERMINAL_PROJECT_TERMINAL_H
#define TERMINAL_PROJECT_TERMINAL_H
#define _GNU_SOURCE

#include <stdio.h>  //the standard library file
#include <stdlib.h> //library file useful for dynamic allocation of memory
#include <string.h> //library file with functions useful to handle strings
#include <zconf.h>
#include <sys/wait.h>
#include <fcntl.h>

#define COMMAND_LEN 7
#define EXIT 0

#define SELECT_COM_INT(com, com_i) {for (int i = 0; i < COMMAND_LEN; ++i) {if (strcmp(com, COMMANDS[i]) == 0){com_i = i;break;}}};
#define RESET_FLAGS {FLGS->MCMD = 0;FLGS->RDRT = 0;};

typedef struct {
    int MCMD;
    int RDRT;
} flags;

flags f = {0, 0};
flags *FLGS = &f;

static const char *COMMANDS[COMMAND_LEN] = {"exit", "ls", "cd", "path", "read-path", "where", ">"};

//the function
char *get_line(char *string);

char **split(char *string, char del);

char *join(char **arr, char del, char *skip);

void execute_process(const char *command, char **args, int exf);

void where();

void path(char **args);

void read_path();

void cd(char *dir);

void interpreter(char *s_args);

/**==========================================================================================================*/

char *get_line(char *string) {
    int c;
    string = calloc(1, sizeof(char));
    string[0] = '\0';

    for (int size = 0; (c = getchar()) != '\n' && c != EOF; size += 1) {
        if (c == '&')
            FLGS->MCMD = 1;
        if (c == '>')
            FLGS->RDRT = 1;
        string = realloc(string, (size + 2) * sizeof(char));
        string[size] = (char) c;
        string[size + 1] = '\0';
    }

    return string;
}

char **split(char *string, char del) {
    int size = 1;
    int pos = 0;
    int n = 0;

    // Count del's
    for (unsigned long k = 0; k <= strlen(string); k += 1) {
        if (string[k] == del) {
            size += 1;
        }
        if (string[k] == '>')
            FLGS->RDRT = 1;
    }

    char **arr = calloc(size, sizeof(char *));
    char *temp = NULL;

    for (unsigned long i = 0; i < strlen(string); i += 1) {

        if (string[i] == del) {

            arr[pos + 1] = NULL;
            pos += 1;
            temp = NULL;
            n = 0;
        } else {
            temp = realloc(temp, (n + 2) * sizeof(char));
            temp[n] = string[i];
            temp[n + 1] = '\0';
            n += 1;
        }
        arr[pos] = temp;
        arr[pos + 1] = NULL;

    }

    return arr;
}

char *join(char **arr, char del, char *skip) {
    int size = 0;
    int i = 0;

    // count size of expected char array
    while (arr[i] != NULL) {
        int j = 0;
        while (arr[i][j] != '\0') {
            j += 1;
            size += 1;
        }
        i += 1;
        size += 1;
    }

    // create char array
    char *string = calloc(size + 1, sizeof(char));
    string[size] = '\0';

    // fill char array
    i = 0;
    int k = 0;
    while (arr[i] != NULL) {
        int m = 0;
        char *word = arr[i];

        if (strcmp(word, skip) == 0) {
            i += 1;
            continue;
        } else {
            while (word[m] != '\0') {
                string[k] = word[m];
                string[k + 1] = '\0';
                m += 1;
                k += 1;
            }
            string[k] = del;
            k += 1;
            i += 1;
        }
    }

    // strip last del from char array
    string[size - 1] = '\0';

    return string;
}

void execute_process(const char *command, char **args, int exf) {
    // Process tree

    int child_process = fork();

    if (child_process < 0) {
        printf("Error: Child process could not be created.\n");
        exit(1);
    }

    if (child_process == 0) {
        // Do magic
//        printf("\n==========\nSuccess: In child\n==========\n");

        if (exf == 0) {

            if (FLGS->RDRT) {
                int i = 0;
                while (strcmp(args[i], ">") != 0) {
                    i += 1;
                }
                char *file_name = args[i + 1];

                args[i] = NULL;
                args[i + 1] = NULL;

                int fd = open(file_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                dup2(fd, 1);

                execvp(command, args);

                close(fd);
            } else {
//                read_path();
//                where();
                execvp(command, args);
            }
            printf("Unknown Command: %s\n", command);
            exit(0);
        }
        return;
        exit(0);
    } else {
        // Complete
        wait(NULL);
//        printf("\n==========\nIn parent\n==========\n");
//        printf("\ncomplete: \nParent: %d\nChild: %d\n", (int) getpid(), child_process);
    }

}

void where() {
    char cwd[1024];
    printf(""
           "\n============================\n"
           "User: %s\n"
           "Cur dir: %s"
           "\n============================\n", getenv("USER"), getcwd(cwd, sizeof(cwd)));
}

void path(char **args) {
    char *path_str = join(args, ':', "path");

    setenv("PATH", path_str, 1);
}

void read_path() {
    char *env = getenv("PATH");
    if (env == NULL)
        printf("No PATH variable set\n");
    else {
        char **path = split(env, ':');
        if (path[0] == NULL) {
            printf("No PATH variable set\n");
        } else {
            printf("Current Paths:\n------------------\n");

            int i = 0;
            while (path[i] != NULL) {
                printf("%d:\t%s\n", i, path[i]);
                i += 1;
            }
            printf("------------------\n");
        }
    }
}

void cd(char *dir) {
    if (chdir(dir) != 0)
        printf("Unknown directory: %s\n", dir);
    else
        where();
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
        case 0:
            exit(0);
            break;
        case 2:
            cd(args[1]);
            break;
        case 3:
            path(args);
            read_path();

            break;
        case 4:
            read_path();
            break;
        case 5:
            where();
            break;
        case 6:
            break;
        default:
            execute_process(com, args, 0);
            break;
    }

}

#endif //TERMINAL_PROJECT_TERMINAL_H
