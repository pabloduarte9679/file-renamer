#include <dirent.h>
#include <stdio.h>
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
    print("Usage: file-rename <directory>\n");
    return 1;
  }
  
  DIR *dir;
  struct dirent *entry;
  directory = opendir(argv[1]);
  // check for config file
  if(access("config.txt", F_OK) != 0){
    printf("config file not found, run setup first\n");
    return 2;
  }

  int fd = open("config.txt", O_RDONLY);
  char buffer[100];
  for(int i = 0; i < 3; i++){
    fgets(buffer, 100, fd)
  }
}
