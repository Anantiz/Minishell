/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:37:01 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 13:21:27 by aurban           ###   ########.fr       */
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
	g_sig = sig;
}

/*
	EOF	: Ctrl + D
		- Exit minishell
	SIGINT: Ctrl + C
		- Display new prompt
	SIGQUIT: Ctrl + \
		- Do nothing
*/
void	register_signals(void)
{
	signal(EOF, our_sig_handl);
	signal(SIGINT, our_sig_handl);
	signal(SIGQUIT, our_sig_handl);
}
