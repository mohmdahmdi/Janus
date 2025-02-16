#include "../janus.h"

void init() {
  mkdir(VCS_DIR, 0777);
  mkdir(OBJECTS_DIR, 0777);
  FILE *index = fopen(INDEX_FILE, "w");
  FILE *head = fopen(HEAD_FILE, "w");
  FILE *logs = fopen(LOGS_FILE, "w");
  fclose(index);
  fclose(head);
  fclose(logs);
  printf("Initialized empty Janus repository in %s\n", VCS_DIR);
}