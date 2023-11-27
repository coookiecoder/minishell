/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/27 14:22:44 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	is_allowed(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	convert_code(char *code)
{
	int	code_int;
	int	cursor;

	cursor = 0;
	while (is_allowed(*(code + cursor)))
		cursor++;
	if (*(code + cursor) == '\0')
		code_int = atolli(code);
	else
		code_int = -1;
	write(1, "exit\n", 5);
	if (code_int == -1)
	{
		write(1, "bash: exit: ", 13);
		write(1, code, ft_strlen(code));
		write(1, ": numeric argument required\n", 29);
		code_int = 0;
	}
	return (code_int);
}
