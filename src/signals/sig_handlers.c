/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:37:01 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 11:28:49 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int sigaction \
	(int signum, const struct sigaction *act, struct sigaction *oldact);

struct sigaction {
    void (*sa_handler)(int);          // Pointer to the signal handling function
    void (*sa_sigaction)(int, siginfo_t *, void *);  // Pointer to an alternative signal handling function
    sigset_t sa_mask;                 // Additional set of signals to be blocked during execution of the signal handling function
    int sa_flags;                     // Flags specifying the behavior of the signal
    void (*sa_restorer)(void);        // Deprecated, not used in modern systems
};

*/

/* Relay signal value into our sig */
static void	our_sig_handl(int sig)
{
	g_sig = sig;
}


/*
	SIGINT
	EOF
*/
void	register_signals(void)
{
	signal(EOF, our_sig_handl);
	signal(SIGINT, our_sig_handl);
}
