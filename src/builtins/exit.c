/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:45:02 by abareux           #+#    #+#             */
/*   Updated: 2024/01/26 10:51:27 by flcollar         ###   ########.fr       */
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
	code_int = -1;
	if (*(code + cursor) == '\0')
		code_int = atolli(code);
	if (code_int == -1)
	{
		write(1, "bash: exit: ", 13);
		write(1, code, ft_strlen(code));
		write(1, ": numeric argument required\n", 29);
		code_int = 2;
	}
	else if (cmd->argc > 2)
		return (write(1, "exit\nbash: exit: too many arguments\n", 37), 300);
	return (code_int);
}
