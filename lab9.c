/* Author(s): Jorge Tadeo & Taylor Allen
 *
 * This is lab9.c the csc60mshell
 * This program serves as a skeleton for doing labs 9, 10, 11.
 * Student is required to use this program to build a mini shell
 * using the specification as documented in direction.
 * Date: Fall 2018
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAXLINE 80
#define MAXARGS 20
#define MAX_PATH_LENGTH 5000
#define TRUE 1

/* function prototypes */
int parseline(char *cmdline, char **argv);

//The two function prototypes below will be needed in lab10.
//Leave them here to be used later.
/* void process_input(int argc, char **argv); */
/* void handle_redir(int count, char *argv[]); */

/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */

int main(void){
  char cmdline[MAXLINE];
  char *argv[MAXARGS];
  char path[MAX_PATH_LENGTH];
  char dir[MAX_PATH_LENGTH];
  int argc;
  int status;
  pid_t pid;
  int loop;

  /* Loop forever to wait and process commands */
  do{
    /* Print your shell name: csc60mshell (m for mini shell) */
    printf("csc60mshell > ");

    /* Read the command line */
    fgets(cmdline, MAXLINE, stdin);

    /* Call parseline to build argc/argv */
    argc = parseline(cmdline, argv);

    /* Print out argc and argv list */
    for(loop = 0; loop < argc ; loop++)
      printf("Argc %i = %s\n",loop,argv[loop]);

    /* if user passes no args return shell prompt */
    if(argc == 0){
      continue;
    }

    /* Check for exit, pwd, or cd */
    if(strcmp(argv[0], "exit") ==  0){
      return EXIT_SUCCESS;
    } else if (strcmp(argv[0], "pwd") == 0){                   // if argv[0] equals pwd print the current working dir
      (getcwd(path, MAX_PATH_LENGTH)) ? printf("%s\n", path) : printf("Cannot Print The Current Working Directory.\n");
      continue;
    } else if (strcmp(argv[0], "cd") == 0 && argv[1] == NULL){ // if argv[0] equals cd without a second arg change dir to HOME
      chdir(getenv("HOME"));
      continue;
    } else if (strcmp(argv[0], "cd") == 0){                    // if cd has a second arg change dir to the path specified
      int dirErr = chdir(argv[1]);
      (dirErr < 0) ? perror("Error") : chdir(argv[1]);
      continue;

    /* If user hits enter key without a command, continue to loop */
    /* again at the beginning */
    /*  Hint: if argc is zero, no command declared */
    /*  Hint: look up for the keyword "continue" in C */

    /* Handle build-in command: exit, pwd, or cd  */
    /* Put the rest of your code here */

    //.......................IGNORE........................
    //	/* Else, fork off a process */
    //      else {
    //      pid = fork();
    //          switch(pid)
    //          {
    //        case -1:
    //        perror("Shell Program fork error");
    //              exit(EXIT_FAILURE);
    //      case 0:
    //        /* I am child process. I will execute the command, */
    //        /* and call: execvp */
    //        process_input(argc, argv);
    //        break;
    //      default:
    //        /* I am parent process */
    //        if (wait(&status) == -1)
    //          perror("Parent Process error");
    //        else
    //        printf("Child returned status: %d\n",status);
    //        break;
    //      }   /* end of the switch */
    //...end of the IGNORE above.........................
    }	/* end of the if-else-if */
  }	while (TRUE); /* end of the while */
}     /* end of main */

/* ----------------------------------------------------------------- */
/*                  parseline                                        */
/* ----------------------------------------------------------------- */
/* parse input line into argc/argv format */

int parseline(char *cmdline, char **argv){
  int count = 0;
  char *separator = " \n\t"; /* Includes space, Enter, Tab */

  /* strtok searches for the characters listed in separator */
  argv[count] = strtok(cmdline, separator);

  while ((argv[count] != NULL) && (count+1 < MAXARGS))
    argv[++count] = strtok((char *) 0, separator);

  return count;  //This becomes "argc" back in main.
}

/* ----------------------------------------------------------------- */
/*                  process_input                                    */
/* ----------------------------------------------------------------- */
/*void process_input(int argc, char **argv) {                       */

    /* Step 1: Call handle_redir to deal with operators:            */
    /* < , or  >, or both                                           */


    /* Step 2: perform system call execvp to execute command        */
    /* Hint: Please be sure to review execvp.c sample program       */
    /* if (........ == -1) {                                        */
    /*    fprintf(stderr, "Error on the exec call\n");              */
    /*    _exit(EXIT_FAILURE);                                      */
    /* }                                                            */

// }
/* ----------------------------------------------------------------- */
//void handle_redir(int count, char *argv[])
/* ----------------------------------------------------------------- */

/* ----------------------------------------------------------------- */
