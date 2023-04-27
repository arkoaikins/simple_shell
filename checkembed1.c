#include "s_shell.h"

void env_helper(void);
void setenv_hepler_1(void);
void unset_helper(void);
void ance_helper(void);

/**
 * env_helper - Displays information on the shellby builtin cmd 'env'.
 */
void env_helper(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * setenv_hepler_1 - Displays information on the shellby builtin cmd 'setenv'.
 */
void setenv_hepler_1(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * unset_helper - Displays information on the shellby builtin cmd
 * 'unsetenv'.
 */
void unset_helper(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
