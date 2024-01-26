/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:46:38 by abareux           #+#    #+#             */
/*   Updated: 2024/01/26 16:24:37 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	pipe_counter(char *raw);
int		execution_parse(t_exec *exe, char *raw);

void	init_command(t_command *command)
{
	int	cursor;

	cursor = 0;
	*command = (t_command){NULL, {'\0'}, 0, NULL, -1, -1};
	while (cursor < PATH_MAX)
		*(command->bin + cursor++) = '\0';
}

void	assign_quote_value(enum e_quotetype *v, char c)
{
	if (c == '\'' && *v == NO_QUOTE)
		*v = SINGLE_QUOTE;
	else if (c == '\"' && *v == NO_QUOTE)
		*v = DOUBLE_QUOTE;
	else if ((c == '\'' && *v == SINGLE_QUOTE) \
			|| (c == '\"' && *v == DOUBLE_QUOTE))
		*v = NO_QUOTE;
}

static
int	token_parse(t_exec *exe, char *raw)
{
	size_t	i;

	exe->total = pipe_counter(raw) + 1;
	exe->cmds = malloc(sizeof(void *) * (exe->total + 1));
	if (!exe->cmds)
		return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
	i = 0;
	while (i < exe->total + 1)
		exe->cmds[i++] = NULL;
	i = 0;
	while (i < exe->total)
	{
		exe->cmds[i] = malloc(sizeof(t_command));
		if (!exe->cmds[i])
			return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
		init_command(exe->cmds[i++]);
	}
	return (execution_parse(exe, raw));
}

int	cmd_parse(t_shell *sh, t_command *cmd)
{
	char	*parsed;

	parsed = expension(sh, cmd->raw);
	if (!parsed)
		return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 1);
	parsed = redirection_handler(parsed, cmd);
	if (g_sig == EXIT)
		return (free(parsed), g_sig = NORMAL, 1);
	if (!parsed)
		return (free(parsed), write(2, ERR_PIPES_FILE, ERR_PIPES_FILE_N), 1);
	format_command(parsed, cmd, NO_QUOTE);
	*(cmd->argv) = ft_strdup(cmd->bin);
	if (!*(cmd->argv))
		return (free(parsed), \
			write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 1);
	free(parsed);
	*(cmd->argv) = purge_quote(*(cmd->argv));
	if (!*(cmd->argv))
		return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 1);
	return (0);
}

int	raw_parse(t_shell *sh, char *raw)
{
	t_exec		exe;
	size_t		i;
	int			ret;

	exe = (t_exec){0, NULL, {-1, -1}, {-1, -1}};
	if (!token_parse(&exe, raw))
		return (ft_freeexec(&exe), 0);
	i = 0;
	while (i < exe.total)
	{
		if (cmd_parse(sh, exe.cmds[i]))
			return (ft_freeexec(&exe), 1);
		ret = 0;
		while (ret < 4096 && exe.cmds[i]->argv[0][ret])
		{
			exe.cmds[i]->bin[ret] = exe.cmds[i]->argv[0][ret];
			ret++;
		}
		exe.cmds[i]->bin[ret] = exe.cmds[i]->argv[0][ret];
		i++;
	}
	ret = cmd_exec(sh, &exe);
	ft_freeexec(&exe);
	return (ret);
}
