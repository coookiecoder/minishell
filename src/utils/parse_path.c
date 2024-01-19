/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <abareux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:25:27 by abareux           #+#    #+#             */
/*   Updated: 2024/01/16 16:27:56 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_path_absolute(char *command)
{
	t_list	*old_path;
	t_list	*element_command;
	t_list	*element;

	old_path = 0;
	element_command = create(ft_split(command, '/'));
	element = element_command;
	while (element)
	{
		if (!ft_strncmp(element->data, "..", 3))
		{
			if (old_path && !old_path->next)
			{
				pop(old_path);
				old_path = 0;
			}
			else if (old_path)
				pop(old_path);
		}
		else if (ft_strncmp(element->data, ".", 2))
			add(&old_path, element->data);
		element = element->next;
	}
	clear(element_command);
	return (join(old_path));
}

char	*parse_path_relative(t_shell *shell, char *command)
{
	t_list	*old_path;
	t_list	*element_command;
	t_list	*element;

	old_path = create(ft_split(shell->pwd, '/'));
	element_command = create(ft_split(command, '/'));
	element = element_command;
	while (element)
	{
		if (!ft_strncmp(element->data, "..", 3))
		{
			if (old_path && !old_path->next)
			{
				pop(old_path);
				old_path = 0;
			}
			else if (old_path)
				pop(old_path);
		}
		else if (ft_strncmp(element->data, ".", 2))
			add(&old_path, element->data);
		element = element->next;
	}
	clear(element_command);
	return (join(old_path));
}
