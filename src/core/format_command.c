/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:45:50 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:45:54 by abareux          ###   ########.fr       */
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
	enum e_quotetype	quote;
	int					len;

	len = 0;
	quote = NO_QUOTE;
	while (*(buffer + len))
	{
		assign_quote_value(&quote, *(buffer + len));
		if (!quote && *(buffer + len) == ' ')
			break ;
		len++;
	}
	return (len);
}

static
void	putargv(char *argv, char *buffer, int *cursor_main)
{
	enum e_quotetype	old;
	enum e_quotetype	quote;
	int					cursor;

	quote = 0;
	cursor = 0;
	if (!argv)
		return ;
	while (*(buffer))
	{
		old = quote;
		assign_quote_value(&quote, *(buffer));
		if (!quote && *(buffer) == ' ')
			break ;
		if (*(buffer) != (char) quote && *(buffer) != (char) old)
			*(argv + cursor++) = *(buffer);
		buffer++;
		(*cursor_main)++;
	}
	*(argv + cursor) = '\0';
	while (*(buffer) == ' ')
	{
		buffer++;
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
	command->argv = malloc(sizeof(char *) * (command->argc + 1));
	if (!command->argv)
		return ;
	while (argv_cursor < command->argc)
	{
		*(command->argv + argv_cursor) = malloc(arg_len(buffer + cursor) + 1);
		putargv(*(command->argv + argv_cursor++), buffer + cursor, &cursor);
	}
	*(command->argv + command->argc) = NULL;
}
