#include "../janus.h"

void jlog() {
  FILE *logs = fopen(LOGS_FILE, "r");
  if (!logs) {
      perror("Failed to open logs file");
      return;
  }
  char ch;
  while ((ch = fgetc(logs)) != EOF) {
      putchar(ch);
  }
  fclose(logs);
}