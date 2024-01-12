/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:45:18 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 09:45:20 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX - 1);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (0);
}
