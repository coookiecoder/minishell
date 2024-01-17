/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <abareux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:18:29 by abareux           #+#    #+#             */
/*   Updated: 2024/01/16 16:23:51 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i < dstsize - 1 && dstsize > 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

static
void	**ft_free_array(void **array, size_t n)
{
	while (n)
		free(array[--n]);
	free(array);
	return (0);
}

static
size_t	ft_split_size(const char *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (s[i++])
	{
		while (s[i] != c && s[i])
			i++;
		len++;
		while (s[i] == c && s[i])
			i++;
	}
	return (len);
}

static
char	**ft_split2(const char *s, char c, char **res)
{
	size_t	len;
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	while (s[y])
	{
		len = 0;
		while (s[y] != c && s[y] && ++y)
			len++;
		res[i] = malloc(len + 1);
		if (!res[i])
			return ((char **) ft_free_array((void **) res, i));
		ft_strlcpy(res[i++], &s[y - len], len + 1);
		while (s[y] == c && s[y])
			y++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	char	**r;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == c && s[i])
		i++;
	r = (char **)malloc(sizeof(char *) * (ft_split_size(&s[i], c) + 1));
	if (!r)
		return (0);
	return (ft_split2(&s[i], c, r));
}
