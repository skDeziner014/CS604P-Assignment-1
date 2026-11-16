#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int pipe1[2], pipe2[2];
    pid_t pid;

    char message[] = "How are you? What's your VUID?";
    char reply[100];
    char receivedMessage[100];

    char vuid[] = "BC240420011";

    if (pipe(pipe1) == -1) {
        perror("First pipe creation failed");
        return 1;
    }

    if (pipe(pipe2) == -1) {
        perror("Second pipe creation failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        /* Child Process */
        close(pipe1[1]);
        close(pipe2[0]);

        if (read(pipe1[0], receivedMessage, sizeof(receivedMessage) - 1) <= 0) {
            perror("Child read failed");
            exit(1);
        }
        receivedMessage[sizeof(receivedMessage) - 1] = '\0';

        printf("Child received: %s\n", receivedMessage);
        fflush(stdout);

        snprintf(reply, sizeof(reply), "I am fine. My VUID is %s", vuid);

        if (write(pipe2[1], reply, strlen(reply) + 1) != (ssize_t)(strlen(reply) + 1)) {
            perror("Child write failed");
            exit(1);
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    } else {
        /* Parent Process */
        close(pipe1[0]);
        close(pipe2[1]);

        if (write(pipe1[1], message, strlen(message) + 1) != (ssize_t)(strlen(message) + 1)) {
            perror("Parent write failed");
            return 1;
        }
        close(pipe1[1]);

        if (read(pipe2[0], reply, sizeof(reply)) <= 0) {
            perror("Parent read failed");
            close(pipe2[0]);
            wait(NULL);
            return 1;
        }

        printf("Parent received: %s\n", reply);

        close(pipe2[0]);
        wait(NULL);
    }

    return 0;
}
