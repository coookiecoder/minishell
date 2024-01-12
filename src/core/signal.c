/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:47:04 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 11:48:48 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	ctrl_c(void)
{
	write(0, "\n", 1);
	if (g_sig)
		return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static
void	ctrl_s(void)
{
	if (g_sig)
	{
		write(1, "Quit\n", 5);
		return ;
	}
	write(0, "\033[D\033[D\033[K", 9);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(int sig)
{
	if (g_sig == EXECUTION)
	{
		signal_breakout(sig);
		return ;
	}
	if (g_sig == EDITMODE || g_sig == EXIT)
	{
		if (sig == SIGINT)
			g_sig = EXIT;
		return ;
	}
	if (sig == SIGINT)
		ctrl_c();
	else if (sig == SIGQUIT)
		ctrl_s();
}

void	signal_breakout(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		write(0, "\033[D\033[D\033[K", 9);
		rl_on_new_line();
		rl_redisplay();
	}
}
