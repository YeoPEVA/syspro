#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

int main(int argc, char *argv[])
{
   char c;
   FILE *fp1, *fp2;
   int optionValue = 0;


   if (argc !=4) {
      fprintf(stderr,  "How to use: %s optionValue File1 File2\n", argv[0]);
      return 1;
   }

   if (argc == 4){
	   optionValue = atoi(argv[1]);
   }
   
   fp1 = fopen(argv[2], "r");
   if (fp1 == NULL) {
      fprintf(stderr, "File %s Open Error\n", argv[1]);
      return 2;
    }

   fp2 = fopen(argv[3], "w");

   if(optionValue == 0){
   		while((c = fgetc(fp1)) != EOF)
      		fputc(c, fp2);
	}else if(optionValue == 1){
			while((c = fgetc(fp1)) != EOF){
				c = tolower(c);
				fputc(c, fp2);	
			}
	}else if(optionValue == 2){
		while((c =fgetc(fp1)) != EOF){
			c = toupper(c);
			fputc(c, fp2);
		}
	}

   fclose(fp1);
   fclose(fp2);
   return 0;
}

