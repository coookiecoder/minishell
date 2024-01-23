/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <abareux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:18:23 by abareux           #+#    #+#             */
/*   Updated: 2024/01/23 16:27:06 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*create(char **data)
{
	t_list	*result;
	t_list	*buffer;
	char	**start;

	if (!data || !*data)
		return (0);
	start = data;
	result = malloc(sizeof(t_list));
	buffer = result;
	while (*data)
	{
		if (!buffer)
			return (clear(result));
		buffer->data = ft_strdup(*data);
		free(*data);
		data++;
		if (*data)
		{
			buffer->next = malloc(sizeof(t_list));
			buffer = buffer->next;
		}
	}
	buffer->next = 0;
	return (free(start), result);
}

t_list	*clear(t_list *list)
{
	t_list	*buffer;

	buffer = list;
	while (list)
	{
		list = list->next;
		free(buffer->data);
		free(buffer);
		buffer = list;
	}
	return (0);
}

void	pop(t_list *list)
{
	while (list && list->next && list->next->next)
		list = list->next;
	if (list && list->next)
	{
		free(list->next->data);
		free(list->next);
		list->next = 0;
	}
	else if (list)
	{
		free(list->data);
		free(list);
	}
}

void	add(t_list **list, char *data)
{
	t_list	*buffer;

	buffer = *list;
	while (buffer && buffer->next)
		buffer = buffer->next;
	if (buffer)
	{
		buffer->next = malloc(sizeof(t_list));
		buffer = buffer->next;
	}
	else
	{
		buffer = malloc(sizeof(t_list));
		*list = buffer;
	}
	if (!buffer)
		return ;
	buffer->data = ft_strdup(data);
	buffer->next = 0;
}

char	*join(t_list *list)
{
	t_list	*buffer;
	char	*result;

	result = NULL;
	if (!list)
		return (ft_strdup("/"));
	buffer = list;
	while (list)
	{
		if (!result)
			result = ft_strdup("/");
		if (result)
			result = ft_strjoin(result, list->data, LEFT, -1);
		if (!result)
			return (0);
		if (list && list->next)
			result = ft_strjoin(result, "/", LEFT, -1);
		if (!result)
			return (0);
		list = list->next;
	}
	clear(buffer);
	return (result);
}
