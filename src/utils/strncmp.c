/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:48:04 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:48:07 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, int len)
{
	int	cursor;

	cursor = 0;
	if (!s1 || !s2)
		return (1);
	while (*(s1 + cursor) && *(s2 + cursor) && cursor < len)
	{
		if (*(s1 + cursor) != *(s2 + cursor))
			return (*(s1 + cursor) - *(s2 + cursor));
		cursor++;
	}
	if (cursor < len)
		return (*(s1 + cursor) - *(s2 + cursor));
	return (0);
}
