#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Usage: file-rename <directory>\n");
    return 1;
  }
  
  DIR *dir;
  struct dirent *entry;
  dir = opendir(argv[1]);
  if(dir == NULL){
    printf("Error opening directory!\n");
    return 3;
  }
  // check for config file
  if(access("config.txt", F_OK) != 0){
    printf("config file not found, run setup first\n");
    return 2;
  }

  int fd = open("config.txt", O_RDONLY);
  if(fd == -1){
    printf("Error opening config file!\n");
    return 4;
  }
  char *pattern;
  char *string;
  char *num_string;
  int num;
  pattern = readline(fd);
  string = readline(fd);
  num_string = readline(fd);
  num = atoi(num_string);

  // read files in directory to change filenames
  while((entry = readdir(dir)) != NULL){
    if(entry->d_type == DT_REG){
      if(strstr(entry->d_name, pattern) != NULL){
        printf("Found\n"); 
      }else{
        printf("Filename not found!\n");
	//exit(5);
      }     
    }
  }

  free(num_string);
  closedir(dir);
  close(fd);
  free(pattern);
  free(string);
}
