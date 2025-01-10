
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int main()
{
        int pid1;
        int pid2;
        int pid3;

        int tmppid;
        int tmppid2;
        int tmppid3;
        int tmppid4;

        pid1 = fork();
        if(pid1 == 0){
                printf("Hello\n");

                tmppid = fork();
                tmppid2 = fork();

                if(tmppid == 0){
                        printf("Hello\n");
                        exit(0);
                }

                if(tmppid2 == 0){
                        printf("Hello\n");
                        tmppid3 = fork();

                        if(tmppid3 == 0){
                                printf("Hello\n");
                                exit(0);
                        }
                        exit(0);
                }
                exit(0);
        }else{
       printf("Hello\n");
        }

        sleep(5);

        pid2 = fork();
        if(pid2 == 0){
                printf("Hello\n");
                exit(0);
        }

        sleep(5);

        pid3 = fork();
        if(pid3 == 0){
                printf("Hello\n");
                tmppid = fork();

                if(tmppid == 0){
                        printf("Hello\n");
                        exit(0);
                }
                exit(0);
        }
        sleep(5);
        exit(0);
}
