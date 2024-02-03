/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:37:01 by aurban            #+#    #+#             */
/*   Updated: 2024/02/03 11:41:15 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Signals have to be implemted if shell is in "interactive mode"
	whatever that means
*/

/* Relay signal value into our sig */
void	our_sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "^C", 2);
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_our_sig = sig;
	replace_signals();
}

void	replace_signals(void)
{
	signal(SIGINT, our_sig_handl);
	signal(SIGQUIT, our_sig_handl);
}
