#include "janus.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: janus <command> [args]\n");
    printf("Commands: init\n");
    printf("          add <file>\n");
    printf("          commit <message>\n");
    printf("          log\n");
    printf("          status\n");
    return 1;
  }

  if (strcmp(argv[1], "init") == 0) {
        init();
    } else if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            printf("Usage: janus add <file>\n");
            return 1;
        }
        add(argv[2]);
    } else if (strcmp(argv[1], "commit") == 0) {
        if (argc < 3) {
            printf("Usage: janus commit <message>\n");
            return 1;
        }
        commit(argv[2]);
    } else if (strcmp(argv[1], "log") == 0) {
        jlog();
    } else if (strcmp(argv[1], "status") == 0) {
        status();
    } else {
        printf("Unknown command: %s\n", argv[1]);
    }
}