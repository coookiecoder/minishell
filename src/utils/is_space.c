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

int	ft_is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c >= '\t' && c <= '\r')
		return (1);
	return (0);
}

int	is_empty(const char *buffer)
{
	int		i;

	i = 0;
	while (ft_is_space(buffer[i]))
		i++;
	if (i == ft_strlen(buffer))
		return (1);
	return (0);
}
