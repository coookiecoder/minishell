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

int	set_env_exists(t_shell *sh, int pos, char *raw)
{
	char	*tmp;

	tmp = ft_strdup(raw);
	if (!tmp)
		return (0);
	free(sh->env[pos]);
	sh->env[pos] = tmp;
	return (1);
}

int	set_env_new(t_shell *sh, int len, char *raw)
{
	char	*tmp;
	char	**buffer;
	int		i;

	tmp = ft_strdup(raw);
	if (!tmp)
		return (0);
	buffer = malloc(sizeof(void *) * (len + 2));
	if (!buffer)
		return (free(tmp), 0);
	i = -1;
	while (++i < len)
		buffer[i] = sh->env[i];
	buffer[i++] = tmp;
	buffer[i] = NULL;
	free(sh->env);
	sh->env = buffer;
	return (1);
}

static
int	is_valid(const char *raw)
{
	int		i;

	i = 0;
	while (raw && raw[i] && (raw[i] == '_' \
		|| (raw[i] >= 'a' && raw[i] <= 'z') \
		|| (raw[i] >= 'A' && raw[i] <= 'Z') \
		|| (raw[i] >= '0' && raw[i] <= '9')))
		i++;
	if (raw[i] != '=' || (raw[0] >= '0' && raw[0] <= '9'))
	{
		write(1, "bash: export: `", 15);
		write(1, raw, ft_strlen(raw));
		write(1, "': not a valid identifier\n", 26);
		return (0);
	}
	return (1);
}

int	ft_export(t_shell *sh, t_command cmd)
{
	int		c;
	int		fails;

	if (cmd.argc < 2)
		return (0);
	c = 1;
	fails = 0;
	while (c < cmd.argc)
	{
		if (!is_valid(cmd.argv[c]))
			fails++;
		else if (!set_env(sh, cmd.argv[c]))
			fails++;
		c++;
	}
	return (fails);
}
