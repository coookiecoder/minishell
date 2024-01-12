/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:46:55 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:46:59 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define WF 65

static
char	*get_entry(const char *target, int *skipped)
{
	t__exp	e;

	e = (t__exp){NO_QUOTE, NULL, 0, 0};
	while (ft_is_space(*(target + *skipped)) && *(target + *skipped))
		(*skipped)++;
	while (*(target + *skipped))
	{
		assign_quote_value(&e.quote, *(target + *skipped));
		if (!e.quote && *(target + *skipped) == ' ')
			break ;
		(*skipped)++;
		e.x++;
	}
	e.tmp = malloc(e.x + 1);
	if (!e.tmp)
		return (NULL);
	while (e.y < e.x)
	{
		*(e.tmp + e.y) = *(target + e.y + (*skipped - e.x));
		e.y++;
	}
	*(e.tmp + e.y) = '\0';
	return (purge_quote(e.tmp));
}

static
int	open_target(const char *target, int *fd, int mode)
{
	char	*tmp;
	int		skipped;

	skipped = 0;
	tmp = get_entry(target, &skipped);
	if (!tmp)
		return (-100);
	*fd = open(tmp, mode, 0755);
	if (*fd < 0)
		return (free(tmp), -100);
	while (target[skipped] == ' ' \
		|| (target[skipped] >= '\t' && target[skipped] <= '\r'))
		skipped++;
	return (free(tmp), skipped);
}

static
void	edit(const char *eof, int out)
{
	pid_t	pid;
	char	*input;

	g_sig = EDITMODE;
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, signal_breakout);
		signal(SIGQUIT, signal_breakout);
		while (1)
		{
			input = readline("> ");
			if (!input)
				write(1, WARN_PIPES_TEMP, WARN_PIPES_TEMP_N);
			if (!input || !ft_strncmp(input, eof, ft_strlen(eof) + 1))
				break ;
			write(out, input, ft_strlen(input));
			write(out, "\n", 1);
			free(input);
		}
		g_sig = NORMAL;
		exit(0);
	}
	waitpid(-1, NULL, 0);
	return ;
}

static
int	editor_mode(const char *eof, int *fd)
{
	char	*tmp;
	int		skipped;

	skipped = 0;
	tmp = ft_strjoin(get_entry(eof, &skipped), "", LEFT, 1);
	if (!tmp)
		return (-100);
	*fd = open("/tmp/.msdump", WF | O_TRUNC, 0755);
	if (*fd < 0)
		return (free(tmp), -100);
	edit(tmp, *fd);
	close(*fd);
	*fd = open("/tmp/.msdump", O_RDONLY);
	if (*fd < 0)
		return (free(tmp), -100);
	while (eof[skipped] == ' ' \
		|| (eof[skipped] >= '\t' && eof[skipped] <= '\r'))
		skipped++;
	return (free(tmp), skipped);
}

char	*redirection_handler(char *raw, t_command *cmd)
{
	t__exp	e;

	e = (t__exp){NO_QUOTE, ft_strdup(""), 0, 0};
	if (!raw || !e.tmp)
		return (free(raw), free(e.tmp), NULL);
	while (raw[e.x])
	{
		e.y = 1;
		assign_quote_value(&e.quote, raw[e.x]);
		if (e.quote == NO_QUOTE && raw[e.x] == '>' && raw[e.x + 1] == '>')
			e.y = open_target(&raw[e.x + 2], &cmd->fd_out, WF | O_APPEND) + 2;
		else if (e.quote == NO_QUOTE && raw[e.x] == '>')
			e.y = open_target(&raw[e.x + 1], &cmd->fd_out, WF | O_TRUNC) + 1;
		else if (e.quote == NO_QUOTE && raw[e.x] == '<' && raw[e.x + 1] == '<')
			e.y = editor_mode(&raw[e.x + 2], &cmd->fd_in) + 2;
		else if (e.quote == NO_QUOTE && raw[e.x] == '<')
			e.y = open_target(&raw[e.x + 1], &cmd->fd_in, O_RDONLY) + 1;
		else
			e.tmp = ft_strjoin(e.tmp, &raw[e.x], LEFT, 1);
		if (e.y < 0 || !e.tmp)
			return (free(raw), free(e.tmp), NULL);
		e.x += e.y;
	}
	return (free(raw), e.tmp);
}
