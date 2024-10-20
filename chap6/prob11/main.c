#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

char type(mode_t);
char *perm(mode_t);

void printStat(char*, char*, struct stat*, int);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];

    int mode = 0;

/* DEBUG
    for(int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
*/

    if (argc == 1){
        dir = ".";
    }else if(argc >= 2){
        // i-node 값 출력
        if(strcmp(argv[1], "-i") == 0){
            mode = 1;
            if(argc > 2) dir = argv[2];
            else dir = ".";
        // 디렉토리인 경우, / 추가
        }else if(strcmp(argv[1], "-p") == 0){
            mode = 2;
            if(argc > 2) dir = argv[2];
            else dir = ".";
        // 디렉토리인 경우, 쌍따음표 안에 출력
        }else if(strcmp(argv[1], "-Q") == 0){
            mode = 3;
            if(argc > 2) dir = argv[2];
            else dir = ".";
        }else{
            dir = argv[1];
        }
    }else{
        dir = argv[1];
    }

    if ((dp = opendir(dir)) == NULL){ // 디렉터리 열기
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) { // 디렉터리의 각 파일에 대해
        sprintf(path, "%s/%s", dir, d->d_name); // 파일경로명 만들기
        if (lstat(path, &st) < 0) // 파일 상태 정보 가져오기
            perror(path);
        else 
            // 상태 정보 출력 +
            printStat(path, d->d_name, &st, mode); 
    }

    closedir(dp);
    return 0;
}

/* 파일 상태 정보를 출력 */
void printStat(char *pathname, char *file, struct stat *st, int mode) 
{
    if(mode == 1){
        printf("%5d ", st->st_blocks);
        printf("%lu ", st->st_ino);
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
        printf("%3d ", st->st_nlink);
        printf("%s %s ", getpwuid(st->st_uid)->pw_name,
                    getgrgid(st->st_gid)->gr_name);
        printf("%9d ", st->st_size);
        printf("%.12s ", ctime(&st->st_mtime)+4);
        if(type(st->st_mode) == 'd'){
            printf("%s/\n", file);
        }else{
            printf("%s\n", file);
        }
    }else if(mode == 2){
        printf("%5d ", st->st_blocks);
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
        printf("%3d ", st->st_nlink);
        printf("%s %s ", getpwuid(st->st_uid)->pw_name,
                    getgrgid(st->st_gid)->gr_name);
        printf("%9d ", st->st_size);
        printf("%.12s ", ctime(&st->st_mtime)+4);
        if(type(st->st_mode) == 'd'){
            printf("%s/\n", file);
        }else{
            printf("%s\n", file);
        }
    }else if(mode == 3){ 
        printf("%5d ", st->st_blocks);
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
        printf("%3d ", st->st_nlink);
        printf("%s %s ", getpwuid(st->st_uid)->pw_name,
                    getgrgid(st->st_gid)->gr_name);
        printf("%9d ", st->st_size);
        printf("%.12s ", ctime(&st->st_mtime)+4);
        if(type(st->st_mode) == 'd'){
            printf("\"%s\"\n", file);
        }else{
            printf("%s\n", file);
        }
    }else{
        printf("%5d ", st->st_blocks);
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
        printf("%3d ", st->st_nlink);
        printf("%s %s ", getpwuid(st->st_uid)->pw_name,
                    getgrgid(st->st_gid)->gr_name);
        printf("%9d ", st->st_size);
        printf("%.12s ", ctime(&st->st_mtime)+4);
        printf("%s\n", file);
    }
}

/* 파일 타입을 반환 */
char type(mode_t mode) 
{
    if (S_ISREG(mode))
         return('-');
     if (S_ISDIR(mode))
         return('d');
    if (S_ISCHR(mode))
         return('c');
     if (S_ISBLK(mode))
         return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
        return('s');
}

/* 파일 접근권한을 반환 */
char* perm(mode_t mode) 
{
    static char perms[10];
    strcpy(perms, "---------");

    for (int i=0; i < 3; i++) {
        if (mode & (S_IRUSR >> i*3))
            perms[i*3] = 'r';
        if (mode & (S_IWUSR >> i*3))
            perms[i*3+1] = 'w';
        if (mode & (S_IXUSR >> i*3))
            perms[i*3+2] = 'x';
    }
     return(perms);
}