#ifndef S_SHELL_H
#define S_SHELL_H

#define END_OF_FILE -2
#define EXIT -3

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

/**
 *  The environ
 *  The name.
 *  counts history.
 */
extern char **environ;
char *name;
int hist;

/**
 * struct list_s - struct that defineslinked list.
 * @dir: the path of the directory.
 * @next: points to other struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - struct that defines added commands.
 * @name: name of the added commands.
 * @f: points to the builtin commands.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **top);
} builtin_t;

/**
 * struct alias_s - struct that defines aliases.
 * @name: name given to  alias.
 * @value: value given to alias.
 * @next: points to other struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/**
 *  aliases for the linked list(global)
 *  They help the main
 *  They help the input
 *  Functions of the sting used
 *   
 */

alias_t *aliases;

ssize_t line_gets(char **linepnt, size_t *n, FILE *strm);
void *re_alloc(void *pnt, unsigned int size1, unsigned int size2);
char **strtoken(char *line, char *dlim);
char *locate(char *cmd);
list_t *ret_dir(char *path);
int perform(char **agt, char **top);
void _releasing(list_t *head);
char *_attol(int num);

void handle_line(char **line, ssize_t read);
void _replacer(char **agt, int *impret);
char *get_agt(char *line, int *impret);
int call_agt(char **agt, char **top, int *impret);
int run_agt(char **agt, char **top, int *impret);
int handle_agt(int *impret);
int check_agt(char **agt);
void free_agt(char **agt, char **top);
int prog_commd(char *file_path, int *impret);
char **change_aliases(char **agt);

int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 *  Builtins
 *  Builtin Helpers
 *  Error Handling
 *  Linkedlist Helpers
 */

int (*get_builtin(char *cmd))(char **agt, char **top);
int by_exit(char **agt, char **top);
int by_env(char **agt, char __attribute__((__unused__)) **top);
int by_set(char **agt, char __attribute__((__unused__)) **top);
int by_unset(char **agt, char __attribute__((__unused__)) **top);
int by_cd(char **agt, char __attribute__((__unused__)) **top);
int by_alias(char **agt, char __attribute__((__unused__)) **top);
int by_help(char **agt, char __attribute__((__unused__)) **top);

char **env_copy(void);
void free_env(void);
char **env_get(const char *var);

int do_error(char **agt, int err);
char *environ_error(char **agt);
char *error_1(char **agt);
char *error_2_exit(char **agt);
char *error_2_cd(char **agt);
char *error_2_syntax(char **agt);
char *error_126(char **agt);
char *error_127(char **agt);

alias_t *alias_adder(alias_t **head, char *name, char *value);
void release_alias_l(alias_t *head);
list_t *node_adder(list_t **head, char *dir);
void _releasing(list_t *head);

void overall_helper(void);
void alias_helper(void);
void cd_helper(void);
void exit_helper(void);
void wa_wa(void);
void env_helper(void);
void setenv_hepler_1(void);
void unset_helper(void);
void ance_helper(void);

#endif
