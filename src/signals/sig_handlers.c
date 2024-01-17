/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:37:01 by aurban            #+#    #+#             */
/*   Updated: 2024/01/17 16:08:21 by aurban           ###   ########.fr       */
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
	struct sigaction	sa;

	sa.sa_handler = our_sig_handl;
	sa.sa_sigaction = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(EOF, &sa, NULL);
}