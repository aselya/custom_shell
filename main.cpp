//
//  main.cpp
//  os_selya_project_shell
//
//  Created by Aaron David Selya on 11/15/17.
//  Copyright © 2017 Aaron David Selya. All rights reserved.
//
//
//
//
//Sources:
//Pseudocode for a shell provided by Prof. Nourai in the assignmnet
//int main (int argc, char **argv) {
//while (1) {
//    printPrompt();
//    cmdLine = readCommandLine();
//    cmd = parseCommand(cmdLine);
//    executeCommand(cmd); /* command is either internal or external */
//}}
//
//Several of the concepts utilized were detailed in the following tutorial provied by Prof Nourai in the assignment
//https://brennan.io/2015/01/16/write-a-shell-in-c/
//This program was created in C++ instead of C to demonstrate my understanding of the concepts detailed in the tutorial
//to avoid any directly copied code from the tutorial.

/////////////////////////////////////////////////////

//libraries utilized
#include < iostream > #include < string.h > #include < stdlib.h > #include < unistd.h > #include < stdio.h > #include < sys / wait.h > #include < ctime > #include < string.h >
  //structure of the nodes that comprise the linked list needed for the history command
  struct Node {
    Node * next;
    std::string data;

  };

//method that inserts the newest command at the end of the linked list
//method returns the head node
Node * Insert(Node * head, std::string data) {
  printf("insert was called"); //string used in debugging
  Node * curr = new Node; // creates new node
  curr - > data = data; //puts the data into the string
  //curr->next = NULL; //sets the value of the next to null placing new node at end of the list

  if (head == NULL) { //if there is no head
    head = curr; //set head to new node
    printf("the head data is %s \n", head - > data.c_str());

  } else {
    curr - > next = head; //makes the next value connected to curr the current head
    head = curr; //sets curr to be the head

    printf("the head data is %s \n", head - > data.c_str());
  }

  return head;
}

//method that prints the linked list structure
//returns head
Node * printLinkedList(Node * head) {
  Node * temp = head; //sets pointer to head
  if (temp == NULL) { //catches no list exception
    printf("The history is empty\n");
  } else {

    static int count = 0; //sets count for printer output
    if (temp - > next == NULL) { //handeles one entry list exception
      printf("command 0 %s\n", head - > data.c_str());
    } else {
      while (temp - > next) { // while temp has next print it and the command number
        //printf("command %i : %s\n", count, temp->data.c_str());
        printf("command used: %s\n", temp - > data.c_str());

        count++; //increase count
        temp = temp - > next; //set next count variable

        if (temp - > next == NULL) { //checkts to see if this is the last node
          printf("command used: %s\n", temp - > data.c_str()); //if last, prints the data in node
        }
      }

    }
  }
  return head;
} // return head

//this method prints the prompt shown for the shell;
//if you want to change it just adjust the string

void printThePrompt() {
  printf("AS>");
}

void read_command(char cmd[], char * par[]) {

  char line[1024]; //set variable for containing char array LINE since I don't care about memory it is larger than needed
  static int count = 0; //initializes count
  int i = 0; //initializes int
  char * array[100], * pch;

  for (;;) {
    int c = fgetc(stdin); //gets input from console
    line[count++] = (char) c; //puts each char from console into line array using for loop
    if (c == '\n') { // breaks at new line
      break;
    }

  }
  if (count == 1) {
    return;
  }
  pch = strtok(line, " \n"); //converts string

  while (pch != NULL) {
    array[i++] = strdup(pch);
    pch = strtok(NULL, " \n");
  }

  strcpy(cmd, array[0]);

  for (int j = 0; j < i; j++) {
    par[j] = array[j];

  }
  par[i] = NULL;

}

