/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <abareux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:18:39 by abareux           #+#    #+#             */
/*   Updated: 2024/01/26 16:26:22 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_bin(char c, enum e_quotetype *quote)
{
	assign_quote_value(quote, c);
	if (*quote == NO_QUOTE && c == ' ')
		return (0);
	return (1);
}
