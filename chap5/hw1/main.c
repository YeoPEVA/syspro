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
   int selecttoint;

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
         // putchar(buf);
         savedText[count1][count2] = buf;
         count2++;

         if(buf == '\n'){
            savedText[count1][count2] = '\0'; // 문자열의 끝 표시
            count1 += 1;
            count2 = 0;
         }
      }else{
         if (count2 > 0) { 
            savedText[count1][count2] = '\0';  // 문자열의 끝 표시
            count1 += 1;
        }
        break;;
      }
   }

   printf("File read success\n");
   printf("Total Line : %d\n", count1);
   printf("You can Choose 1 ~ %d Line\n", count1);
   printf("pls 'Enter' the line to select : ");
   
   scanf("%s", select);

   // 모든 줄
   if(select[0] == '*'){
      for(int i = 0; i < count1; i++){
         printf("%s", savedText[i]);
      }
   }

   // 줄 범위 n-m
   else if(strchr(select, '-') != NULL){
      int start, end;
      sscanf(select, "%d-%d", &start, &end);
      if (start >= 1 && end <= count1 && start <= end) {
         for(int i = start - 1; i < end; i++){
            printf("%s", savedText[i]);
         }
      } else {
         printf("Wrong Range.\n");
      }
   }

   // 줄 번호 리스트 n,m,..
   else if(strchr(select, ',') != NULL){
      char *token = strtok(select, ",");
      while(token != NULL){
         int line = atoi(token);
         if(line >= 1 && line <= count1){
            printf("%s", savedText[line - 1]);
         } else {
            printf("Wrong Line: %d\n", line);
         }
         token = strtok(NULL, ",");
      }
   }

   // 한 줄 번호
   else{
      selecttoint = atoi(select);
      if (selecttoint >= 1 && selecttoint <= count1) {
         printf("%s", savedText[selecttoint - 1]);
      } else {
         printf("Wrong Line Number.\n");
      }
   }

   // printf("\n");

   close(fd);
   exit(0);
}