//main loop
//calls print the prompt
//reads commands
//forks if nessecary
//evaluates built in commands
int main() {
  printf("Starting shell\n");

  char cmd[100], command[100], * parameters[20];

  char * envp[] = {
    (char * )
    "PATH=/bin",
    0
  };
  char
  const * find = "!"; //
  Node * head = NULL;
  int status = 1;
  while (status < 3) {
    printThePrompt();

    read_command(command, parameters);

    if (strcmp(command, "!!") == 0) { //determines if the user wants most recent command
      std::string temp = head - > data; // takes data from head and puts it in command[]
      printf("most recent command called"); //feedback for debugging
      strcpy(command, temp.c_str());
    } // puts head data value in command

    //since the previous if statment will change any command matching !! to the most recent command
    //to ientify the !n (where n is a number) command we only need to look at the first char of the char[]
    find = "!"; //sets value of find
    if (command[0] == * find) { //
      printf("command recall initiated!");
      int numberToFind = command[1]; //gets the values stored in char array and converts them to in
      printf("the number to find is %d", numberToFind);

      //convert remaining part of command to int
      //seach llinked list
      //return
      Node * start = head;

      strcpy(command, "error"); //sets value of command to error
      //following code will change value to appropriate call or it will remain as a error
      if (start == NULL) {
        printf("command not found");

      }

      int counter = 0; //counter starts at 0
      while (start - > next) {
        if (counter == numberToFind) {
          std::string temp = start - > data; // takes data from start node and puts it in command[]
          printf("prev command recall called"); //feedback for debugging
          strcpy(command, temp.c_str());
          start = start - > next;
          counter++;
        }
        start = start - > next;
        counter++;

      }

      //if not found command is "error"

    }

    //built in commands are placed here
    if (strcmp(command, "exit") == 0) {
      printf("exit function called- failure\n");
      status = 3;
      break;
    } else if (strcmp(command, "help") == 0) {
      printf("built in command\n");
      printf("Welcome to Aaron Selya's Custom Shell!\nThis shell has the following built in commands\nhelp\nexit\ncd\ndate\n\nI hope you enjoy using the shell. If you have any questions or bugs to report email me at aselya@bu.edu");

    } else if (strcmp(command, "date") == 0) {
      printf("built in command\n");
      head = Insert(head, command);

      time_t currentTime = time(0);
      struct tm * now = localtime( & currentTime);
      std::cout << (now - > tm_year + 1900) << '-' <<
        (now - > tm_mon + 1) << '-' <<
        (now - > tm_mday) <<
        std::endl;

    } else if (strcmp(command, "cd") == 0) {
      printf("built in command\n");
      head = Insert(head, command);
      printf("the parameters for cd are: %c", parameters);
      // printf("%d\n", chdir(parameters[]));
    } else if (strcmp(command, "cd3") == 0) {
      head = Insert(head, command);

      if (parameters[1] == NULL) {
        printf("2nd argument required");
      } else {
        if (chdir(parameters[1]) != 0) {
          printf("error");
        }

      }

    } else if (strcmp(command, "") == 0) { //in the event there is an issue with the command initating a prompt
      printf("\n");
    } //this built in command will clear the line and reinitate the main loop
    //when user enters empty string
    else if (strcmp(command, "\n") == 0) { //in the event there is an issue with the command initating a prompt
      printf("\n");
    } else if (strcmp(command, "cd2") == 0) {
      printf("built in command\n");

      head = Insert(head, command);
      const char * target = "/temp";
      char directory[1024];

      getcwd(directory, sizeof(directory));
      printf("In %s\n", directory);

      if (chdir(target) == 0) {
        getcwd(directory, sizeof(directory));
        printf("In %s\n", directory);
      }

    } else if (strcmp(command, "history") == 0) {
      printf("built in command\n");

      //head = Insert( head, command);
      //printf("history called\n");
      printLinkedList(head);
    } else if (strcmp(command, "error") == 0) {
      printf("built in command\n");

      //head = Insert( head, command);
      printf("error occured, invalid command\n");
      //printLinkedList(head);

    } else {
      printf("external command\n");
      head = Insert(head, command);

      int pid = fork();
      if (pid != 0) {
        wait(NULL);
      } else {

        strcpy(cmd, "/bin/"); //since the os commands are stored within /bin/ this puts them in right location
        strcat(cmd, command); //combines string command wi

        printf(" child process %s\n", command);

        execve(cmd, parameters, envp);
      } //execute command

    }
  }

  return status;

}
