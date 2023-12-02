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
		return (do_builtin(cmd, sh));
	tmp = dup(STDOUT_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	ret = do_builtin(cmd, sh);
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
			exit(do_builtin(&command, shell));
		close_fd(pos, exe);
		close_fd(pos + 1, exe);
		try_path(command, shell);
	}
	g_sig = EXECUTION;
	close_fd(pos, exe);
	waitpid(pid, &shell->last_code, 0);
	g_sig = NORMAL;
	return (1);
}
