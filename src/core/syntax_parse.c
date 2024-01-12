/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:48:45 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:48:47 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*purge_quote(char *str)
{
	t__exp		e;

	e = (t__exp){NO_QUOTE, ft_strdup(""), 0, 0};
	if (!e.tmp)
		return (free(str), NULL);
	while (str[e.x])
	{
		e.y = e.quote;
		assign_quote_value(&e.quote, str[e.x]);
		if (str[e.x] == (char) e.quote || str[e.x] == (char) e.y)
		{
			e.x++;
			continue ;
		}
		e.tmp = ft_strjoin(e.tmp, &str[e.x++], LEFT, 1);
		if (!e.tmp)
			return (free(str), NULL);
	}
	return (free(str), e.tmp);
}

static
int	apply_expension(t_shell *sh, char **base, char *raw)
{
	int		len;
	char	*env;
	char	*val;

	len = 0;
	if (raw && raw[len] == '?')
	{
		*base = ft_strjoin(*base, \
			ft_itoa((char)(((sh->last_code) & 0xff00) >> 8)), BOTH, -1);
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
	enum e_quotetype	quote;
	size_t				c;

	c = 0;
	quote = 0;
	while (raw && *raw)
	{
		assign_quote_value(&quote, *raw);
		if (*(raw++) == '|' && quote == NO_QUOTE)
			c++;
	}
	return (c);
}
