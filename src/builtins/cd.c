/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:44:45 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:44:47 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	*(new_pwd + cursor + 5) = '\0';
	free(*env);
	*env = new_pwd;
}

static
int	set_pwd(t_shell *shell)
{
	char	path[PATH_MAX];
	int		cursor;

	getcwd(path, PATH_MAX - 1);
	cursor = 0;
	while (*(shell->env + cursor))
	{
		if (!ft_strncmp(*(shell->env + cursor), "PWD=", 4))
			put_in_env(shell->env + cursor, path);
		cursor++;
	}
	return (0);
}

int	cd(int argc, char **argv, t_shell *shell)
{
	if (argc != 2)
	{
		if (argc > 2)
			write(1, "bash: cd: too many arguments\n", 30);
		else
			write(1, "bash: cd: not enough arguments\n", 32);
		return (1);
	}
	if (chdir(*(argv + 1)))
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
		return (1);
	}
	return (set_pwd(shell));
}
