#include <stdio.h>
#define MAXLINE 100

/* popen() 함수를 이용해 자식에서 실행되는 명령어 출력을 받아 프린트 */
int main(int argc, char* argv[])
{
   char line[MAXLINE];
   FILE *fpin;
   if ((fpin = popen(argv[1],"r")) == NULL) {
      perror("popen 오류");
      return 1;
   }
   printf("The result from child process\n");
   while (fgets(line, MAXLINE, fpin))
      fputs(line, stdout);
   pclose(fpin);
   return 0;
}

