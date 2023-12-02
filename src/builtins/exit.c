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

	if (!code)
		return (0);
	cursor = 0;
	while (is_allowed(*(code + cursor)))
		cursor++;
	if (*(code + cursor) == '\0')
		code_int = atolli(code);
	else
		code_int = -1;
	if (code_int == -1)
	{
		write(1, "bash: exit: ", 13);
		write(1, code, ft_strlen(code));
		write(1, ": numeric argument required\n", 29);
		code_int = 2;
	}
	return (code_int);
}
