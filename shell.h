#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global Environemnt */
extern char **environ;

/* Global Program Name */
char *name;

/* Global History Counter */
int hist;

/**
 * struct lists_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct lists_s
{
	char *dir;
	struct lists_s *next;
} lists_t;

/**
 * struct builtins_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtins_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtins_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct aliases_s
{
	char *name;
	char *value;
	struct aliases_s *next;
} aliases_t;

/* Global aliases linked list */
aliases_t *aliases;

/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
lists_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(lists_t *head);
char *_itoa(int num);

/* Input Helpers */
void handleline(char **line, ssize_t read);
void variable_replacer(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_alias(char **args);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int shellie_exit(char **args, char **front);
int shellie_env(char **args, char __attribute__((__unused__)) **front);
int shellie_setenv(char **args, char __attribute__((__unused__)) **front);
int shellie_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellie_cd(char **args, char __attribute__((__unused__)) **front);
int shellie_alias(char **args, char __attribute__((__unused__)) **front);
int shellie_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copy_env(void);
void free_env(void);
char **_get_env(const char *var);

/* Error Handling */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
aliases_t *add_alias_end(aliases_t **head, char *name, char *value);
void free_alias_list(aliases_t *head);
lists_t *add_node_end(lists_t **head, char *dir);
void free_list(lists_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_commands(char *file_path, int *exe_ret);

#endif /* SHELL_H */
