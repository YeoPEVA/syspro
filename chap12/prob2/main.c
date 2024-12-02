#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 100

/* 파이프를 통해 자식에서 실행되는명령어 출력을 받아 프린트 */
int main(int argc, char* argv[])
{
    int n, pid, fd[2];
    char line[MAXLINE];
    pipe(fd);   /* 파이프 생성 */


    if ((pid = fork()) == 0) {    //자식 프로세스 
       close(fd[0]);
       dup2(fd[1],1); 
       close(fd[1]);
       printf("Hello! pipe\n");
       printf("Bye! pipe\n");
    } else {       // 부모 프로세스 
       close(fd[1]);
       printf("The result from child process\n");
       while ((n = read(fd[0], line, MAXLINE))> 0)
          write(STDOUT_FILENO, line, n);
    }

    exit(0);
}