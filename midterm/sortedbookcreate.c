#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
   struct book record;

   struct book tmp[30];


   if (argc < 2) {
      fprintf(stderr, "How to use : %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_RDONLY)) == -1) {
      perror(argv[1]);
      exit(2);
   }
   printf("--bookquery--\n");
   while(1) {
      printf("0: list of all books, 1: list of available books ) ");
	  scanf("%d", &mode);
	  count = 1;

      if (mode == 0) {
         lseek(fd, 0, SEEK_SET);
		 while(1){
         if ((read(fd, (char *) &record, sizeof(record)) > 0)){
			 printf("id:%d\t bookname:%s\t author:%s\t year:%d\t numofborrow:%d\t borrow: ", 
					 record.id, record.bookName, record.bookAuthor, record.releaseDate, record.lenCount);
			 if(record.isLen == 1){
				 printf("True\n");
			 }else{
				 printf("False\n");
			 }
			}else {
				break;
				printf("Record %d Null\n", mode);
			}
		 	lseek(fd, count * sizeof(record), SEEK_SET);
			count += 1; 
		 }
      }else if(mode == 1){
         lseek(fd, 0, SEEK_SET);
		 while(1){
          if ((read(fd, (char *) &record, sizeof(record)) > 0)){
			  if(record.isLen == 0){
				  count += 1;
				  continue;
			  }
              printf("id:%d\t bookname:%s\t author:%s\t year:%d\t numofborrow:%d\t borrow: ",
                      record.id, record.bookName, record.bookAuthor, record.releaseDate, record.lenCount);
              if(record.isLen == 1){
                 printf("True\n");
              }else{
                 printf("False\n");
              }
          }else {
                break;
                printf("Record %d Null\n", mode);
             }
             lseek(fd, count * sizeof(record), SEEK_SET);
             count += 1;
          }
	  }else{
		printf("input Error. \n");
	  }
   } 
   close(fd);
   exit(0);
}

