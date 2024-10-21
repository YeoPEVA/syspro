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
   int fd;
   struct book record;

   char temp[10];

   if (argc < 2) {
      fprintf(stderr, "How to use: %s file\n", argv[0]);
      exit(1);
   }

   if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
      perror(argv[1]);
      exit(2);
   }
   
   printf("%-9s %-8s %-4s %-5s %-4s %-8s\n", "id", "bookName", "author", "year", "numofborrow", "borrow");
   while (scanf("%d %s %s %d %d %s", &record.id, &record.bookName, &record.bookAuthor, &record.releaseDate, &record.lenCount, &temp) == 6) {
	   if(strcmp(temp, "True") == 0){
		   record.isLen = 1;
	   }else{
		   record.isLen = 0;
	   }
      lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
      write(fd, (char *) &record, sizeof(record) );
   }
   close(fd);
   exit(0);
}

