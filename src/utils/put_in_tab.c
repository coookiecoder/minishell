/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <abareux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:27:11 by abareux           #+#    #+#             */
/*   Updated: 2024/01/19 15:27:14 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_in_tab(char *destination, const char *source)
{
	while (*source)
		*destination++ = *source++;
	*destination = *source;
}
