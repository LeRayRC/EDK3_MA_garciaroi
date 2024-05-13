#include "tools.h"

#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>

char* ReadFile(const char* filename){
  FILE* in_file = 0;
  int err = fopen_s(&in_file, filename, "rb");
  assert(in_file);
  struct stat sb;
  assert(stat(filename, &sb) != -1);
  char* file_contents = (char*)malloc(sb.st_size + 1);
  if (file_contents) {
    fread(file_contents, sb.st_size, 1, in_file);
    file_contents[sb.st_size] = 0;
    fclose(in_file);
  }
  return file_contents;
}