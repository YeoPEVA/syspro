#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
    char str[1024];
    char *command1 = NULL, *command2 = NULL;
    int fd[2];

    if (argc > 1) {
        // 명령어를 명령행 인수로부터 처리
        char *arg_str = strdup(argv[1]); // 명령어 문자열 복사
        if (strchr(arg_str, '|') != NULL) { // 파이프 체크 
            command1 = strtok(arg_str, "| ");
            command2 = strtok(NULL, "| ");
        } else {
            command1 = arg_str; // 파이프가 없다면 ->  단일 명령
        }
    } else {
        // 명령행 인수 x시 표준 입력 -> 처리
        printf("[shell] ");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0'; // 개행 제거
        if (strchr(str, '|') != NULL) { // 파이프 포함 여부 확인
            command1 = strtok(str, "| ");
            command2 = strtok(NULL, "| ");
        } else {
            command1 = str; // 파이프가 없다면 ->  단일 명령
        }
    }

    // 파이프가 필요한 경우 파이프 생성
    if (command2 != NULL && pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // 첫 번째 명령 실행
    if (fork() == 0) {
        if (command2 != NULL) {
            close(fd[READ]); // 읽기 끝 닫기
            dup2(fd[WRITE], STDOUT_FILENO); // 쓰기 파이프를 표준 출력으로 복제
            close(fd[WRITE]); // 쓰기 끝 닫기
        }
        execlp(command1, command1, NULL); // 첫 번째 명령 실행
        perror("execlp");
        exit(1);
    }

    // 두 번째 명령 실행
    if (command2 != NULL) {
        if (fork() == 0) {
            close(fd[WRITE]); // 쓰기 끝 닫기
            dup2(fd[READ], STDIN_FILENO); // 읽기 파이프를 표준 입력으로 복제
            close(fd[READ]); // 읽기 끝 닫기
            execlp(command2, command2, NULL); // 두 번째 명령 실행
            perror("execlp");
            exit(1);
        }
    }
    close(fd[READ]);
    close(fd[WRITE]);

    return 0;
}
