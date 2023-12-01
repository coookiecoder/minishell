/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   NOOT NOOT MOTHER FUCKER                      :#:  :#:         :#:  :#:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: the-day-it-was updated by UwU                                   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	builtin(t_command command)
{
	if (!strncmp(command.bin, "pwd", 4))
		return (1);
	else if (!strncmp(command.bin, "cd", 3))
		return (1);
	else if (!strncmp(command.bin, "echo", 5))
		return (1);
	else if (!strncmp(command.bin, "env", 4))
		return (1);
	else if (!strncmp(command.bin, "export", 7))
		return (1);
	else if (!strncmp(command.bin, "unset", 6))
		return (1);
	return (0);
}

int	do_builtin(t_command command, t_shell *shell)
{
	if (!strncmp(command.bin, "pwd", 4))
		return (pwd());
	else if (!strncmp(command.bin, "cd", 3))
		return (cd(command.argc, command.argv, shell));
	else if (!strncmp(command.bin, "echo", 5))
		return (echo(command.argc, command.argv));
	else if (!strncmp(command.bin, "env", 4))
		return (env(shell));
	else if (!strncmp(command.bin, "export", 7))
		return (ft_export(shell, command));
	else if (!strncmp(command.bin, "unset", 6))
		return (unset_env(shell, command));
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
	int		cursor;

	cursor = 0;
	while (ft_strncmp(*(shell->env + cursor), "PATH=", 5))
		cursor++;
	path = *(shell->env + cursor);
	cursor = 0;
	while (*(path + cursor))
	{
		if (*(path + cursor) == ':')
			if (try_bin(buffer, command, shell) != -1)
				return ;
		*(buffer + cursor) = *(path + cursor);
		cursor++;
	}
	exit(1);
}

int	make_command(t_command command, t_shell *shell, t_exec *exe, size_t pos)
{
	pid_t	pid;
	int		fds[2];

	if (builtin(command))
		return (do_builtin(command, shell));
	if (pos < exe->total - 1)
		pipe(fds);
	pid = fork();
	if (!pid)
	{
		if (pos < exe->total - 1)
			dup2(fds[1], STDOUT_FILENO);
		if (pos)
			dup2(fds[0], STDIN_FILENO);
		try_path(command, shell);
	}
	g_sig = 1;
	waitpid(-1, &shell->last_code, 0);
	g_sig = 0;
	return (0);
}
