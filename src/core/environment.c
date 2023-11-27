/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/27 14:02:07 by abareux          ###   ########.fr       */
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

void	set_env(t_shell *sh, const char *name, const char *value)
{
	(void) sh;
	(void) name;
	(void) value;
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

void	unload_env(t_shell *sh)
{
	char	**tmp;

	tmp = sh->env;
	if (!tmp)
		return ;
	while (*tmp)
		free(*tmp++);
	free(sh->env);
}
