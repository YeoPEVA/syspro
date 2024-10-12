#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFSIZE 1024

char savedText[10][100];

int main(int argc, char *argv[]) 
{
   char buffer[BUFSIZE];
   char buf;
   char select[10];

   int fd;
   int count1, count2;
   count1 = 0;
   count2 = 0;

   ssize_t nread;

   if ((fd = open(argv[1], O_RDONLY)) == -1){ 
      perror(argv[1]);
      exit(1);
   }

   while(1){
      if(read(fd, &buf, 1) > 0){
         if (buf == '\n') {
            savedText[count1][count2] = '\0'; 
            count1 += 1;
            count2 = 0;
         } else {
            savedText[count1][count2] = buf;
            count2++;
         }
      } else {
         if (count2 > 0) { 
            savedText[count1][count2] = '\0';  
            count1 += 1;
         }
         break;
      }
   }

   // 역순으로 줄 출력
   for (int i = count1 - 1; i >= 0; i--) {
       printf("%s\n", savedText[i]); 
   }

   close(fd);
   exit(0);
}
