#include "s_shell.h"

void sig_handler(int sig);
int perform(char **agt, char **top);

/**
 * sig_handler - Prints a new prompt.
 * @sig: Signal.
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n#cisfun$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 10);
}

/**
 * perform - Executes a command in a child process.
 * @agt: Array of arguments.
 * @top: A double pointer to the beginning of agt.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last performd cmd.
 */
int perform(char **agt, char **top)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *cmd = agt[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = locate(cmd);
	}

	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (do_error(agt, 126));
		else
			ret = (do_error(agt, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, agt, environ);
			if (errno == EACCES)
				ret = (do_error(agt, 126));
			free_env();
			free_agt(agt, top);
			release_alias_l(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: Array of pointers to the arguments.
 *
 * Return: The return value of the last performd command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *impret = &retn;
	char *prompt = "#cisfun$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*impret = 0;
	environ = env_copy();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = prog_commd(argv[1], impret);
		free_env();
		release_alias_l(aliases);
		return (*impret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_agt(impret);
		free_env();
		release_alias_l(aliases);
		return (*impret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 10);
		ret = handle_agt(impret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 10);
			free_env();
			release_alias_l(aliases);
			exit(*impret);
		}
	}

	free_env();
	release_alias_l(aliases);
	return (*impret);
}
