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
	cursor = 1;
	while (cursor < cmd->argc)
		free(cmd->argv[cursor++]);
	if (cmd->raw)
		free(cmd->raw);
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
	free(exe->cmds);
}

int	ft_exit(char *buffer, t_shell *shell, t_command *command)
{
	int	code;

	if (command && command->argc > 1 && buffer)
	{
		code = convert_code(*(command->argv + 1));
		return (ft_free(buffer, shell, command), code);
	}
	write(1, "exit\n", 5);
	return (ft_free(buffer, shell, command), 0);
}
