/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:46:09 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 13:06:49 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_exec(t_shell *sh, t_exec *exe)
{
	size_t	i;

	sh->pids = malloc(sizeof(pid_t) * (exe->total + 1));
	if (!sh->pids)
		return (0);
	i = 0;
	g_sig = EXECUTION;
	while (i < exe->total)
	{
		sh->pids[i] = 0;
		if (!strncmp(exe->cmds[i]->bin, "exit", 5))
		{
			sh->exit = convert_code(exe->cmds[i]);
			return (exe->total == 1);
		}
		make_command(*(exe->cmds[i]), sh, exe, i);
		i++;
	}
	sh->pids[i] = 0;
	return (0);
}

int	try_bin(char *path_to_bin, t_command command, t_shell *shell)
{
	int	last_section;
	int	cursor;
	int	cursor_bin;

	last_section = 5;
	cursor = 0;
	cursor_bin = 0;
	while (*(path_to_bin + cursor))
		if (*(path_to_bin + cursor++) == ':')
			last_section = cursor;
	*(path_to_bin + cursor++) = '/';
	while (*(command.bin + cursor_bin))
		*(path_to_bin + cursor++) = *(command.bin + cursor_bin++);
	return (execve(path_to_bin + last_section, command.argv, shell->env));
}

void	try_path(t_command command, t_shell *shell)
{
	char	buffer[PATH_MAX];
	char	*path;
	int		crs;

	crs = 0;
	while (*(shell->env + crs) && ft_strncmp(*(shell->env + crs), "PATH=", 5))
		crs++;
	path = *(shell->env + crs);
	ft_bzero(buffer, PATH_MAX);
	crs = 0;
	execve(command.bin, command.argv, shell->env);
	while (path && *(path + crs))
	{
		if (*(path + crs) == ':')
			if (try_bin(buffer, command, shell) != -1)
				return ;
		*(buffer + crs) = *(path + crs);
		crs++;
	}
	write(2, ERR_UNKNOWN_CMD, ERR_UNKNOWN_CMD_N);
	if (command.fd_in >= 0)
		close(command.fd_in);
	if (command.fd_out >= 0)
		close(command.fd_out);
	exit(127);
}

static
int	singleton(t_command *cmd, t_shell *sh)
{
	int		tmp;
	int		ret;

	if (cmd->fd_out < 0)
		return (sh->last_code = do_builtin(cmd, sh) << 8);
	tmp = dup(STDOUT_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	ret = do_builtin(cmd, sh);
	sh->last_code = ret << 8;
	dup2(tmp, STDOUT_FILENO);
	close(tmp);
	return (ret);
}

int	make_command(t_command command, t_shell *shell, t_exec *exe, size_t pos)
{
	pid_t	pid;

	if (exe->total == 1 && builtin(&command))
		return (singleton(&command, shell));
	new_pipe(pos, exe);
	pid = fork();
	if (!pid)
	{
		duplicate_input(pos, exe);
		duplicate_output(pos, exe);
		if (command.fd_in)
			dup2(command.fd_in, STDIN_FILENO);
		if (command.fd_out)
			dup2(command.fd_out, STDOUT_FILENO);
		if (builtin(&command))
			exit(do_builtin(&command, shell) << 8);
		close_fd(pos, exe);
		close_fd(pos + 1, exe);
		try_path(command, shell);
	}
	close_fd(pos, exe);
	shell->pids[pos] = pid;
	return (1);
}
