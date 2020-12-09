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
char s[100];
char *ptr;



int main() {
  
    signal(SIGINT, sighandle);
    int a,b,c;
    bool Background;
    
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
  
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    
    while (true) {
        bool Background = false;
        do{ 
            // Print the shell prompt.
            printf("%s>", getcwd(s, 100));
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
			  
        arguments[0] = strtok(command_line, delimiters);
        // 1. Tokenize the command line input (split it on whitespace)

        a=0;
        while(arguments[a] != NULL){
          arguments[++a] = strtok(NULL,delimiters);
        }
          arguments[a] == NULL;
      
        // 2. Implement Built-In Commands
        if (strcmp(arguments[0],"cd") == 0){
          //$
          chdir(arguments[1]);
        } 
        else if (strcmp(arguments[0],"pwd") == 0){
          printf("%s\n", getcwd(s, 100)); 
        }
        else if (strcmp(arguments[0],"echo") == 0){
          //$
          c=1;
    
          while(arguments[c] != NULL){
            ptr = arguments[c];
            if(strchr(ptr,'$') != NULL){
              memmove(ptr, ptr+1, strlen(ptr));
              arguments[c] = getenv(ptr);
            }
            printf("%s ",arguments[c]);
            c++; 
          }
          printf("\n");
        }
        else if (strcmp(arguments[0],"exit") == 0){
          exit(0);
        }
        else if (strcmp(arguments[0],"env") == 0){
          if (arguments[1] == NULL){
            for (a = 0; environ[a] != NULL; a++){
                printf("\n%s", environ[a]);
             }
            printf("\n");
          } else {
              printf("%s\n",getenv(arguments[1]));
            
          }
        }
        else if(strcmp(arguments[0],"setenv") == 0){
            const char *str_arr[2];
            char *str = arguments[1];
            a=0;
            str_arr[a] = strtok(str, "=");
            while(str_arr[a] != NULL) {
              str_arr[++a] = strtok(NULL,"=");
            }
            setenv(str_arr[0],str_arr[1],1);
          
        }
        else{
          if (strcmp(arguments[a-1],"&") == 0){
           arguments[a-1] = NULL;
           Background = true;//flag
            
          }
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
            // 4. The parent process should wait for the child to complete unless its a background process
            if (Background  != true){
              wait(NULL);
            }
            
          }
        }     
        // 3. Create a child process which will execute the command line input

  
        
      
      
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

void sighandle(int signum){
  printf("caught signal %d,coming out...\n", signum);
  kill(pid,SIGKILL);
 
}
