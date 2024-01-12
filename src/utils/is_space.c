/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:49:04 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:49:05 by abareux          ###   ########.fr       */
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
