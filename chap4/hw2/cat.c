#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 80

int main(int argc, char *argv[])
{
    FILE *fp;
    int c;
    int line = 0;
    char buffer[MAXLINE];

    if(argc < 2)
        fp = stdin;
    else{
        if(strcmp(argv[1], "-n") == 0){
            for(int i=2; i<argc; i++)
            {
                fp = fopen(argv[i], "r");

                if(fp == NULL){
                    fprintf(stderr,"Error Open File\n");
                    exit(1);
                }

                while(fgets(buffer, MAXLINE,fp) != NULL){
                    line++;
                    printf("%3d %s", line, buffer);
                }
                line = 0;
                fclose(fp);
            }
        }
        else{
            for(int i=1; i<argc; i++)
            {
                fp = fopen(argv[i], "r");

                if(fp == NULL){
                    fprintf(stderr,"Error Open File\n");
                    exit(2);
                }

                c= getc(fp);
                while(c != EOF){
                    putc(c, stdout);
                    c = getc(fp);
                }
                fclose(fp);
            }
        }
    }

    return 0;
}