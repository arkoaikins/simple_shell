#include "s_shell.h"

int (*get_builtin(char *cmd))(char **agt, char **top);
int by_exit(char **agt, char **top);
int by_cd(char **agt, char __attribute__((__unused__)) **top);
int by_help(char **agt, char __attribute__((__unused__)) **top);

/**
 * get_builtin - Matches a cmd with a corresponding
 *               shellby builtin function.
 * @cmd: The cmd to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *cmd))(char **agt, char **top)
{
	builtin_t funcs[] = {
		{ "exit", by_exit },
		{ "env", by_env },
		{ "setenv", by_set },
		{ "unsetenv", by_unset },
		{ "cd", by_cd },
		{ "alias", by_alias },
		{ "help", by_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, cmd) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * by_exit - Causes normal process termination
 *                for the shellby shell.
 * @agt: An array of arguments containing the exit value.
 * @top: A double pointer to the beginning of agt.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int by_exit(char **agt, char **top)
{
	int i = 0, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (agt[0])
	{
		if (agt[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; agt[0][i]; i++)
		{
			if (i <= len_of_int && agt[0][i] >= '0' && agt[0][i] <= '9')
				num = (num * 10) + (agt[0][i] - '0');
			else
				return (do_error(--agt, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (do_error(--agt, 2));
	agt -= 1;
	free_agt(agt, top);
	free_env();
	release_alias_l(aliases);
	exit(num);
}

/**
 * by_cd - Changes the current directory of the shellby process.
 * @agt: An array of arguments.
 * @top: A double pointer to the beginning of agt.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int by_cd(char **agt, char __attribute__((__unused__)) **top)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (agt[0])
	{
		if (*(agt[0]) == '-' || _strcmp(agt[0], "--") == 0)
		{
			if ((agt[0][1] == '-' && agt[0][2] == '\0') ||
			    agt[0][1] == '\0')
			{
				if (env_get("OLDPWD") != NULL)
					(chdir(*env_get("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (do_error(agt, 2));
			}
		}
		else
		{
			if (stat(agt[0], &dir) == 0 && S_ISDIR(dir.st_mode)
			    && ((dir.st_mode & S_IXUSR) != 0))
				chdir(agt[0]);
			else
			{
				free(oldpwd);
				return (do_error(agt, 2));
			}
		}
	}
	else
	{
		if (env_get("HOME") != NULL)
			chdir(*(env_get("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (by_set(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (by_set(dir_info, dir_info) == -1)
		return (-1);
	if (agt[0] && agt[0][0] == '-' && agt[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * by_help - Displays information about shellby builtin cmds.
 * @agt: An array of arguments.
 * @top: A pointer to the beginning of agt.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int by_help(char **agt, char __attribute__((__unused__)) **top)
{
	if (!agt[0])
		overall_helper();
	else if (_strcmp(agt[0], "alias") == 0)
		alias_helper();
	else if (_strcmp(agt[0], "cd") == 0)
		cd_helper();
	else if (_strcmp(agt[0], "exit") == 0)
		exit_helper();
	else if (_strcmp(agt[0], "env") == 0)
		env_helper();
	else if (_strcmp(agt[0], "setenv") == 0)
		setenv_hepler_1();
	else if (_strcmp(agt[0], "unsetenv") == 0)
		unset_helper();
	else if (_strcmp(agt[0], "help") == 0)
		wa_wa();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
