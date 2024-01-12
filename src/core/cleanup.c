/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:45:31 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:45:36 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *buffer, t_shell *shell, t_command *command)
{
	if (buffer)
		free(buffer);
	unload_env(shell);
	ft_freecmd(command);
}

void	ft_freecmd(t_command *cmd)
{
	int	cursor;

	if (!cmd)
		return ;
	cursor = 0;
	while (cursor < cmd->argc)
		free(cmd->argv[cursor++]);
	if (cmd->raw)
		free(cmd->raw);
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	free(cmd->argv);
}

void	ft_freeexec(t_exec *exe)
{
	size_t	cursor;

	if (!exe)
		return ;
	cursor = -1;
	while (++cursor < exe->total)
	{
		if (exe->cmds[cursor])
		{
			ft_freecmd(exe->cmds[cursor]);
			free(exe->cmds[cursor]);
		}
	}
	if (exe->fds_odd[0] >= 0)
		close(exe->fds_odd[0]);
	if (exe->fds_odd[1] >= 0)
		close(exe->fds_odd[1]);
	if (exe->fds_even[0] >= 0)
		close(exe->fds_even[0]);
	if (exe->fds_even[1] >= 0)
		close(exe->fds_even[1]);
	free(exe->cmds);
}

int	ft_exit(char *buffer, t_shell *shell, t_command *command)
{
	write(1, "exit\n", 5);
	return (ft_free(buffer, shell, command), 0);
}

void	ft_bzero(char *buffer, const size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
		buffer[i++] = '\0';
}
