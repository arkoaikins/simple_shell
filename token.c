#include "s_shell.h"

int token_len(char *str, char *dlim);
int count_tokens(char *str, char *dlim);
char **strtoken(char *line, char *dlim);

/**
 * token_len - Looks for dlimiter index
 * @str: string to be searched.
 * @dlim: The dlimiter  .
 *
 * Return: The dlimiter index.
 */
int token_len(char *str, char *dlim)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *dlim)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * count_tokens - Counts the delimeter in strings
 * @str: string to be searched.
 * @dlim: The dlimiter character.
 *
 * Return: words contained within str.
 */
int count_tokens(char *str, char *dlim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *dlim)
		{
			tokens++;
			index += token_len(str + index, dlim);
		}
	}

	return (tokens);
}

/**
 * strtoken - The string that is tokenized.
 * @line: This is the string.
 * @dlim: The dlimeter that will tokenize the sting.
 *
 * Return: the pointer of the tokenized words.
 */
char **strtoken(char *line, char *dlim)
{
	char **pnt;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(line, dlim);
	if (tokens == 0)
		return (NULL);

	pnt = malloc(sizeof(char *) * (tokens + 2));
	if (!pnt)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *dlim)
			index++;

		letters = token_len(line + index, dlim);

		pnt[t] = malloc(sizeof(char) * (letters + 1));
		if (!pnt[t])
		{
			for (index -= 1; index >= 0; index--)
				free(pnt[index]);
			free(pnt);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			pnt[t][l] = line[index];
			index++;
		}

		pnt[t][l] = '\0';
	}
	pnt[t] = NULL;
	pnt[t + 1] = NULL;

	return (pnt);
}
