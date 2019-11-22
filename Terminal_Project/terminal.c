//
// Created by sai-pher on 17/11/2019.
//

#include "terminal.h"

int main(int argc, char *argv[]) {

    RESET_FLAGS
    clearenv();
    setenv("PATH", "", 1);
    char *buf = NULL; //pointer to hold base address of string

    if (argc >= 2) {
        FILE *stream;
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;

        stream = fopen(argv[1], "r");
        if (stream == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        while ((nread = getline(&line, &len, stream)) != -1) {
            RESET_FLAGS

            line[nread - 1] = '\0';
            printf("args: %s\n", line);

            //check flags
            int i = 0;
            while (line[i] != '\0') {
                if (line[i] == '&')
                    FLGS->MCMD = 1;
//                if (line[i] == '>')
//                    FLGS->RDRT = 1;
                i += 1;
            }

//            printf("\n------------------\nMCMD: %d\t\t\tRDRT: %d\n------------------\n",FLGS->MCMD, FLGS->RDRT);

            if (FLGS->MCMD == 1) {
                char **margs = split(line, '&');

                int j = 0;
                while (margs[j] != NULL) {
                    interpreter(margs[j]);
                    j += 1;
                }
            } else {
                interpreter(line);
            }
        }

        free(line);
        fclose(stream);
        exit(0);
    } else {

        where();

        while (1) {
            RESET_FLAGS

            printf("wish> ");

            buf = get_line(buf);

            if (FLGS->MCMD == 1) {
                char **margs = split(buf, '&');

                int i = 0;
                while (margs[i] != NULL) {
                    interpreter(margs[i]);
                    i += 1;
                }
            } else {
                interpreter(buf);
            }
        }
    }
    return 0;
}
