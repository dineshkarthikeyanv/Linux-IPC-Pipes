# Linux-IPC--Pipes
Linux-IPC-Pipes


# Ex03-Linux IPC - Pipes

# AIM:
To write a C program that illustrate communication between two process using unnamed and named pipes

# DESIGN STEPS:

### Step 1:

Navigate to any Linux environment installed on the system or installed inside a virtual environment like virtual box/vmware or online linux JSLinux (https://bellard.org/jslinux/vm.html?url=alpine-x86.cfg&mem=192) or docker.

### Step 2:

Write the C Program using Linux Process API - pipe(), fifo()

### Step 3:

Testing the C Program for the desired output. 

# PROGRAM:

## C Program that illustrate communication between two process using unnamed pipes using Linux API system calls
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

    // Create FIFO (ignore if already exists)
    mkfifo(FIFO_FILE, 0666);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    // ----------- CHILD PROCESS (CLIENT) -----------
    if (pid == 0) {
        fifo_fd = open(FIFO_FILE, O_RDONLY);
        if (fifo_fd == -1) {
            perror("Error opening FIFO (client)");
            exit(EXIT_FAILURE);
        }

        printf("Client reading from FIFO:\n");

        while ((bytes_read = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        close(fifo_fd);
    }

    // ----------- PARENT PROCESS (SERVER) -----------
    else {
        sleep(1); // ensure client is ready

        file_fd = open(FILE_NAME, O_RDONLY);
        if (file_fd == -1) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        fifo_fd = open(FIFO_FILE, O_WRONLY);
        if (fifo_fd == -1) {
            perror("Error opening FIFO (server)");
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



## OUTPUT

![Output 1](images/Screenshot%20at%202026-03-20%2010-58-47.png)

## C Program that illustrate communication between two process using named pipes using Linux API system calls
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

    // Create FIFO (ignore if already exists)
    mkfifo(FIFO_FILE, 0666);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    // ----------- CHILD PROCESS (CLIENT) -----------
    if (pid == 0) {
        fifo_fd = open(FIFO_FILE, O_RDONLY);
        if (fifo_fd == -1) {
            perror("Error opening FIFO (client)");
            exit(EXIT_FAILURE);
        }

        printf("Client reading from FIFO:\n");

        while ((bytes_read = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        close(fifo_fd);
    }

    // ----------- PARENT PROCESS (SERVER) -----------
    else {
        sleep(1); // ensure client is ready

        file_fd = open(FILE_NAME, O_RDONLY);
        if (file_fd == -1) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        fifo_fd = open(FIFO_FILE, O_WRONLY);
        if (fifo_fd == -1) {
            perror("Error opening FIFO (server)");
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


### Output
![Output 2](images/Screenshot%20at%202026-03-20%2011-10-32.png)

# RESULT:
The program is executed successfully.
