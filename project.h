#ifndef _PROJECT_H
#define _PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int show(char *_x);
int wordsno(char *_cmd, char _c);
void dollar(void);
char *_strdup(const char *_tr);
char *_strcpy(char *_dest, char *_src);
int _strlen(char *_s);
char *_strchr(char *_s, int _c);
int _strcmp(char *_s1, char *_s2);
char *_strcat(char *_dest, char *_src);
void exitShell(char *_cmd, char **_par);
void printEnvironment(void);
size_t _strcspn(char *_str, char *_reject);
size_t _strspn(char *_str, char *_accept);
char *_strtok(char *_str, char *_delimiters);
ssize_t own_getline(char **line, size_t *size, int fd);

extern char **environ;

#define INITIAL_BUFFER_SIZE 128

#endif /*_PROJECT_H*/
