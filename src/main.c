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

int	main(int argc, char **argv, const char **envp)
{
	char		*buffer;
	t_shell		shell;

	load_env(&shell, envp);
	(void) argc;
	(void) argv;
	while (1)
	{
		buffer = readline("hello there UwU : ");
		if (!buffer)
			return (ft_exit(buffer, &shell, NULL));
		if (raw_parse(&shell, buffer))
			return (ft_exit(buffer, &shell, NULL));
		free(buffer);
	}
}
