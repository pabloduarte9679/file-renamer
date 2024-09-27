#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
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
  char filename[] = {"config.txt"};
  DIR *dir;
  struct dirent **entry;
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

  int fd = open("config.txt", O_RDWR);
  if(fd == -1){
    printf("Error opening config file!\n");
    return 4;
  }
  char *pattern;
  char *string;
  char *num_string;
  pattern = readline(fd);
  string = readline(fd);

 
  char new_filename[200];
  int found = 0;
  // read files in directory to change filenames
  char *filelist[100];
  int file_n;
  int tmp = 0;
  int num;
  printf("Type the number to start counting: ");
  scanf("%d", &num);
  file_n = scandir(argv[1], &entry, NULL, alphasort);
  if(file_n == -1){
    perror("scandir");
    exit(EXIT_FAILURE);
  }
  while(tmp < file_n){
    if(entry[tmp]->d_type == DT_REG && strstr(entry[tmp]->d_name, pattern) != NULL){
      found = 1;
      sprintf(new_filename, string, num++, entry[tmp]->d_name);
      rename(entry[tmp]->d_name, new_filename);
    }
    free(entry[tmp++]);
  }

  // rename files


  if(found == 0){
    printf("Filename not found!\n");
    exit(5);
  }
  closedir(dir);
  close(fd);
  free(pattern);
  free(string);
}
