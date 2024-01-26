/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:44:52 by abareux           #+#    #+#             */
/*   Updated: 2024/01/26 16:02:24 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
int	check_n(char *arg)
{
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (0);
		arg++;
	}
	return (1);
}

static
int	check_option(char **argv, int *argv_cursor)
{
	*argv_cursor = 1;
	while (argv[*argv_cursor] && argv[*argv_cursor][0] == '-')
	{
		if (check_n(argv[*argv_cursor]))
			(*argv_cursor)++;
		else
			return (*argv_cursor > 1);
	}
	return (*argv_cursor > 1);
}

int	echo(int argc, char **argv)
{
	int	argv_cursor;
	int	new_line;

	new_line = check_option(argv, &argv_cursor);
	while (argv_cursor < argc)
	{
		write(1, *(argv + argv_cursor), ft_strlen(*(argv + argv_cursor)));
		argv_cursor++;
		if (argv_cursor < argc)
			write(1, " ", 1);
	}
	if (!new_line)
		write(1, "\n", 1);
	return (0);
}
