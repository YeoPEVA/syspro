#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX 24
#define START_ID 1
#define false 0
#define true 1

struct book{
    char bookName[MAX];
    char bookAuthor[MAX];
    int id;
    int releaseDate;
    int lenCount;
    int isLen;
};


int main(int argc, char *argv[])
{
   int fd, mode;
   int count = 1;
   char c; 
   char tmp[30];
   struct book record;
   if (argc < 2) {
      fprintf(stderr, "How to use : %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_RDONLY)) == -1) {
      perror(argv[1]);
      exit(2);
   }
   while(1) {
      printf("input name of book ) ");
	  scanf("%s", &tmp);
	  count = 1;
	  mode = 0;

      lseek(fd, 0, SEEK_SET);
	  while(1){
         if ((read(fd, (char *) &record, sizeof(record)) > 0)){
			 if(strcmp(record.bookName, tmp) == 0){
			     printf("id\t bookname\t author\t year\t numofborrow\t borrow \n");
			     printf("%d\t %s\t %s\t %d\t %d\t",
						 record.id, record.bookName, record.bookAuthor, record.releaseDate, record.lenCount);
			 	if(record.isLen == 1){
					 printf("True\n");
			 	}else{
				 	printf("False\n");
			 	}
				mode = 1;
			 }
		 	lseek(fd, count * sizeof(record), SEEK_SET);
			count += 1; 
		 }else{
			break;
		 }
	  }
	 if(mode == 0){
					printf("not found book name : \'%s\'\n", tmp);
	 }
	}
   
   close(fd);
   exit(0);

}
