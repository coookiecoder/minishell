/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:44:28 by abareux           #+#    #+#             */
/*   Updated: 2024/01/29 18:08:44 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin(t_command *command)
{
	if (!ft_strncmp(command->bin, "pwd", 4))
		return (1);
	else if (!ft_strncmp(command->bin, "cd", 3))
		return (1);
	else if (!ft_strncmp(command->bin, "echo", 5))
		return (1);
	else if (!ft_strncmp(command->bin, "env", 4))
		return (1);
	else if (!ft_strncmp(command->bin, "export", 7))
		return (1);
	else if (!ft_strncmp(command->bin, "unset", 6))
		return (1);
	return (0);
}

int	do_builtin(t_command *command, t_shell *shell)
{
	if (!ft_strncmp(command->bin, "pwd", 4))
		return (pwd(shell));
	else if (!ft_strncmp(command->bin, "cd", 3))
		return (cd(command->argc, command->argv, shell));
	else if (!ft_strncmp(command->bin, "echo", 5))
		return (echo(command->argc, command->argv));
	else if (!ft_strncmp(command->bin, "env", 4))
		return (env(shell));
	else if (!ft_strncmp(command->bin, "export", 7))
		return (ft_export(shell, *command));
	else if (!ft_strncmp(command->bin, "unset", 6))
		return (unset_env(shell, *command));
	return (0);
}
