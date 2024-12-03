#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2]; 
    pid_t pid;
    char buffer[100];
    char message[] = "Hello from PID";

    // 파이프 생성
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    // 프로세스 분기
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 자식 프로세스
        close(pipe_fd[1]); // 쓰기 끝 닫기
        read(pipe_fd[0], buffer, sizeof(buffer)); // 부모 - 메시지 읽기
        close(pipe_fd[0]); // 읽기 끝 닫기
        printf("Recv: [%d] %s\n", getpid(), buffer);
    } else {
        // 부모 프로세스
        close(pipe_fd[0]); // 읽기 끝 닫기
        char full_message[100];
        sprintf(full_message, "%s %d", message, getpid());
        write(pipe_fd[1], full_message, strlen(full_message) + 1); // 자식 - 메시지 전송
        close(pipe_fd[1]); // 쓰기 끝 닫기
        printf("Send: [%d] %s\n", getpid(), full_message);
    }

    return 0;
}
