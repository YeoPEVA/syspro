#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("parental process start\n");
    if(fork() == 0){
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "first Fail");
        exit(1);
    }
    if(fork() == 0){
        execl("/bin/date", "date", NULL);
        fprintf(stderr, "second Fail");
        exit(2);
    }
    if(fork() == 0){
        execl("/bin/ls", "ls", "-l", NULL);
        fprintf(stderr, "third Fail");
        exit(3);
    }

    printf("prarental process end\n");
}