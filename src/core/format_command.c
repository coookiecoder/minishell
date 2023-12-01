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

	cursor = 1;
	while (*(command->argv + cursor))
		free(*(command->argv + cursor++));
	free(command->argv);
}

static
int	find_argv_number(char *buffer, int *argv_cursor)
{
	int					space;
	int					result;
	int					cursor;
	enum e_quotetype	quote;

	space = 1;
	result = 0;
	cursor = 0;
	quote = NO_QUOTE;
	*argv_cursor = 1;
	while (*(buffer + cursor))
	{
		assign_quote_value(&quote, *(buffer + cursor));
		if (*(buffer + cursor) != ' ' && space && !quote && *(buffer + cursor))
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
	if (*buffer == '"')
	{
		len++;
		while (*(buffer + len) && *(buffer + len) != '"')
			len++;
	}
	else if (*buffer == '\'')
	{
		len++;
		while (*(buffer + len) && *(buffer + len) != '\'')
			len++;
	}
	else
		while (*(buffer + len) && *(buffer + len) != ' ')
			len++;
	return (len);
}

static
void	putargv(char *argv, char *buffer, int *cursor_main)
{
	char	delimiter;
	int		cursor;

	cursor = 0;
	delimiter = *(buffer + cursor++);
	if (delimiter != '"' && delimiter != '\'')
	{
		delimiter = ' ';
		cursor--;
	}
	while (*(buffer + cursor) && *(buffer + cursor) != delimiter)
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
	*(command->bin + cursor) = '\0';
	while (*(buffer + cursor) == ' ' && *(buffer + cursor))
		cursor++;
	if (command->argv)
		clear_argv(command);
	command->argc = find_argv_number(buffer + cursor, &argv_cursor) + 1;
	command->argv = malloc(sizeof(char *) * (command->argc));
	if (!command->argv)
		return ;
	while (argv_cursor < command->argc)
	{
		*(command->argv + argv_cursor) = malloc(arg_len(buffer + cursor) + 1);
		putargv(*(command->argv + argv_cursor++), buffer + cursor, &cursor);
	}
	*(command->argv) = NULL;
}
