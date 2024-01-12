/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:47:15 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:47:18 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

enum e_sighandle	g_sig;

int	main(int argc, char **argv, const char **envp)
{
	char		*buffer;
	t_shell		shell;

	g_sig = NORMAL;
	shell = (t_shell){0, 0, NULL};
	load_env(&shell, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (argc || argv)
	{
		buffer = readline(SHELL_PROMPT);
		if (!buffer)
			return (ft_exit(buffer, &shell, NULL));
		if (is_empty(buffer))
		{
			free(buffer);
			continue ;
		}
		add_history(buffer);
		if (raw_parse(&shell, buffer))
			return (ft_exit(buffer, &shell, NULL), shell.exit);
		free(buffer);
	}
}
