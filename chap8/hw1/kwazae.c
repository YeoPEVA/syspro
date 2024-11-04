#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    char **ptr;
    extern char **environ;
    char *ptr_one;

    if(argc == 1){
        perror(argv[1]);
        return 1;
    }

    // -e 환경변수 이름 
    // 지정된 이름의 환경 변수 값, 이름 없으면 모든 값 출력 
    if(strcmp(argv[1], "-e") == 0){
        if(argc > 2){
            ptr_one = getenv(argv[2]);
            printf("%s = %s \n", argv[2], ptr_one);
            
        }else{
            for(ptr = environ; *ptr != 0; ptr++)
                printf("%s \n", *ptr);
        }
    // -u 실행중인 프로세스 실제 사용자 ID, 유효 사용자 ID 
    }else if(strcmp(argv[1], "-u") == 0){
        printf("My Realistic User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
        printf("My Valid User ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
    // -g 실행중인 프로세스 실제 그룹 ID, 유효 그룹 ID 
    }else if(strcmp(argv[1], "-g") == 0){
        printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
        printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
    // 프로세스 ID 
    }else if(strcmp(argv[1], "-i") == 0){
        printf("my process number: [%d]\n", getpid());
    // 부모 프로세스 ID 
    }else if(strcmp(argv[1], "-p") == 0){
        printf("my parent process number: [%d]\n", getppid());
    }else{
        printf("ERROR!");
        return 1;
    }

    return 0;
}