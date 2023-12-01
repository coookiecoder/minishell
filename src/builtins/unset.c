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

int	keep_env(char *env, t_command cmd)
{
	int	crs;

	crs = 1;
	while (crs < cmd.argc)
	{
		if (!strncmp(env, *(cmd.argv + crs), ft_strlen(*(cmd.argv + crs))))
			return (free(env), 0);
		crs++;
	}
	return (1);
}
