#include "../janus.h"

void status() {
  if (access(VCS_DIR, F_OK) == -1){
    printf("Not a VCS repository (or any of the parent directories).\n");
    return;
  }

  FILE *index = fopen(INDEX_FILE, "r");
  if (!index) {
    perror("Failed to oppen index file");
    return;
  }

  char staged_files[100][256];
  int staged_count = 0;
  char file_path[256];
  while (fgets(file_path, sizeof(file_path), index)) {
      file_path[strcspn(file_path, "\n")] = 0;
      strcpy(staged_files[staged_count++], file_path);
  }
  fclose(index);

  DIR *dir;
  struct dirent *entry;
  dir = opendir(".");
  if (!dir) {
      perror("Failed to open directory");
      return;
  }

  char untracked_files[100][256];
  int untracked_count = 0;
  char modified_files[100][256];
  int modified_count = 0;

  while ((entry = readdir(dir)) != NULL) {
      if (entry->d_type == DT_REG) {
          char *filename = entry->d_name;
          int is_tracked = 0;

          for (int i = 0; i < staged_count; i++) {
              if (strcmp(staged_files[i], filename) == 0) {
                  is_tracked = 1;
                  break;
              }
          }

          if (is_tracked) {
              struct stat file_stat;
              stat(filename, &file_stat);
              FILE *last_commit = fopen(HEAD_FILE, "r");
              if (last_commit) {
                  char commit_hash[33];
                  fscanf(last_commit, "%s", commit_hash);
                  fclose(last_commit);

                  char commit_path[100];
                  snprintf(commit_path, sizeof(commit_path), "%s/%s", OBJECTS_DIR, commit_hash);
                  FILE *commit_file = fopen(commit_path, "r");
                  if (commit_file) {
                      char line[256];
                      int found = 0;
                      while (fgets(line, sizeof(line), commit_file)) {
                          line[strcspn(line, "\n")] = 0;
                          if (strcmp(line, filename) == 0) {
                              found = 1;
                              break;
                          }
                      }
                      fclose(commit_file);

                      if (found) {
                          struct stat commit_stat;
                          stat(commit_path, &commit_stat);
                          if (file_stat.st_mtime > commit_stat.st_mtime) {
                              strcpy(modified_files[modified_count++], filename);
                          }
                      }
                  }
              }
          } else {
              strcpy(untracked_files[untracked_count++], filename);
          }
      }
  }
  closedir(dir);

  printf("Staged files:\n");
  for (int i = 0; i < staged_count; i++) {
      printf("  %s\n", staged_files[i]);
  }

  printf("\nChanges not staged for commit:\n");
  for (int i = 0; i < modified_count; i++) {
      printf("  %s\n", modified_files[i]);
  }

  printf("\nUntracked files:\n");
  for (int i = 0; i < untracked_count; i++) {
      printf("  %s\n", untracked_files[i]);
  }
}