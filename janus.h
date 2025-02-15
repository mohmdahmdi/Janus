#ifndef VCS_H
#define VCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>

#define VCS_DIR ".janus"
#define OBJECTS_DIR ".janus/objects"
#define INDEX_FILE ".janus/index"
#define HEAD_FILE ".janus/HEAD"
#define LOGS_FILE ".janus/logs"

// command funcs (this part will be increased in the future)
void init();
void add(const char *file);
void commit(const char *message);
void jlog();
void status();

#endif