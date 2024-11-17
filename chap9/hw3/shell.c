#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void execute_command(char *cmd);

int main() {
    char input[MAX_INPUT];

    while (1) {
        printf("[shell] ");
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            break; // 종료 신호 처리
        }

        // 입력 끝의 개행 문자 제거
        input[strcspn(input, "\n")] = '\0';

        // 빈 입력 무시
        if (strlen(input) == 0) {
            continue;
        }

        // 명령어 분리 (명령어 간에 ';'로 구분)
        char *cmd;
        char *saveptr; // strtok_r용 안전한 포인터
        cmd = strtok_r(input, ";", &saveptr);

        while (cmd != NULL) {
            // 각 명령어 앞뒤 공백 제거
            while (*cmd == ' ') cmd++;
            char *end = cmd + strlen(cmd) - 1;
            while (end > cmd && *end == ' ') *end-- = '\0';

            // 명령어 실행
            if (strlen(cmd) > 0) {
                execute_command(cmd);
            }

            cmd = strtok_r(NULL, ";", &saveptr);
        }
    }

    return 0;
}

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    int background = 0; // 백그라운드 실행 여부
    int redirect_out = 0, redirect_in = 0; // 리디렉션 여부
    char *outfile = NULL, *infile = NULL;

    // 백그라운드 실행 여부 확인
    if (cmd[strlen(cmd) - 1] == '&') {
        background = 1;
        cmd[strlen(cmd) - 1] = '\0';
    }

    // 명령어를 공백으로 구분하여 분리
    char *token;
    char *saveptr;
    int arg_count = 0;

    token = strtok_r(cmd, " ", &saveptr);
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            // 출력 리디렉션
            redirect_out = 1;
            outfile = strtok_r(NULL, " ", &saveptr);
        } else if (strcmp(token, "<") == 0) {
            // 입력 리디렉션
            redirect_in = 1;
            infile = strtok_r(NULL, " ", &saveptr);
        } else {
            // 일반 명령어와 인자
            args[arg_count++] = token;
        }
        token = strtok_r(NULL, " ", &saveptr);
    }
    args[arg_count] = NULL; // 인자 리스트 끝

    // 자식 프로세스 생성 및 명령 실행
    pid_t pid = fork();

    if (pid == 0) { // 자식 프로세스
        // 출력 리디렉션 처리
        if (redirect_out && outfile) {
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("Failed to open output file");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        // 입력 리디렉션 처리
        if (redirect_in && infile) {
            int fd = open(infile, O_RDONLY);
            if (fd < 0) {
                perror("Failed to open input file");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        // 명령 실행
        execvp(args[0], args);
        // execvp 실패 시
        perror("Command execution failed");
        exit(1);
    } else if (pid > 0) { // 부모 프로세스
        if (!background) {
            // 백그라운드가 아니면 자식 프로세스 종료 대기
            waitpid(pid, NULL, 0);
        }
    } else {
        perror("Failed to fork");
    }
}
