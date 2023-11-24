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

void	init_command(t_command *command)
{
	int	cursor;

	cursor = 0;
	command->argv = NULL;
	command->argc = 0;
	while (cursor < PATH_MAX)
		*(command->bin + cursor++) = '\0';
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
		format_command(buffer, &command);
		make_command(command, &shell);
		free(buffer);
	}
}
