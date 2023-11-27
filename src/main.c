/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/27 14:19:50 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	init_command(t_command *command)
{
	int	cursor;

	cursor = 0;
	command->argv = NULL;
	command->argc = 0;
	while (cursor < PATH_MAX)
		*(command->bin + cursor++) = '\0';
}

static
void	ft_free(char *buffer, t_shell *shell, t_command *command)
{
	int	cursor;

	free(buffer);
	cursor = 0;
	while (*(shell->env + cursor))
		free(*(shell->env + cursor++));
	free(shell->env);
	cursor = 1;
	while (cursor < command->argc)
		free (*(command->argv + cursor++));
	free(command->argv);
}

int	main(int argc, char **argv, const char **envp)
{
	int			code;
	char		*buffer;
	t_shell		shell;
	t_command	command;

	(void) argc;
	(void) argv;
	load_env(&shell, envp);
	init_command(&command);
	while (1)
	{
		buffer = readline("hello there UwU : ");
		format_command(buffer, &command);
		if (!strncmp(command.bin, "exit", 5) && command.argc > 1)
			code = convert_code(*(command.argv + 1));
		if (!strncmp(command.bin, "exit", 5) && command.argc > 1)
			return (ft_free(buffer, &shell, &command), code);
		if (!strncmp(command.bin, "exit", 5) && command.argc == 1)
			write(1, "exit\n", 5);
		if (!strncmp(command.bin, "exit", 5) && command.argc == 1)
			return (ft_free(buffer, &shell, &command), 0);
		make_command(command, &shell);
		free(buffer);
	}
}
