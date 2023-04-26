#include "s_shell.h"

void *re_alloc(void *pnt, unsigned int size1, unsigned int size2);
void assign_linepnt(char **linepnt, size_t *n, char *buffer, size_t b);
ssize_t line_gets(char **linepnt, size_t *n, FILE *strm);

/**
 * re_alloc - Reallocates a memory block using malloc and free.
 * @pnt: A pointer to the memory previously allocated.
 * @size1: The size in bytes of the allocated space for pnt.
 * @size2: The size in bytes for the new memory block.
 *
 * Return: If size2 == size1 - pnt.
 *         If size2 == 0 and pnt is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *re_alloc(void *pnt, unsigned int size1, unsigned int size2)
{
	void *mem;
	char *pnt_copy, *filler;
	unsigned int index;

	if (size2 == size1)
		return (pnt);

	if (pnt == NULL)
	{
		mem = malloc(size2);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (size2 == 0 && pnt != NULL)
	{
		free(pnt);
		return (NULL);
	}

	pnt_copy = pnt;
	mem = malloc(sizeof(*pnt_copy) * size2);
	if (mem == NULL)
	{
		free(pnt);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < size1 && index < size2; index++)
		filler[index] = *pnt_copy++;

	free(pnt);
	return (mem);
}

/**
 * assign_linepnt - Reassigns the linepnt variable for line_gets.
 * @linepnt: A buffer to store an input string.
 * @n: The size of linepnt.
 * @buffer: The string to assign to linepnt.
 * @b: The size of buffer.
 */
void assign_linepnt(char **linepnt, size_t *n, char *buffer, size_t b)
{
	if (*linepnt == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*linepnt = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*linepnt = buffer;
	}
	else
	{
		_strcpy(*linepnt, buffer);
		free(buffer);
	}
}

/**
 * line_gets - Reads input from a strm.
 * @linepnt: A buffer to store the input.
 * @n: The size of linepnt.
 * @strm: The strm to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t line_gets(char **linepnt, size_t *n, FILE *strm)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(strm);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buffer = re_alloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_linepnt(linepnt, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
