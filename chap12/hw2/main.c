#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int pipe1[2], pipe2[2]; 
    // 두 개의 파이프 생성 
    // (부모- 첫 번째 자식, 첫 번째 자식-두 번째 자식)

    pid_t pid1, pid2;

    // 파이프 생성
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        return 1;
    }

    // 첫 번째 자식 프로세스 생성
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
        // 첫 번째 자식 프로세스
        close(pipe1[0]); // pipe1 읽기 끝 닫기
        close(pipe2[0]); // pipe2 읽기 끝 닫기
        close(pipe2[1]); // pipe2 쓰기 끝 닫기

        char input[100];
        printf("input string: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // 개행 문자 제거

        write(pipe1[1], input, strlen(input) + 1); // 입력 문자열을 부모로 전송
        close(pipe1[1]); // pipe1 쓰기 끝 닫기
        return 0;
    }

    // 두 번째 자식 프로세스 생성
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {
        // 두 번째 자식 프로세스
        close(pipe1[0]); // pipe1 읽기 끝 닫기
        close(pipe1[1]); // pipe1 쓰기 끝 닫기
        close(pipe2[1]); // pipe2 쓰기 끝 닫기

        char received[100];
        read(pipe2[0], received, sizeof(received)); // 첫 번째 자식 프로세스에서 데이터 읽기
        close(pipe2[0]); // pipe2 읽기 끝 닫기

        to_uppercase(received); // 문자열 -> 대문자 
        printf("%s\n", received);
        return 0;
    }

    // 부모 프로세스
    close(pipe1[1]); // pipe1 쓰기 끝 닫기
    close(pipe2[0]); // pipe2 읽기 끝 닫기

    char buffer[100];
    read(pipe1[0], buffer, sizeof(buffer)); // 첫 번째 자식 프로세스에서 데이터 읽기
    close(pipe1[0]); // pipe1 읽기 끝 닫기

    write(pipe2[1], buffer, strlen(buffer) + 1); // 데이터를 두 번째 자식 프로세스로 전달
    close(pipe2[1]); // pipe2 쓰기 끝 닫기
    
    return 0;
}
