/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <abareux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:56:35 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 11:56:43 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

enum e_sighandle	g_sig;

void	ft_waitpid(t_shell *shell)
{
	int	cursor;

	if (!shell->pids)
		return ;
	cursor = 0;
	while (shell->pids[cursor])
		waitpid(shell->pids[cursor++], &shell->last_code, 0);
	free(shell->pids);
	g_sig = NORMAL;
}

int	main(int argc, char **argv, const char **envp)
{
	char		*buffer;
	t_shell		shell;

	g_sig = NORMAL;
	shell = (t_shell){0, 0, NULL, NULL};
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
		ft_waitpid(&shell);
		free(buffer);
	}
}
