#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/// testSignal 
// signo - 설정할 시그널 번호
// handler - 새로 설정할 시그널 핸들러 함수
// 반환값 - 이전에 설정된 시그널 핸들러 함수 포인터

void (*testSignal(int signo, void (*handler)(int)))(int) {
    // sigaction 구조체 
    struct sigaction act;
    struct sigaction old_act;

    // 새로 설정할 시그널 핸들러 지정 
    act.sa_handler = handler;
    // 시그널 마스크 초기화 
    sigemptyset(&act.sa_mask);
    // 추가 플래그 -> 사용 X 
    act.sa_flags = 0;

    // sigaction - 시그널 핸들러 설정 
    if (sigaction(signo, &act, &old_act) < 0) {
        perror("sigaction error");
        exit(1);
    }
    // 이전 핸들러 반환 
    return old_act.sa_handler;
}

// 알람 시그널을 처리하는 핸들러 
void alarmHandler(int signo) {
    printf("Wake up\n");
    exit(0);
}

int main() {
    testSignal(SIGALRM, alarmHandler);
    alarm(5);
    
    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }
    
    printf("end\n");
}
