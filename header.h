#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))

/*constants*/
#define INVALID_COMMAND -1
#define EXTERNAL_COMMAND 1
#define PATH_COMMAND 3
#define INTERNAL_COMMAND 2

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/**
 *struct map - a struct that maps a command name to a function 
 *
 *@command_name: name of the command
 *@func: the function that executes the command
 */
typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

/*tokenizer.c*/
char **tokenizer(char *, char *);
void print(char *, int);
void remove_newline(char *);
int _strlen(char *);
void _strcpy(char *, char *);

/*string.c*/
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);
char *_strchr(char *, char);

/*sllocate_memory.c*/
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ctrl_c_handler(int);
void remove_comment(char *);

/*utils.c*/
int parse_command(char *);
void execute_command(char **, int);
char *check_path(char *);
void (*get_func(char *))(char **);
char *_getenv(char *);

/*built_in.c*/
void env(char **);
void quit(char **);

/*main*/
extern void non_interactive(void);
extern void initializer(char **current_command, int type_command);

#endif /*SHELL_H*/


