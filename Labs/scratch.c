#include <stdlib.h>
#include <stdio.h>

char *reverse(char *arr, int len){

    char *res;

    for (int i = len; i > 0; i-=1)
    {
        res[len - i] = arr[i];
    }
    
    return res;
}


int main(int argc, char const *argv[])
{
    int arrLen = 10;
    char *arr = "1234567890";

    char *res = reverse(arr, arrLen);

    printf("%s", res);
    return 0;
}
