#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFSIZE 1024

char savedText[10][100];

/* 파일 크기를 계산 한다 */
int main(int argc, char *argv[]) 
{
   char buffer[BUFSIZE];
   char buf;
   int fd;
   int n,i;

   ssize_t nread;
   long total = 0;
   n = 0;
   i = 0;

   if ((fd = open(argv[1], O_RDONLY)) == -1){ 
      perror(argv[1]);
      exit(1);
   }

   /* 파일의 끝에 도달할 때까지 반복해서 읽으면서 파일 크기 계산 */
   while( (nread = read(fd, buffer, BUFSIZE)) > 0)
      read(fd, &buf, 1);
      printf("%c", buf);
      savedText[n][i] = buf;
      i += 1;
      if(buf == "\n"){
        n += 1;
      }
      total += nread;

   close(fd);

/*
   for(n = 0; n <10; n++){
    i = 0;
    while(1){
        printf("%c", savedText[n][i]);
        i+=1;
        if(buf == "\n"){
            break;
        }
    }
   }
*/
   exit(0);
}
