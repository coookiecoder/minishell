/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:45:26 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:45:28 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	keep_env(char *env, t_command cmd)
{
	int	crs;

	crs = 1;
	while (crs < cmd.argc)
	{
		if (!strncmp(env, *(cmd.argv + crs), ft_strlen(*(cmd.argv + crs))))
			return (free(env), 0);
		crs++;
	}
	return (1);
}
