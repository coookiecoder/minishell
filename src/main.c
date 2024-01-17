/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <abareux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:56:35 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 13:08:15 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <signal.h>

enum e_sighandle	g_sig;

int	ft_waitpid(t_shell *shell)
{
	int	cursor;
	int	code;

	if (!shell->pids)
		return (1);
	cursor = 0;
	while (shell->pids[cursor])
	{
		waitpid(shell->pids[cursor++], &code, 0);
		if (g_sig != HANDLED)
			shell->last_code = (unsigned char)(((code) & 0xff00) >> 8);
	}
	free(shell->pids);
	g_sig = NORMAL;
	return (1);
}

static
int	inc_shlvl(t_shell *sh, const char **envp)
{
	char	*shlvl;
	char	*tmp;
	int		ret;

	*sh = (t_shell){0, 0, NULL, NULL};
	if (!load_env(sh, envp))
		return (0);
	shlvl = get_env(sh, "SHLVL");
	if (!shlvl)
		return (set_env(sh, "1"));
	tmp = ft_itoa(atolli(shlvl) + 1);
	if (!tmp)
		return (0);
	tmp = ft_strjoin("SHLVL=", tmp, RIGHT, -1);
	if (!tmp)
		return (0);
	ret = set_env(sh, tmp);
	free(tmp);
	set_code(0, sh);
	return (ret);
}

int	main(int argc, char **argv, const char **envp)
{
	char		*buffer;
	t_shell		shell;

	g_sig = NORMAL;
	if (!inc_shlvl(&shell, envp))
		return (ft_exit(NULL, &shell, NULL), 1);
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
