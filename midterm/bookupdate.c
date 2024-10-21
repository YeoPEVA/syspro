#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define START_ID 1
#define MAX 24

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
   int fd, mode, id;
   char c;
   struct book record;
   if (argc < 2) {
      fprintf(stderr, "How to use : %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_RDWR)) == -1) {
      perror(argv[1]);
      exit(2);
   }
   printf("--bookupdate--\n");
   while(1) {
      printf("0 bookId: borrow book, 1 bookId: return book ) ");
	  scanf("%d %d", &mode, &id);
	  printf("\n");
	  
		  if(mode == 0){
			 printf("You've got bellow book..\n");
             lseek(fd, (long) (id-START_ID)*sizeof(record), SEEK_SET);
			 if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
              printf("id \t bookname \t author: \t year \t numberofborrow \t borrow\n");
              printf("%d \t %s \t %s \t %d \t %d ",
					  record.id, record.bookName, record.bookAuthor, record.releaseDate, record.lenCount);
		      if(record.isLen == 1){
				  printf("True");
			  }else{
				  printf("False");
			  }
			  
			  record.isLen = 1;
			  record.lenCount += 1;

              lseek(fd, (long) -sizeof(record), SEEK_CUR);
              write(fd, (char *) &record, sizeof(record));
             } else printf("Record %d Null\n", id);
           }else if(mode == 1){
			  printf("You've returned bellow book..\n");
			  lseek(fd, (long) (id-START_ID)*sizeof(record), SEEK_SET);
              if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
               printf("id \t bookname \t author: \t year \t numberofborrow \t borrow\n");
               printf("%d \t %s \t %s \t %d \t %d ",
                       record.id, record.bookName, record.bookAuthor, record.releaseDate, record.lenCount);
               if(record.isLen == 1){
                   printf("True");
               }else{
                   printf("False");
               }

               record.isLen = 1;
               record.lenCount += 1;

               lseek(fd, (long) -sizeof(record), SEEK_CUR);
               write(fd, (char *) &record, sizeof(record));
			   continue;
             } else printf("Record %d Null\n", id);
		  }else{
			  printf("Option Error\n");
		  }
	  printf("\n");
      }  
   close(fd);
   exit(0);
}
