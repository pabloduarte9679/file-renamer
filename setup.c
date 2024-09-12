#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 100
int main(void){
  int fd;
  char buffer[BUF_SIZE];
  char filename[11] = {"config.txt"};
  if(access(filename, F_OK) != 0){
    // create file
    fd = open(filename, O_CREAT |  O_APPEND | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  }else{
    fd = open(filename, O_APPEND| O_RDWR);
  }
  lseek(fd, 0, SEEK_END);
  
  printf("Type the pattern to replace with printf format\n");
  fgets(buffer, BUF_SIZE, stdin);
  if(write(fd, buffer, strlen(buffer)) != strlen(buffer)){
    printf("Error writing to config file. Closing...");
    close(fd);
    exit(errno);
  }

  printf("Type the string to add to the filename\n");
  fgets(buffer, BUF_SIZE, stdin);
 
  if(write(fd, buffer, strlen(buffer)) != strlen(buffer)){
    printf("Error writing to config file. Closing...");
    close(fd);
    exit(errno);
  }

  printf("Type the number to put in the filename in case you specified a decimal in the replace string\n");
  fgets(buffer, BUF_SIZE, stdin);

  if(write(fd, buffer, strlen(buffer)) != strlen(buffer)){
    printf("Error writing to config file. Closing...");
    close(fd);
    exit(errno);
  }
  
  close(fd);
  

  return 0;
}
