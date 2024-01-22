/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:07:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 18:00:13 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Cannot explicitly free everything if the call comes from a signal
	If the evaluator says that "Still reachable" is a leak he can fuck off
*/
int	our_exit(t_shell_data *shell_data, t_s_token *token)
{
	int status;

	(void)shell_data;
	if (token)
		status = ft_atoi(token->data.cmd.args[1]);
	else
		status = 0;
	ft_putendl_fd("exit", 1);
	safe_as_fuck_malloc(0, NULL, SAFE_MALLOC_FREE_ALL);
	exit(status);
}
