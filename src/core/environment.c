/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/29 10:38:52 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	load_env(t_shell *sh, const char **envp)
{
	int	len;
	int	cursor;

	len = 0;
	while (*(envp + len))
		len++;
	sh->env = malloc(sizeof(char **) * (len + 1));
	if (!sh->env)
		return (0);
	cursor = 0;
	while (cursor < len)
	{
		*(sh->env + cursor) = ft_strdup(*(envp + cursor));
		cursor++;
	}
	*(sh->env + cursor) = NULL;
	return (1);
}

int	set_env(t_shell *shell, t_command command)
{
	int		len;
	int		cursor;
	char	**buffer;

	if (command.argc == 1)
		return (1);
	len = 0;
	while (*(shell->env + len))
		len++;
	buffer = malloc(sizeof(char **) * (len + command.argc));
	if (!buffer)
		return (1);
	cursor = 0;
	while (cursor < len)
	{
		*(buffer + cursor) = *(shell->env + cursor);
		cursor++;
	}
	if (export(buffer, command, &cursor))
		return (free(buffer), 1);
	*(buffer + cursor) = NULL;
	free(shell->env);
	shell->env = buffer;
	return (0);
}

void	unset_env(t_shell *sh, const char *name)
{
	(void) sh;
	(void) name;
}

char	*get_env(t_shell *sh, const char *name)
{
	const int	len = ft_strlen(name);
	char		**tmp;

	tmp = sh->env;
	while (*tmp)
	{
		if (!ft_strncmp(*tmp, name, len))
			return (*tmp + len + 1);
	}
	return (NULL);
}

void	unload_env(t_shell *shell)
{
	int	cursor;

	cursor = 0;
	if (!shell->env)
		return ;
	while (*(shell->env + cursor))
		free(*(shell->env + cursor++));
	free(shell->env);
}
