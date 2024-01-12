/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:44:52 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:44:54 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(int argc, char **argv)
{
	int	argv_cursor;

	argv_cursor = 1;
	while (argc != 1 && !ft_strncmp(*(argv + argv_cursor), "-n", 3))
		argv_cursor++;
	while (argv_cursor < argc)
	{
		write(1, *(argv + argv_cursor), ft_strlen(*(argv + argv_cursor)));
		argv_cursor++;
		if (argv_cursor < argc)
			write(1, " ", 1);
	}
	if (argc == 1 || ft_strncmp(*(argv + 1), "-n", 3))
		write(1, "\n", 1);
	return (0);
}
