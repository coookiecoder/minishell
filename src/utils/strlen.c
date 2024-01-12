/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:47:58 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:48:00 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *str)
{
	int	a;

	a = 0;
	while (str && *(str + a))
		a++;
	return (a);
}

int	ft_strclen(const char *str, const char stop)
{
	int	a;

	a = 0;
	while (str && *(str + a) && *(str + a) != stop)
		a++;
	return (a);
}
