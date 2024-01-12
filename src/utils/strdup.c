/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:47:42 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:47:45 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char			*result;
	const size_t	len = ft_strlen(s);
	size_t			cursor;

	if (len < n)
		result = malloc(len + 1);
	else
		result = malloc(n + 1);
	cursor = 0;
	if (!result)
		return (NULL);
	while (cursor < len && cursor < n)
	{
		*(result + cursor) = *(s + cursor);
		cursor++;
	}
	*(result + cursor) = '\0';
	return (result);
}

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
