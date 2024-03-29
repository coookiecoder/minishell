/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:44:45 by abareux           #+#    #+#             */
/*   Updated: 2024/01/17 16:59:51 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
void	put_in_env(char **env, char *path)
{
	char	*new_pwd;
	int		cursor;

	new_pwd = malloc(ft_strlen(path) + 5);
	if (!new_pwd)
		return ;
	cursor = 0;
	*(new_pwd + 0) = 'P';
	*(new_pwd + 1) = 'W';
	*(new_pwd + 2) = 'D';
	*(new_pwd + 3) = '=';
	while (*(path + cursor))
	{
		*(new_pwd + cursor + 4) = *(path + cursor);
		cursor++;
	}
	*(new_pwd + cursor + 4) = '\0';
	free(*env);
	*env = new_pwd;
}

static
char	*parse_path(t_shell *shell, char *command)
{
	char	*old_path;

	if (command[0] == '/')
		return (parse_path_absolute(command));
	old_path = shell->pwd;
	if (old_path && !old_path[1])
		return (parse_path_absolute(command));
	return (parse_path_relative(shell, command));
}

static
int	set_pwd(t_shell *shell, char *command)
{
	int		cursor;

	cursor = 0;
	while (*(shell->env + cursor))
	{
		if (!ft_strncmp(*(shell->env + cursor), "PWD=", 4))
			put_in_env(shell->env + cursor, command);
		cursor++;
	}
	put_in_tab(shell->pwd, command);
	free(command);
	return (0);
}

int	cd(int argc, char **argv, t_shell *shell)
{
	char	*buffer;

	if (argc > 2)
		return (write(1, "bash: cd: too many arguments\n", 30), 1);
	else if (argc < 2)
		return (write(1, "bash: cd: not enough arguments\n", 32), 1);
	buffer = parse_path(shell, *(argv + 1));
	if (chdir(buffer))
	{
		if (errno == EACCES)
		{
			write(1, "bash: cd: ", 11);
			write(1, *(argv + 1), ft_strlen(*(argv + 1)));
			write(1, ": permissions denied\n", 22);
		}
		else
		{
			write(1, "bash: cd: ", 11);
			write(1, *(argv + 1), ft_strlen(*(argv + 1)));
			write(1, ": is not a directory\n", 22);
		}
		return (free(buffer), 1);
	}
	return (set_pwd(shell, buffer));
}
