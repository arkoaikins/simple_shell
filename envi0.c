#include "s_shell.h"

int by_env(char **agt, char __attribute__((__unused__)) **top);
int by_set(char **agt, char __attribute__((__unused__)) **top);
int by_unset(char **agt, char __attribute__((__unused__)) **top);

/**
 * by_env - Prints the current environment.
 * @agt: An array of arguments passed to the shell.
 * @top: A double pointer to the beginning of agt.
 *
 * Return: If an error occurs - -1.
 *   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int by_env(char **agt, char __attribute__((__unused__)) **top)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)agt;
	return (0);
}

/**
 *by_set - Changes or adds an environmental variable to the PATH.
 * @agt: An array of arguments passed to the shell.
 * @top: A double pointer to the beginning of agt.
 * Description: agt[1] is the name of the new or existing PATH variable.
 *              agt[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int by_set(char **agt, char __attribute__((__unused__)) **top)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!agt[0] || !agt[1])
		return (do_error(agt, -1));

	new_value = malloc(_strlen(agt[0]) + 1 + _strlen(agt[1]) + 1);
	if (!new_value)
		return (do_error(agt, -1));
	_strcpy(new_value, agt[0]);
	_strcat(new_value, "=");
	_strcat(new_value, agt[1]);

	env_var = env_get(agt[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (do_error(agt, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * by_unset - Deletes an environmental variable from the PATH.
 * @agt: An array of arguments passed to the shell.
 * @top: A double pointer to the beginning of agt.
 * Description: agt[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int by_unset(char **agt, char __attribute__((__unused__)) **top)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!agt[0])
		return (do_error(agt, -1));
	env_var = env_get(agt[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (do_error(agt, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
