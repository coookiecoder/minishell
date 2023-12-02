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
		if (!e.quote && *(target + (*skipped)++) == ' ')
			break ;
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
	return (e.tmp);
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
	return (free(tmp), skipped);
}

static
int	editor_mode(const char *eof, int *fd)
{
	char	*tmp;
	char	*input;
	int		skipped;

	skipped = 0;
	tmp = get_entry(eof, &skipped);
	if (!tmp)
		return (-100);
	*fd = open("/tmp/.msdump", WF | O_TRUNC, 0755);
	if (*fd < 0)
		return (free(tmp), -100);
	input = get_next_line(0);
	while (input)
	{
		printf("EOF:   [%s]\nINPUT: [%s]\n", tmp, input);
		if (!ft_strncmp(input, tmp, ft_strlen(tmp)))
			break ;
		write(*fd, input, ft_strlen(input));
		free(input);
		input = get_next_line(0);
	}
	free(input);
	close(*fd);
	*fd = open("/tmp/.msdump", O_RDONLY);
	if (*fd < 0)
		return (free(tmp), -100);
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
