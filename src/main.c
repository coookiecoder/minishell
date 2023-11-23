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
#include <stdio.h>

int	main(int argc, char **argv, const char **envp)
{
	char	*buffer;
	t_shell	shell;

	(void) argc;
	(void) argv;
	load_env(&shell, envp);
	while (1)
	{
		buffer = readline("hello there UwU : ");
		if (!buffer || !ft_strncmp(buffer, "exit", 5))
			break ;
		if (!ft_strncmp(buffer, "pwd ", 4) || !ft_strncmp(buffer, "pwd", 4))
			pwd(shell.env);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	unload_env(&shell);
	return (0);
}
