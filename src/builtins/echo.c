/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/27 12:27:17 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(int argc, char **argv)
{
	int	argv_cursor;

	argv_cursor = 1;
	if (argc != 1 && !ft_strncmp(*(argv + 1), "-n", 3))
		argv_cursor++;
	while (argv_cursor < argc)
	{
        write(1, *(argv + argv_cursor), ft_strlen(*(argv + argv_cursor)));
		argv_cursor++;
		if (argv_cursor < argc)
			write(1, " ", 1);
	}
	if (argc == 1 || ft_strncmp(*(argv + 1), "-n", 3))
		write(1, "\n", 1);
	return (0);
}
