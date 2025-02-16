#include "../janus.h"

void add(char *file) {
  FILE *index = fopen(INDEX_FILE, "a");
  if(!index) {
    perror("Failed to open index file");
    return;
  }
  fprintf(index, "%s\n", file);
  fclose(index);
  printf("Added '%s' to the staging area.\n", file);
}