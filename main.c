#include <dirent.h>
#include <stdio.h>
// with git
int main(void){
  DIR *directory;
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
}
