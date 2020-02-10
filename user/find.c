#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void find(const char* path, const char* nextaddress, const char* filename, int a) {
  int fd;
  struct dirent de;
  struct stat st;

  char this_path[DIRSIZ + 1];
  strcpy(this_path, path);//copying the path

  if (a == 0) {
    int length = strlen(this_path);
    this_path[length] = '/';
    strcpy(this_path + length + 1, nextaddress);//appending the path and storing it in the variable this_path
  }

  if((fd = open(this_path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  if(st.type==T_DIR){
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0) 
	continue;
      if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0){ 
        
	continue;
      }
      find(this_path, de.name, filename, 0);//calling recursive function
    }

  }
    
  if(st.type==T_FILE){
    if (strcmp(filename, nextaddress) == 0) {
      printf("%s\n", this_path);
    }	
    
  }

  close(fd);
}

int main(int argc, char *argv[]){
  if(argc < 2){
    fprintf(2, "Format: find Path Filename\n");
    exit();
  }

  const char* path = argv[1];
  const char* filename = argv[2];

  find(path, "", filename, 1);

  exit();
}
