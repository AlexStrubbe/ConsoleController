#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * @brief Main function for the terminal command selector.
 *
 * This program presents a menu of options to the user, allowing them to
 * execute various system commands such as `ls`, `cp`, `mv`, `ifconfig`,
 * `make`, `cat`, or to run a custom executable program. The user can select
 * multiple options separated by spaces. For each selected option, the program
 * forks a new process to execute the corresponding command.
 *
 * @return int Exit status of the program. Returns 0 on successful completion.
 */
int main() {
  int buffer[BUFFER_SIZE];  ///< Buffer to store user-selected options.
  char file[BUFFER_SIZE];  ///< Buffer to store file paths provided by the user.
  char destination[BUFFER_SIZE];  ///< Buffer to store destination paths
                                  ///< provided by the user.
  int i = 0;                      ///< Loop counter.
  int size = 0;  ///< Number of valid options entered by the user.
  int num;       ///< Variable to hold user input.

  printf(
      "Welcome to the terminal, please select an option from below (you can "
      "choose multiple if you input the desired selection separated by a "
      "space and press ctrl+D to stop):\n1) "
      "ls\n2) cp\n3) mv\n4) ifconfig\n5) make\n6) cat\n7) execute a "
      "program\n");

  // Read user input until EOF or buffer is full
  while (size < BUFFER_SIZE && scanf("%d", &num) == 1) {
    buffer[size] = num;
    size++;
  }

  // Handle end-of-file (EOF) or input error
  if (feof(stdin)) {
    clearerr(stdin);  ///< Clear the EOF flag
  } else if (ferror(stdin)) {
    perror("Input error");
    exit(EXIT_FAILURE);
  }

  // Process each user-selected option
  for (i = 0; i < size; i++) {
    switch (buffer[i]) {
      case 1:
        printf("You have selected ls \n");

        // Fork a new process to execute `ls`
        if (fork() == 0) {
          char* argument_list[] = {"ls", "-l", NULL};
          int status_code = execvp("ls", argument_list);
          if (status_code == -1) {
            printf("Process did not terminate correctly\n");
            exit(1);
          }
        }
        break;
      case 2:
        printf(
            "\nYou have selected cp, please indicate the path of the file you "
            "wish to copy: \n");
        scanf("%s", file);
        printf("Now, please write the path of the destination: \n");
        scanf("%s", destination);

        // Fork a new process to execute `cp`
        if (fork() == 0) {
          char* argument_list[] = {"cp", file, destination, NULL};
          int status_code = execvp("cp", argument_list);
          if (status_code == -1) {
            printf("Process did not terminate correctly\n");
            exit(1);
          }
        }
        break;
      case 3:
        printf(
            "\nPlease choose a file path for which you wish to change name or "
            "move: ");
        scanf("%s", file);
        printf("Now, please write the path of the destination: \n");
        scanf("%s", destination);

        // Fork a new process to execute `mv`
        if (fork() == 0) {
          char* argument_list[] = {"mv", file, destination, NULL};
          int status_code = execvp("mv", argument_list);
          if (status_code == -1) {
            printf("Process did not terminate correctly\n");
            exit(1);
          }
        }
        break;
      case 4:
        printf("\nYou have selected ifconfig \n");

        // Fork a new process to execute `ifconfig`
        if (fork() == 0) {
          char* argument_list[] = {"ifconfig", NULL};
          int status_code = execvp("ifconfig", argument_list);
          if (status_code == -1) {
            printf("Process did not terminate correctly\n");
            exit(1);
          }
        }
        break;
      case 5:
        printf("\nYou have selected make \n");

        // Fork a new process to execute `make`
        if (fork() == 0) {
          char* argument_list[] = {"make", NULL};
          int status_code = execvp("make", argument_list);
          if (status_code == -1) {
            printf("Process did not terminate correctly\n");
            exit(1);
          }
        }
        break;
      case 6:
        printf(
            "\nYou have selected cat, please indicate the path of the file you "
            "wish to read: \n");
        scanf("%s", file);

        // Fork a new process to execute `cat`
        if (fork() == 0) {
          char* argument_list[] = {"cat", file, NULL};
          int status_code = execvp("cat", argument_list);
          if (status_code == -1) {
            printf("Process did not terminate correctly\n");
            exit(1);
          }
        }
        break;
      case 7:
        printf(
            "\nYou have selected to execute a file, please indicate the path "
            "of the file you wish to execute: \n");
        scanf("%s", file);

        // Fork a new process to execute a user-specified file
        if (fork() == 0) {
          char* argument_list[] = {file, NULL};
          int status_code = execvp(file, argument_list);
          if (status_code == -1) {
            printf("Process did not terminate correctly\n");
            exit(1);
          }
        }
        break;
    }
    // Parent process waits for each child process to finish
    int status;
    wait(&status);
  }
  return 0;
}
