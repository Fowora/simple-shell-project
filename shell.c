#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128



int main() {
    char prompt[] = "> Ciara & Emmanuel";
    char delimiters[] = " \t\r\n";
    extern char **environ;
    int counter = 0;
    char *getcwd(char *buf, size_t size);
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
    char cwd[MAX_COMMAND_LINE_LEN];
    int pid;
    int status;
    char *split;
  
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    	
    while (true) {
      
        do{ 
            // Print the shell prompt.
            getcwd(cwd, sizeof(cwd));
            printf("%s", prompt);
            fflush(stdout);

            // Read input from stdin and store it in command_line. If there's an
            // error, exit immediately. (If you want to learn more about this line,
            // you can Google "man fgets")
        
            if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
                fprintf(stderr, "fgets error");
                exit(0);
            }
 
        }while(command_line[0] == 0x0A);  // while just ENTER pressed

      
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // TODO:
        // 
        
			  // 0. Modify the prompt to print the current working directory
			  
			
        // 1. Tokenize the command line input (split it on whitespace)
        int x = 0;
        split = strtok(command_line, delimiters);
        while (split != NULL){
          arguments[x] = split;
          x++;
          split = strtok(NULL, delimiters);
        }
      
        // 2. Implement Built-In Commands
        // cd - change directory
        char y[100];
        printf("%s\n", getcwd(y, 100));
        chdir("..");
        printf("%s\n", getcwd(y, 100));
        return 0;
      
        // pwd - print directory
        if (getcwd(cwd, sizeof(cwd)) != NULL){
          printf("%s\n", cwd);
        } else {
          return 0;
        }        
        // echo - print message and values
        int z = 0;
        int input;
        while (z != EOF){
          printf("\n Input: ");
          z = getchar();
          input = getchar();
          putchar(z);
        }
        // exit - exit
        exit(0);
        // setenv - set env variable
        char path[100]= "PATH=";
        char *charInput = "Hello";
        putenv(strcat(path, charInput));
        char* pPath;
        pPath = getenv("PATH");
        printf("%s", pPath);
        return 0;

        // env - print current values of env
        printf("%s", pPath);
    
        // 3. Create a child process which will execute the command line input
        pid = fork();
        if (pid == 0){
          execve(arguments[0], arguments, environ);
        }
              // 4. The parent process should wait for the child to complete unless its a background process

        else if (pid > 0){
          wait(&status);
        }      
      
        // Hints (put these into Google):
        // man fork
        // man execvp
        // man wait
        // man strtok
        // man environ
        // man signals
        
        // Extra Credit
        // man dup2
        // man open
        // man pipes
    }
    // This should never be reached.
    return -1;
}

