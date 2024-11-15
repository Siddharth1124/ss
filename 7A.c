#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PIPE1 "/tmp/pipe1"
#define PIPE2 "/tmp/pipe2"
#define BUFFER_SIZE 1024
#define OUTPUT_FILE "output.txt"

// Function to count characters, words, and lines
void count_chars_words_lines(char *text, int *chars, int *words, int *lines) {
    *chars = *words = *lines = 0;
    int in_word = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        (*chars)++;
        if (text[i] == '\n') (*lines)++;
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            (*words)++;
        }
    }
}

// Process 1: Send sentence to Process 2, receive result and display it
void process1() {
    char input[BUFFER_SIZE], result[BUFFER_SIZE];

    printf("Enter a sentence: ");
    fgets(input, BUFFER_SIZE, stdin);

    int fd1 = open(PIPE1, O_WRONLY);
    write(fd1, input, strlen(input) + 1);
    close(fd1);

    int fd2 = open(PIPE2, O_RDONLY);
    read(fd2, result, BUFFER_SIZE);
    printf("Result from Process 2:\n%s", result);
    close(fd2);
}

// Process 2: Receive text, process it, write results to file, send back to Process 1
void process2() {
    char input[BUFFER_SIZE], result[BUFFER_SIZE];
    int chars, words, lines;

    int fd1 = open(PIPE1, O_RDONLY);
    read(fd1, input, BUFFER_SIZE);
    close(fd1);

    count_chars_words_lines(input, &chars, &words, &lines);

    FILE *file = fopen(OUTPUT_FILE, "w");
    fprintf(file, "Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
    fclose(file);

    file = fopen(OUTPUT_FILE, "r");
    fread(result, sizeof(char), BUFFER_SIZE, file);
    fclose(file);

    int fd2 = open(PIPE2, O_WRONLY);
    write(fd2, result, strlen(result) + 1);
    close(fd2);
}

int main() {
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

    pid_t pid = fork();

    if (pid > 0) {
        process1();
    } else if (pid == 0) {
        process2();
    } else {
        perror("Fork failed");
        exit(1);
    }

    unlink(PIPE1);
    unlink(PIPE2);
    remove(OUTPUT_FILE);

    return 0;
}
