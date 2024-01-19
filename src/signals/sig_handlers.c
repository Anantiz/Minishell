/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:37:01 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 18:56:45 by aurban           ###   ########.fr       */
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
	our_g_sig = sig;
	ft_putstr_fd("our_g_sig = ", 2);
	ft_putnbr_fd(our_g_sig, 2);
	ft_putstr_fd("\n", 2);
}

/*
	SIGINT: Ctrl + C
		- Display new prompt
	SIGQUIT: Ctrl + \
		- Do nothing
*/
void	register_signals(void)
{
	signal(SIGINT, our_sig_handl);
	signal(SIGQUIT, our_sig_handl);
}
