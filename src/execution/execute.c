/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:39:33 by aurban            #+#    #+#             */
/*   Updated: 2024/01/20 15:41:44 by aurban           ###   ########.fr       */
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

static void	close_all_pipes(t_s_token *node)
{
	while (node)
	{
		if (node->token_type == TK_OP && (node->data.op.type >= \
			PIPE && node->data.op.type < REDIR_HEREDOC))
		{
			close(node->data.op.pipefd[0]);
			close(node->data.op.pipefd[1]);
		}
		node = get_next_node(node);
	}
}

static int execution_loop(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	int i = 0;
	while (node)
	{
		i++;
		#ifdef DEBUG
			printf("Executing node %d: %p\n", i, node);
		#endif
		if (node->token_type == TK_CMD)
		{
			printf("\tExecuting  ");fflush(stdout);
			if (execute_command(shell_data, node))
			{
				printf(CMD_ERROR_EXEC_MSG);
				close_all_pipes(node);
				return (CMD_ERROR_EXEC);
			}
			#ifdef DEBUG
				printf("Done\n");
			#endif
		}
		node = get_next_node(node);
	}
	#ifdef DEBUG
		printf("Execution loop done\n");
	#endif
	return (SUCCESS);
}

int	execute_commands(t_shell_data *shell_data)
{
	if (setup_pipes(shell_data))
		return (PIPE_ERROR);
	if (execution_loop(shell_data))
		return (EXECTION_ERROR);
	return (SUCCESS);
}
