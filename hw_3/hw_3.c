#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int factorial(int n) {
    int res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }

    return res;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    printf("%d\n", n);

    int pid, ppid, chpid;
    chpid = fork();
    pid = getpid();
    ppid = getppid();

    if (chpid == -1) {
        printf("Incorrect fork syscall\n");
    } else if (chpid == 0) {
        printf("I am child. My pid = %d, my ppid = %d, child pid = %d, factorial: %d\n", pid, ppid, chpid, factorial(n));
    } else {
        printf("I am parent. My pid = %d, my ppid = %d, child pid = %d, fibonacci: %d\n", pid, ppid, chpid, fibonacci(n));
    }

    return 0;
}
