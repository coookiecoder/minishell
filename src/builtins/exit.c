/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:45:02 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:45:04 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	is_allowed(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	convert_code(t_command *cmd)
{
	char	*code;
	int		code_int;
	int		cursor;

	if (cmd->argc == 1)
		return (0);
	cursor = 0;
	code = cmd->argv[1];
	while (is_allowed(*(code + cursor)))
		cursor++;
	if (*(code + cursor) == '\0')
		code_int = atolli(code);
	else
		code_int = -1;
	if (code_int == -1)
	{
		write(1, "bash: exit: ", 13);
		write(1, code, ft_strlen(code));
		write(1, ": numeric argument required\n", 29);
		code_int = 2;
	}
	return (code_int);
}
