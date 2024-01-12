/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:47:04 by abareux           #+#    #+#             */
/*   Updated: 2024/01/12 12:45:20 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_code(int sig, t_shell *save)
{
	static t_shell		*sh = NULL;

	if (save)
		sh = save;
	else
		sh->last_code = 128 + sig;
}

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
		signal_breakout(sig);
	else if (g_sig == EDITMODE || g_sig == EXIT)
	{
		if (sig == SIGINT)
			g_sig = EXIT;
	}
	else if (sig == SIGINT)
		ctrl_c();
	else if (sig == SIGQUIT)
		ctrl_s();
	if (sig == SIGINT)
		set_code(sig, NULL);
}

void	signal_breakout(int sig)
{
	g_sig = HANDLED;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		ctrl_s();
		set_code(sig, NULL);
	}
}
