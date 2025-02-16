#include "../janus.h"

void commit(const char *message){
  char commit_hash[33];
  snprintf(commit_hash, 33, "%ld", time(NULL));

  char commit_path[100];
  smprintf(commit_path, sizeof(commit_path), "%s/ %s", OBJECTS_DIR, commit_hash);
  FILE *commit_file = fopen(commit_path, "w");
  if (!commit_path){
    perror("Failed to create commit object");
    return;
  }

  FILE *index = fopen(INDEX_FILE, "r");
  if (!index){
    perror("Failed to open index file");
    return;
  }

  while (fgets(file_path, sizeof(file_path), index)) {
    file_path[strcspn(file_path, "\n")] = 0;
    FILE *src = fopen(file_path, "r");
    if (!src) {
      perror("Failed to open file");
      continue;
    }
    fprintf(commit_file, "%s\n", file_path);
    char ch;
    while ((ch = fgetc(src)) != EOF) {
      fputc(ch, commit_file);
    }
    fclose(src);
  }
  fclose(index);
  fclose(commit_file);
      
  FILE *head = fopen(HEAD_FILE, "w");
  fprintf(head, "%s", commit_hash);
  fclose(head);

  FILE *logs = fopen(LOGS_FILE, "a");
  fprintf(logs, "Commit: %s\nMessage: %s\n\n", commit_hash, message);
  fclose(logs);

  printf("Committed changes with hash: %s\n", commit_hash);
}