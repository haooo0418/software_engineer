/*
 * Simple string parser for AFL++ fuzzing demonstration
 * This program intentionally has some potential vulnerabilities for fuzzing to find
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

// Function to parse a simple command format: "CMD:arg1,arg2"
int parse_command(char *input) {
    if (input == NULL || strlen(input) == 0) {
        return -1;
    }
    
    // Find the colon separator
    char *colon = strchr(input, ':');
    if (colon == NULL) {
        return -1;
    }
    
    // Extract command part
    int cmd_len = colon - input;
    if (cmd_len <= 0 || cmd_len > 100) {
        return -1;
    }
    
    char command[101];
    strncpy(command, input, cmd_len);
    command[cmd_len] = '\0';
    
    // Extract arguments part
    char *args = colon + 1;
    
    // Process different commands
    if (strcmp(command, "ADD") == 0) {
        // Parse two numbers separated by comma
        char *comma = strchr(args, ',');
        if (comma == NULL) {
            return -1;
        }
        
        int num1 = atoi(args);
        int num2 = atoi(comma + 1);
        
        return num1 + num2;
    } else if (strcmp(command, "REPEAT") == 0) {
        // Repeat a string N times
        char *comma = strchr(args, ',');
        if (comma == NULL) {
            return -1;
        }
        
        int count = atoi(args);
        char *text = comma + 1;
        
        // Potential buffer overflow if count is too large
        if (count > 0 && count < 100) {
            for (int i = 0; i < count; i++) {
                printf("%s", text);
            }
            printf("\n");
        }
        return 0;
    } else if (strcmp(command, "CALC") == 0) {
        // Simple calculator: CALC:10/5 or CALC:10*5
        char op = '\0';
        int num1 = 0, num2 = 0;
        
        // Find operator
        for (int i = 0; args[i] != '\0'; i++) {
            if (args[i] == '+' || args[i] == '-' || args[i] == '*' || args[i] == '/') {
                op = args[i];
                args[i] = '\0';
                num1 = atoi(args);
                num2 = atoi(args + i + 1);
                break;
            }
        }
        
        switch (op) {
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/': 
                // Potential division by zero
                if (num2 == 0) {
                    fprintf(stderr, "Division by zero!\n");
                    return -1;
                }
                return num1 / num2;
            default:
                return -1;
        }
    }
    
    return -1;
}

// Function with potential buffer overflow
void process_buffer(char *input) {
    char buffer[64];
    
    // Check for special marker
    if (strncmp(input, "MAGIC:", 6) == 0) {
        // Potential buffer overflow here
        strcpy(buffer, input + 6);
        printf("Magic command: %s\n", buffer);
    }
}

int main(int argc, char **argv) {
    char input[MAX_INPUT_SIZE];
    
    // Read input from stdin or file
    if (argc > 1) {
        // Read from file
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "Cannot open file: %s\n", argv[1]);
            return 1;
        }
        
        size_t len = fread(input, 1, MAX_INPUT_SIZE - 1, fp);
        input[len] = '\0';
        fclose(fp);
    } else {
        // Read from stdin
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            return 1;
        }
    }
    
    // Remove newline
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    // Process the input
    process_buffer(input);
    
    int result = parse_command(input);
    if (result >= 0) {
        printf("Result: %d\n", result);
    } else {
        printf("Invalid command\n");
    }
    
    return 0;
}
