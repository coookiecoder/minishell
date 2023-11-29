/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/29 10:44:12 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	find_egal(char *string)
{
	int	cursor;

	cursor = 0;
	while (*(string + cursor))
	{
		if (*(string + cursor) == '=' && *(string + cursor + 1) != '\0')
			return (1);
		cursor++;
	}
	return (0);
}

int	export(char **buffer, t_command command, int *crs)
{
	int	crs_c;
	int	crs_v;

	crs_c = 1;
	while (crs_c < command.argc)
	{
		*(buffer + *crs) = malloc(ft_strlen(*(command.argv + crs_c)) + 1);
		if (!*(buffer + *crs))
			return (1);
		if (!find_egal(*(command.argv + crs_c)))
			return (1);
		crs_v = 0;
		while (*(*(command.argv + crs_c) + crs_v))
		{
			*(*(buffer + *crs) + crs_v) = *(*(command.argv + crs_c) + crs_v);
			crs_v++;
		}
		*(*(buffer + *crs) + crs_v) = '\0';
		crs_c++;
		(*crs)++;
	}
	return (0);
}
