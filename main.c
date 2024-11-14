#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdatomic.h>

// Shared memory (global)
volatile atomic_int *shared_mem;

void read_process(int id, int seconds) {
    long long counter = 0;
    time_t start_time = time(NULL);

    while (time(NULL) - start_time < seconds) {
        counter++;
        double result = sqrt((double)counter); // Compute square root
        (void)result; // Suppress unused variable warning
    }

    printf("Process %d: Counter = %lld\n", id, counter);
    exit(0); // Terminate the child process
}

void write_process(int id, int seconds) {
    long long counter = 0;
    time_t start_time = time(NULL);

    while (time(NULL) - start_time < seconds) {
        counter++;
        double result = sqrt((double)counter); // Compute square root
        (void)result; // Suppress unused variable warning
    }

    printf("Process %d: Counter = %lld\n", id, counter);
    exit(0); // Terminate the child process
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_processes> <seconds>\n", argv[0]);
        return 1;
    }

    int num_processes = atoi(argv[1]);
    int seconds = atoi(argv[2]);

    if (num_processes <= 0 || seconds <= 0) {
        fprintf(stderr, "Both number_of_processes and seconds must be positive integers.\n");
        return 1;
    }

    pid_t pid;
    for (int i = 0; i < num_processes; i++) {
        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid == 0) {
            // Child process
            read_process(i + 1, seconds);
        }
        // Parent process continues the loop to create more child processes
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    printf("All processes completed.\n");
    return 0;
}
