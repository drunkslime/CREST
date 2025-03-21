#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../include/utils.h"

char* read_user_file(const char* filename) {
  // char *absolute_path = realpath(filename, NULL);

  // if (!absolute_path) {
  //   perror("Error resolving path");
  //   return NULL;
  // }

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
      fprintf(stderr, "Failed to open file: %s\n", filename);
      return NULL;
  }
  
  // set pointer position to the end of file to calculate its size
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);

  fseek(file, 0, SEEK_SET);
  
  // Allocate memory for the file content
  char* buffer = (char*)malloc(file_size + 1);
  if (buffer == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      fclose(file);
      return NULL;
  }
  
  // Read the file content
  size_t read_size = fread(buffer, 1, file_size, file);
  buffer[read_size] = '\0';  // Null-terminate the string
  
  fclose(file);
  return buffer;
}