#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pid> <value>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    int value = atoi(argv[2]);

    // Create a sigval structure to pass the value
    union sigval sig_value;
    sig_value.sival_int = value;

    // Send the SIGINT signal with the value
    if (sigqueue(pid, SIGINT, sig_value) == -1) {
        perror("sigqueue failed");
        return 1;
    }

    printf("Sent SIGINT to process %d with value %d\n", pid, value);
    return 0;
}
