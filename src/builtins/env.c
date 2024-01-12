/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:44:58 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:45:00 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_shell *shell)
{
	int	cursor;

	cursor = 0;
	while (*(shell->env + cursor))
	{
		write(1, *(shell->env + cursor), ft_strlen(*(shell->env + cursor)));
		write(1, "\n", 1);
		cursor++;
	}
	return (0);
}
