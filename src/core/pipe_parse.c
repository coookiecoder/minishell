/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:46:19 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:46:22 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	skip_and_check(const char *raw, t__exp *e, int do_inc)
{
	if (do_inc)
	{
		e->x++;
		e->y++;
	}
	while (raw[e->x] == ' ' || (raw[e->x] >= '\t' && raw[e->x] <= '\r'))
		e->x++;
	if (raw[e->x] == '|')
		return (write(2, ERR_PARSE_SYNTAX, ERR_PARSE_SYNTAX_N), 0);
	return (1);
}

static
int	pre_alloc_next(t_exec *exe, t__exp *e)
{
	if (!exe->cmds[e->y]->raw)
		exe->cmds[e->y]->raw = ft_strdup("");
	if (!exe->cmds[e->y]->raw)
		return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
	return (1);
}

static
int	quote_divide(const char *raw, t_exec *exe, t__exp *e)
{
	int		len;

	len = 1;
	while (raw[e->x + len] && raw[e->x + len] != (char) e->quote)
		len++;
	if (raw[e->x + len] != (char) e->quote)
		return (write(2, ERR_PARSE_SYNTAX, ERR_PARSE_SYNTAX_N), 0);
	e->tmp = ft_strndup(&raw[e->x], len);
	if (!exe->cmds[e->y]->raw)
		return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
	exe->cmds[e->y]->raw = \
		ft_strjoin(exe->cmds[e->y]->raw, e->tmp, BOTH, -1);
	if (!exe->cmds[e->y]->raw)
		return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
	e->x += len;
	return (1);
}

int	execution_parse(t_exec *exe, char *raw)
{
	t__exp	e;

	e = (t__exp){NO_QUOTE, NULL, 0, 0};
	if (!skip_and_check(raw, &e, 0))
		return (0);
	while (raw[e.x])
	{
		assign_quote_value(&e.quote, raw[e.x]);
		if (!pre_alloc_next(exe, &e))
			return (0);
		if (e.quote == NO_QUOTE)
		{
			if (raw[e.x] == '|')
				if (!skip_and_check(raw, &e, 1) || !pre_alloc_next(exe, &e))
					return (0);
			exe->cmds[e.y]->raw = \
				ft_strjoin(exe->cmds[e.y]->raw, &raw[e.x], LEFT, 1);
			if (!exe->cmds[e.y]->raw)
				return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
			e.x++;
		}
		else if (!quote_divide(raw, exe, &e))
			return (0);
	}
	return (1);
}
