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

char	*ft_strdup(const char *s)
{
	char	*result;
	int		len;
	int		cursor;

	len = ft_strlen(s);
	result = malloc(len + 1);
	cursor = 0;
	if (!result)
		return (NULL);
	while (cursor < len)
	{
		*(result + cursor) = *(s + cursor);
		cursor++;
	}
	*(result + cursor) = '\0';
	return (result);
}
