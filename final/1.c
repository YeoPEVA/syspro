#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int savePid = 0;
int sleepCount = 1;

int main()
{
        int pid;
        int getPidCount;

        printf("type num of childs : ");
        scanf("%d", &getPidCount);
        printf("\n");

        for(int i = 0; i<getPidCount; i++){
                pid = fork();

                if(pid == 0){
                        printf("[Child %d] : Started! pid=%d, sleep=%d\n",i,getpid(),sleepCount);
                        sleep(sleepCount);
                        exit(0);
                }else if(pid > 0){
                        if(i == getPidCount-1){
                                savePid = getpid();
                        }
                        waitpid(pid, NULL, 0);
                        printf("[Child %d] : Killed! pid=%d, sleep=%d\n", i,getpid(),sleepCount);
                }
                sleepCount += 1;
        }

        printf("parent killed - last child id = %d\n", savePid + getPidCount);

        exit(0);
}
