#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *readline(int fd){
  char *buf = (char*)malloc(100);
  if(buf == NULL){
    printf("Error allocating memory for buffer!\n");
    return NULL;
  }
  int i = 0;
  while(buf[i - 1] != '\n'){
    read(fd, &buf[i], 1);
    i++;
  }
  buf[i - 1] = '\0';
  return buf;
}

int main(void){
  int max = 67;
  int fd = open("files.txt", O_RDONLY);
  for(int i = 0; i < max; i++){
    char *buffer = readline(fd);
    int nfd = open(buffer, O_RDONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH);
    close(nfd);
    free(buffer);
  }
  return 0;
}
