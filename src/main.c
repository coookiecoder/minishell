/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/29 10:20:49 by abareux          ###   ########.fr       */
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
	if (buffer)
		free(buffer);
	unload_env(shell);
	cursor = 1;
	while (cursor < command->argc)
		free (*(command->argv + cursor++));
	free(command->argv);
}

static
int	ft_exit(char *buffer, t_shell *shell, t_command *command)
{
	int	code;

	if (command->argc > 1 && buffer)
	{
		code = convert_code(*(command->argv + 1));
		return (ft_free(buffer, shell, command), code);
	}
	write(1, "exit\n", 5);
	return (ft_free(buffer, shell, command), 0);
}

int	main(int argc, char **argv, const char **envp)
{
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
		if (!buffer)
			return (ft_exit(buffer, &shell, &command));
		format_command(buffer, &command);
		if (!strncmp(command.bin, "exit", 5))
			return (ft_exit(buffer, &shell, &command));
		make_command(command, &shell);
		free(buffer);
	}
}
