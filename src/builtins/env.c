/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/29 08:28:35 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_shell *shell)
{
	int	cursor;

	cursor = 0;
	while (*(shell->env + cursor))
	{
		write(1, *(shell->env + cursor), ft_strlen(*(shell->env + cursor)));
		write(1, "\n", 1);
		cursor++;
	}
	return (0);
}
