/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:39:33 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 10:55:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Protocol:
		-1: Init all pipes
		Loop:
			-2: Execute commands  (Monitor global signal and send to children)
				-2.1: Handle redirections
				-2.2: try:
					-Execute from builtins
				else:
					-Execute from absolute path
				else:
					-Execute from path
				-2.3: Handle Errors
				-2.4: Close pipes
			done;
		-3: Cleanup and wait for next command-line
*/

static int execute_loop(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	while (node)
	{
		if (node->token_type == TK_CMD)
		{
			if (execute_command(shell_data, node))
			{
				printf(CMD_ERROR_EXEC_MSG);
				return (CMD_ERROR_EXEC);
			}
		}
		node = get_next_node(node);
	}
}

int	execute_commands(t_shell_data *shell_data)
{
	if (setup_pipes(shell_data))
		return (PIPE_ERROR);
	if (execute_loop(shell_data))
		return (EXECTION_ERROR);
	return (SUCCESS);
}
