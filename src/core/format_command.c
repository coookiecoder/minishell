/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   NOOT NOOT MOTHER FUCKER                      :#:  :#:         :#:  :#:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: the-day-it-was updated by UwU                                   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	clear_argv(t_command *command)
{
	int	cursor;

	cursor = 0;
	while (*(command->argv + cursor))
		free(*(command->argv + cursor++));
	free(command->argv);
}

static
int	find_argv_number(char *buffer, int *argv_cursor)
{
	int	space;
	int	result;
	int	cursor;

	space = 1;
	result = 0;
	cursor = 0;
	*argv_cursor = 0;
	while (*(buffer + cursor))
	{
		if (*(buffer + cursor) != ' ' && space && *(buffer + cursor))
		{
			result = result + 1;
			space = 0;
		}
		if (*(buffer + cursor++) == ' ')
			space = 1;
	}
	return (result);
}

static
int	arg_len(char *buffer)
{
	int	len;

	len = 0;
	while (*(buffer + len) && *(buffer + len) != ' ')
		len++;
	return (len);
}

static
void	putargv(char *argv, char *buffer, int *cursor_main)
{
	int	cursor;

	cursor = 0;
	while (*(buffer + cursor) && *(buffer + cursor) != ' ')
	{
		*(argv + cursor) = *(buffer + cursor);
		cursor++;
		(*cursor_main)++;
	}
	*(argv + cursor) = '\0';
	while (*(buffer + cursor) == ' ')
	{
		cursor++;
		(*cursor_main)++;
	}
}

void	format_command(char *buffer, t_command *command)
{
	int	cursor;
	int	argv_cursor;

	cursor = 0;
	while (*(buffer + cursor) != ' ' && *(buffer + cursor))
	{
		*(command->bin + cursor) = *(buffer + cursor);
		cursor++;
	}
	while (*(buffer + cursor) == ' ' && *(buffer + cursor))
		cursor++;
	if (command->argv)
		clear_argv(command);
	command->argc = find_argv_number(buffer + cursor, &argv_cursor) + 1;
	command->argv = malloc(sizeof(char *) * (command->argc + 1));
	if (!command->argv)
		return ;
	while (*(buffer + cursor))
	{
		*(command->argv + argv_cursor) = malloc(arg_len(buffer + cursor) + 1);
		putargv(*(command->argv + argv_cursor++), buffer + cursor, &cursor);
	}
	*(command->argv + argv_cursor) = NULL;
}
