#include "s_shell.h"

alias_t *alias_adder(alias_t **head, char *name, char *value);
void release_alias_l(alias_t *head);
list_t *node_adder(list_t **head, char *dir);
void _releasing(list_t *head);

/**
 * alias_adder - Adds node to linked lists.
 * @head: points to the head of the list_t.
 * @name: name of  new alias .
 * @value:  value of alias that will be added.
 * Return: NULL,if error.
 *         else - return pointer to the new node.
 */
alias_t *alias_adder(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * node_adder - node adder.
 * @head: points to the head of the list_t .
 * @dir: The  path for the new nodes.
 *
 * Return: NULL,if error occures.
 *         else - return pointer to the new node.
 */
list_t *node_adder(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * release_alias_l - Frees  alias_t linked list.
 * @head: head of the alias_t list.
 */
void release_alias_l(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * _releasing - Frees  list_t linked list.
 * @head: head of the list_t list.
 */
void _releasing(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
