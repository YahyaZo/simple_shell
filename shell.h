#ifndef SHELL_H
#define SHELL_H

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stddef.h>
#include<string.h>
#include<sys/wait.h>
#include <limits.h>

extern char **environ;

/* built-in function*/
void start_shell(void);
void non_interactive_mode(char *token, int *status);
ssize_t reader(char **line, size_t *size_line);
void exit_status(int my_status, char **single_command,
char **token, int *status);
void custom_exit(int my_status, char **commands,
char *line, int *status);

/* execute command*/
void _execvep(char **commands, char **envp, int *status);
int _locate(char *command, char **full_path);
void wait_child_process(int *status);
char *_getenv(const char *path);
int _atoi(char *s);

/* handle line and delimiters(/n...)*/
char **tokenizer(char *str, char *delimiters);

/* write messages */
void write_error(char *command);
void write_exit_error(char *number);
void print_env_var(void);
void _getline_error(char *line);

/* string fucntion*/
char *_strdup(const char *src);
int _strlen(char *str);
int _strcmp(char *s1, char *s2);


/* free memory leak*/
void free_array(char **array);

#endif
