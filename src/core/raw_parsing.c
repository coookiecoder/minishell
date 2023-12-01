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
#define ERR_PARSE_MEMORY "Parsing Error: Memory allocation failed\n"
#define ERR_PARSE_MEMORY_N 40

static
void	init_command(t_command *command)
{
	int	cursor;

	cursor = 0;
	command->argv = NULL;
	command->argc = 1;
	while (cursor < PATH_MAX)
		*(command->bin + cursor++) = '\0';
}

static
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
int	apply_expension(t_shell *sh, char **base, char *raw)
{
	int		len;
	char	*env;
	char	*val;

	len = 0;
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

	e = (t__exp){NO_QUOTE, ft_strdup(""), 0};
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

int	raw_parse(t_shell *sh, char *raw)
{
	t_command	command;
	char		*parsed;

	parsed = expension(sh, raw);
	if (!parsed)
		return (write(1, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 1);
	init_command(&command);
	format_command(parsed, &command);
	if (!command.argv)
		return (free(parsed), \
			write(1, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 1);
	if (!strncmp(command.bin, "exit", 5))
		return (free(parsed), ft_freecmd(&command), 1);
	make_command(command, sh);
	return (free(parsed), ft_freecmd(&command), 0);
}
