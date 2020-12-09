// https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
// https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/#:~:text=The%20chdir%20command%20is%20a,the%20directory%20specified%20in%20path.
// https://forgetcode.com/c/977-exit-terminate-the-program
// https://stackoverflow.com/questions/28502305/writing-a-simple-shell-in-c-using-fork-execvp
// https://danishpraka.sh/2018/01/15/write-a-shell.html
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

char prompt[] = " > ";
char delimiters[] = " \t\r\n";
extern char **environ;
void sighandle(int);
pid_t pid;
char character[100];
char *ptr;

int main() {
 
    signal(SIGINT, sighandle);
    bool Background;
   
    // Stores the string typed into the command line.
    int a,b,c;
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
 
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
   
    while (true) {
        bool Background = false;
        do{
            // Print the shell prompt.
            printf("%s>", getcwd(character, 100));
            fflush(stdout);

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

        arguments[0] = strtok(command_line, delimiters);

        a=0;
        while(arguments[a] != NULL){
          arguments[++a] = strtok(NULL,delimiters);
        }
          arguments[a] == NULL;
     
        if (strcmp(arguments[0],"cd") == 0){
          pid = fork();
          if (pid<0){
            perror("fork failed");
            exit(0);
          }
          else if(pid == 0){
            execvp(arguments[0], arguments);
            printf("execvp() failed: No such file or directory");
            exit(0);
          }
          else{
            if (Background  != true){
              wait(NULL);
            }
           
          }
        }    
    }
