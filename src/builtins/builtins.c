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

int	builtin(t_command *command)
{
	if (!strncmp(command->bin, "pwd", 4))
		return (1);
	else if (!strncmp(command->bin, "cd", 3))
		return (1);
	else if (!strncmp(command->bin, "echo", 5))
		return (1);
	else if (!strncmp(command->bin, "env", 4))
		return (1);
	else if (!strncmp(command->bin, "export", 7))
		return (1);
	else if (!strncmp(command->bin, "unset", 6))
		return (1);
	return (0);
}

int	do_builtin(t_command *command, t_shell *shell)
{
	if (!strncmp(command->bin, "pwd", 4))
		return (pwd());
	else if (!strncmp(command->bin, "cd", 3))
		return (cd(command->argc, command->argv, shell));
	else if (!strncmp(command->bin, "echo", 5))
		return (echo(command->argc, command->argv));
	else if (!strncmp(command->bin, "env", 4))
		return (env(shell));
	else if (!strncmp(command->bin, "export", 7))
		return (ft_export(shell, *command));
	else if (!strncmp(command->bin, "unset", 6))
		return (unset_env(shell, *command));
	return (0);
}
