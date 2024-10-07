#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 1024

/* 파일 크기를 계산 한다 */
int main(int argc, char *argv[]) 
{
   char buffer[BUFSIZE];
   int fd;
   ssize_t nread;
   long total = 0;
   double total_mb = 0.0;


   if ((fd = open(argv[1], O_RDONLY)) == -1){ 
      perror(argv[1]);
      exit(1);
   }

   /* 파일의 끝에 도달할 때까지 반복해서 읽으면서 파일 크기 계산 */
   while( (nread = read(fd, buffer, BUFSIZE)) > 0)
      total += nread;

   close(fd);

   total_mb = (double)total/1024;
   
   printf ("File Name : %s \nFile Size (MB) : %f\nFile Byte : %ld \n", argv[1], total_mb, total);
   exit(0);
}
