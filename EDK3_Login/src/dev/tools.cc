#include "tools.h"

#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include "EDK3/scoped_array.h"

void ReadFile(const char* filename, EDK3::scoped_array<char>& output){
  FILE* in_file = 0;
  int err = fopen_s(&in_file, filename, "rb");
  assert(in_file);
  struct stat sb;
  assert(stat(filename, &sb) != -1);
  output.alloc(sb.st_size + 1);
  //char* file_contents = (char*)malloc(sb.st_size + 1);
  if (output.get()) {
    fread(output.get(), sb.st_size, 1, in_file);
    output.get()[sb.st_size] = 0;
    fclose(in_file);
  }
}