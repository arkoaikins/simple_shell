#include "s_shell.h"

int num_len(int num);
char *_attol(int num);
int do_error(char **agt, int err);

/**
 * num_len - digits counter.
 * @num: measures number.
 *
 * Return: length of the digit.
 */
int num_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _attol - Changes integer into a string.
 * @num: The integer.
 *
 * Return: The string changed.
 */
char *_attol(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * do_error - prints a  error to standard err.
 * @agt: argument arrays.
 * @err: value of the error.
 *
 * Return: value of the error.
 */
int do_error(char **agt, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = environ_error(agt);
		break;
	case 1:
		error = error_1(agt);
		break;
	case 2:
		if (*(agt[0]) == 'e')
			error = error_2_exit(++agt);
		else if (agt[0][0] == ';' || agt[0][0] == '&' || agt[0][0] == '|')
			error = error_2_syntax(agt);
		else
			error = error_2_cd(agt);
		break;
	case 126:
		error = error_126(agt);
		break;
	case 127:
		error = error_127(agt);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
