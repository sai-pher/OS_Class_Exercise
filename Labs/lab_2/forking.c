#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void printAll(int x[][]){
    
}



int main() {

    printf("hi. i'm the parent process\nPID:-> %d\n", (int) getpid());

    int newChildProcess = fork();

    if (newChildProcess < 0)        
    {
        printf(stderr, "Fork creation failed");
    }else if(newChildProcess == 0)
    {
        printf("The kid ins't dead!\nPID:-> %d\n", (int) getpid());
    } else
    {
        int waitValue = wait(NULL);
        printf("parent %d of child %d\n", (int) getpid(), newChildProcess);
    }
    
    
    


    return 0;
}