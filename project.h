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
void printEnvironment(char **env);
size_t _strcspn(char *_str, char *_reject);
size_t _strspn(char *_str, char *_accept);
char *_strtok(char *_str, char *_delimiters);
ssize_t own_getline(char **line, size_t *size, int fd);
void changeDirectory(char **_par);
void customErrorPrint(char *command);
ssize_t bufferAndReadInput(info_t *info, char **buf, size_t *len);
ssize_t getUserInput(info_t *info);
ssize_t readBuffer(info_t *info, char *buf, size_t *i);
int getNextLine(info_t *info, char **ptr, size_t *length);
void blockCtrlC(__attribute__((unused)) int sig_num);
/*extern char **environ;*/

#define INITIAL_BUFFER_SIZE 128
#define DELIM " \t\r\n\a\"'|"

#endif /*_PROJECT_H*/
