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

static
int	cmd_parse(t_shell *sh, t_command *cmd, t_exec *exe, size_t pos)
{
	char	*parsed;

	parsed = expension(sh, cmd->raw);
	if (!parsed)
		return (write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
	parsed = redirection_handler(parsed, cmd);
	if (g_sig == EXIT)
		return (free(parsed), g_sig = NORMAL, 0);
	if (!parsed)
		return (free(parsed), write(2, ERR_PIPES_FILE, ERR_PIPES_FILE_N), 0);
	format_command(parsed, cmd);
	*(cmd->argv) = malloc(PATH_MAX);
	if (!*(cmd->argv))
		return (free(parsed), \
			write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
	getcwd(*(cmd->argv), PATH_MAX);
	if (!cmd->argv)
		return (free(parsed), \
			write(2, ERR_PARSE_MEMORY, ERR_PARSE_MEMORY_N), 0);
	if (!strncmp(cmd->bin, "exit", 5))
		return (free(parsed), sh->exit = convert_code(cmd->argv[1]), \
			exe->total == 1);
	make_command(*cmd, sh, exe, pos);
	return (free(parsed), 0);
}

int	raw_parse(t_shell *sh, char *raw)
{
	t_exec		exe;
	size_t		i;

	exe = (t_exec){0, NULL, {-1, -1}, {-1, -1}};
	if (!token_parse(&exe, raw))
		return (ft_freeexec(&exe), 0);
	for (int i = 0; exe.cmds[i]; i++)
		printf("CMD: [%s]\n", exe.cmds[i]->raw);
	i = 0;
	while (i < exe.total)
	{
		if (cmd_parse(sh, exe.cmds[i], &exe, i))
			return (ft_freeexec(&exe), 1);
		i++;
	}
	ft_freeexec(&exe);
	return (0);
}
