#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE]; // 입력 줄
char tmp[MAXLINE]; // tmp 공간 
char longest[MAXLINE]; // 가장 긴 줄
char userstring[5][MAXLINE]; // 입력 값 저장 

/* 입력 줄 가운데 가장 긴 줄을 프린트한다. */

int main(){
  int len;
  int max;
  int count;
  int i, j = 0;

  count = 0;
  max = 0;

  while(gets(line) != NULL) {
    len = strlen(line);

    if(len > max) {
       max = len;
       copy(line, longest);
    }

    copy(line, userstring[count]);
    if(count == 4){
	    break;
	  }
    count++;
  }

  for(i=1; i<=4; i++){
    for(j=0; j<5-i; j++){
      if(strlen(userstring[j])<strlen(userstring[j+1])){
        strcpy(tmp, userstring[j+1]);
        strcpy(userstring[j+1], userstring[j]);
        strcpy(userstring[j], tmp);
      }
    }
  }

  if(max > 0){
    for(i = 0; i < 5; i++){
      printf("%d : ", i);
      printf("%s \n", userstring[i]);
    }
  }

  return 0;
}
