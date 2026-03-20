#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/my_fifo"
#define FILE_NAME "hello.txt"

int main() {
    pid_t pid;
    int fifo_fd, file_fd;
    char buffer[1024];
    ssize_t bytes_read;

    // Create FIFO (ignore error if already exists)
    mkfifo(FIFO_FILE, 0666);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    // ---------------- CLIENT (Child) ----------------
    if (pid == 0) {
        sleep(1);  // Ensure server opens FIFO first

        fifo_fd = open(FIFO_FILE, O_RDONLY);
        if (fifo_fd == -1) {
            perror("Client: Error opening FIFO");
            exit(EXIT_FAILURE);
        }

        printf("Client reading from FIFO:\n");

        while ((bytes_read = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        close(fifo_fd);
    }

    // ---------------- SERVER (Parent) ----------------
    else {
        file_fd = open(FILE_NAME, O_RDONLY);
        if (file_fd == -1) {
            perror("Server: Error opening file");
            exit(EXIT_FAILURE);
        }

        fifo_fd = open(FIFO_FILE, O_WRONLY);
        if (fifo_fd == -1) {
            perror("Server: Error opening FIFO");
            exit(EXIT_FAILURE);
        }

        printf("Server sending file contents...\n");

        while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) {
            write(fifo_fd, buffer, bytes_read);
        }

        close(file_fd);
        close(fifo_fd);
    }

    return 0;
}
