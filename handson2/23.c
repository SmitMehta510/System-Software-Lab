/*
============================================================================
Name : 23.c
Author : Smit Mehta
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 11th oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

void main() {
    // Get the maximum number of files a process can open
    long max_open_files = sysconf(_SC_OPEN_MAX);
    if (max_open_files == -1) {
        perror("Error getting maximum number of open files");
    } else {
        printf("Maximum number of open files: %ld\n", max_open_files);
    }

    // Get the size of a pipe (circular buffer)
    long pipe_buf_size = fpathconf(1, _PC_PIPE_BUF);
    if (pipe_buf_size == -1) {
        perror("Error getting pipe buffer size");
    } else {
        printf("Size of a pipe (circular buffer): %ld\n", pipe_buf_size);
    }

}