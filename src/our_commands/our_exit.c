/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:07:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 17:02:48 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token(t_s_token *token)
{
	(void)token;
	/* To do */
}

/*
	Cannot explicitly free everything if the call comes from a signal
	If the evaluator says that "Still reachable" is a leak he can fuck off
*/
int	our_exit(t_shell_data *shell_data, t_s_token *token)
{
	int status;

	if (token)
	{
		status = ft_atoi(token->data.cmd.args[1]);
		// Free token
		if (!shell_data)
			free_token(token);
	}
	else
		status = 0;
	if (shell_data)
		cleanup_shell_data(shell_data);
	ft_putendl_fd("exit", 1);
	safe_as_fuck_malloc(0, NULL, SAFE_MALLOC_FREE_ALL);
	exit(status);
}
