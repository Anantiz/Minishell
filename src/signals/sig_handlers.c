/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:37:01 by aurban            #+#    #+#             */
/*   Updated: 2024/02/07 10:40:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Signals have to be implemted if shell is in "interactive mode"
	whatever that means
*/

/* Relay signal value into our sig */
static void	our_sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_our_sig = sig;
	replace_signals();
}

static void	our_sig_handl2(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit\n", 5);
	else
		write(1, "\n", 1);
	g_our_sig = sig;
	replace_signals_2();
}

void	replace_signals(void)
{
	signal(SIGINT, our_sig_handl);
	signal(SIGQUIT, our_sig_handl);
}

void	replace_signals_2(void)
{
	signal(SIGINT, our_sig_handl2);
	signal(SIGQUIT, our_sig_handl2);
}
