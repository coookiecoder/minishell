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

int	set_env_exists(t_shell *sh, int pos, char *raw);
int	set_env_new(t_shell *sh, int len, char *raw);

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

int	set_env(t_shell *sh, char *raw)
{
	int		len;

	len = 0;
	while (sh->env[len])
	{
		if (!ft_strncmp(raw, sh->env[len], ft_strclen(raw, '=')))
			return (set_env_exists(sh, len, raw));
		len++;
	}
	return (set_env_new(sh, len, raw));
}

int	unset_env(t_shell *shell, t_command command)
{
	int	len;
	int	cursor;
	int	cursor_new;
	int	not_removed;

	if (command.argc == 1)
		return (0);
	len = 0;
	while (*(shell->env + len))
		len++;
	cursor = 0;
	cursor_new = 0;
	not_removed = 0;
	while (cursor < len)
	{
		if (keep_env(*(shell->env + cursor), command))
			*(shell->env + cursor_new++) = *(shell->env + cursor++);
		else
			cursor++;
	}
	not_removed = cursor - cursor_new;
	while (cursor_new <= len)
		*(shell->env + cursor_new++) = NULL;
	return (not_removed);
}

char	*get_env(t_shell *sh, const char *name)
{
	const int	len = ft_strlen(name);
	char		**tmp;

	if (!name)
		return (NULL);
	tmp = sh->env;
	while (*tmp)
	{
		if (!ft_strncmp(*tmp, name, len))
			return (*tmp + len + 1);
		tmp++;
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
