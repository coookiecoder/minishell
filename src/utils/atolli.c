/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   atolli.c                                           :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/27 14:27:03 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	atolli(char *number)
{
	unsigned long long int	result;
	int						sign;

	if (ft_strlen(number) > 19)
		return (-1);
	result = 0;
	sign = 1;
	if (*number == '+')
		number++;
	else if (*number == '-')
	{
		number++;
		sign = -1;
	}
	while (*number)
	{
		result = (result * 10) + (*(number++) - '0');
	}
	if (result > LLONG_MAX)
		return (-1);
	return (((long long int) result) * sign % 256);
}