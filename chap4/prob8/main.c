#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _IO_UNBUFFERED 0x0002
#define _IO_LINE_BUF 0x0200

// Not Work -  Mac OS

int main(int argc, char *argv[])
{
    FILE *fp;
    if(!strcmp(argv[1], "stdin")){
        fp = stdin;
        printf("Enter one letter.");
        if(getchar() == EOF) perror("getchar");
    }
    else if(!strcmp(argv[1], "stdout"))
        fp = stdout;
    else if(!strcmp(argv[1], "stderr"))
        fp = stderr;
    else if((fp = fopen(argv[1], "r"))== NULL){
        perror("fopen");
        exit(1);
    }
    else if(getc(fp) == EOF) perror("getc");

    printf("Stream = %s, ", argv[1]);

    if (fp->_flags & _IO_UNBUFFERED)
        printf("버퍼 미사용");
    else if (fp->_flags & _IO_LINE_BUF)
        printf("줄 버퍼 사용");
    else 
        printf("완전 버퍼 사용");

    printf(", 버퍼크기 = %d\n", fp->_IO_buf_end - fp->_IO_buf_base);
    exit(0);
}