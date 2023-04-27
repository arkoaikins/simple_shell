#include "s_shell.h"

void free_agt(char **agt, char **top);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void _replacer(char **agt, int *impret);

/**
 * free_agt - Frees up memory space taken by agt.
 * @agt: points to memory space.
 * @top: points to the beginning of agt.
 */
void free_agt(char **agt, char **top)
{
	size_t i;

	for (i = 0; agt[i] || agt[i + 1]; i++)
		free(agt[i]);

	free(top);
}

/**
 * get_pid - accpets current process ID.
 * Description: The function that reads the PID into
 *              a buffer and replace the space
 *              at the end with a \0 byte.
 *
 * Return: The working process ID .
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - accpets the value corresponding to an environmemt variable.
 * @beginning: The environment variable to search.
 * @len: length of the environment variable to search.
 *
 * Return: empty string if the variable  not found
 *         else - value of the environmental variable.
 *
 * Description: stored variables in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = env_get(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * _replacer - variable replacer.
 * @line: points to cmd and arguments.
 * @impret: points to the return value of the last performd comm.
 *
 * Description: Replaces envrionmental variables preceded by $
 *              with their corresponding value
 *              $$  and the current PID, $? with the return value
 *              of the last performd program,
 */

void _replacer(char **line, int *impret)
{
	int j, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
		    old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _attol(*impret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
					     old_line[k] != '$' &&
					     old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = get_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(replacement)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
