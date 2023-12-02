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

static
int	apply_expension(t_shell *sh, char **base, char *raw)
{
	int		len;
	char	*env;
	char	*val;

	len = 0;
	if (raw && raw[len] == '?')
	{
		*base = ft_strjoin(*base, ft_itoa(sh->last_code), BOTH, -1);
		return (2);
	}
	while (raw && raw[len] && (raw[len] == '_' \
		|| (raw[len] >= 'a' && raw[len] <= 'z') \
		|| (raw[len] >= 'A' && raw[len] <= 'Z') \
		|| (raw[len] >= '0' && raw[len] <= '9')))
		len++;
	env = ft_strndup(raw, len);
	val = get_env(sh, env);
	if (val)
		*base = ft_strjoin(*base, val, LEFT, -1);
	free(env);
	return (len + 1);
}

char	*expension(t_shell *sh, char *raw)
{
	t__exp	e;

	e = (t__exp){NO_QUOTE, ft_strdup(""), 0, 0};
	if (!e.tmp)
		return (NULL);
	while (raw[e.x])
	{
		assign_quote_value(&e.quote, raw[e.x]);
		if (raw[e.x] == '$' && e.quote != SINGLE_QUOTE && raw[e.x + 1])
			e.x += apply_expension(sh, &e.tmp, &raw[e.x + 1]);
		else
			e.tmp = ft_strjoin(e.tmp, &raw[e.x++], LEFT, 1);
		if (!e.tmp)
			return (NULL);
	}
	return (e.tmp);
}

size_t	pipe_counter(char *raw)
{
	size_t	c;

	c = 0;
	while (raw && *raw)
		if (*(raw++) == '|')
			c++;
	return (c);
}

static
int	execution_subparse(t_exec *exe, char *raw, t__exp *e, int *toggle)
{
	if (raw[e->x] == '|' && e->quote != SINGLE_QUOTE && raw[e->x + 1])
	{
		if (*toggle)
			return (write(2, ERR_PARSE_SYNTAX, ERR_PARSE_SYNTAX_N), 0);
		*toggle = 1;
		e->x++;
	}
	else
	{
		exe->cmds[e->y]->raw = \
			ft_strndup(&raw[e->x], ft_strclen(&raw[e->x], '|'));
		if (!exe->cmds[e->y++])
			return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
		*toggle = 0;
		e->x += ft_strclen(&raw[e->x], '|');
	}
	return (1);
}

int	execution_parse(t_exec *exe, char *raw)
{
	t__exp	e;
	int		toggle;

	toggle = 0;
	e = (t__exp){NO_QUOTE, NULL, 0, 0};
	while (raw[e.x])
	{
		while (raw[e.x] == ' ' || (raw[e.x] >= '\t' && raw[e.x] <= '\r'))
			e.x++;
		assign_quote_value(&e.quote, raw[e.x]);
		if (!execution_subparse(exe, raw, &e, &toggle))
			return (0);
	}
	return (1);
}
