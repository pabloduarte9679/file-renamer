#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *readline(int fd){
  char *buf = (char*)malloc(100);
  int i = 0;
  while(buf[i - 1] != '\n'){
    read(fd, &buf[i], 1);
    i++;
  }
  buf[i - 1] = '\0';
  return buf;
}

int main(int argc, char *argv[]){
 /* DIR *directory;
  struct dirent *entry;
  directory = opendir(".");
  if(directory == NULL){
    printf("Error opening directory\n");
    return 1;
  }
  while((entry = readdir(directory)) != NULL){
    if(entry->d_type == DT_REG){
      printf("File: %s\n", entry->d_name);
    }else if(entry->d_type == DT_DIR){
      printf("Dir: %s\n", entry->d_name);
    }
  }
  if(closedir(directory) == -1){
    printf("Error closing directory\n");
    return 1;
  }
  return 0;
  */
  if(argc != 2){
    printf("Usage: file-rename <directory>\n");
    return 1;
  }
  
  DIR *dir;
  struct dirent *entry;
  dir = opendir(argv[1]);
  // check for config file
  if(access("config.txt", F_OK) != 0){
    printf("config file not found, run setup first\n");
    return 2;
  }

  int fd = open("config.txt", O_RDONLY);
  char *pattern;
  char *string;
  char *num_string;
  int num;
  pattern = readline(fd);
  string = readline(fd);
  num_string = readline(fd);
  num = atoi(num_string);

  

  free(num_string);
  closedir(dir);
  close(fd);
  free(pattern);
  free(string);
}
