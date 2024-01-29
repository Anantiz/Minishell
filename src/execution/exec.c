/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:39:33 by aurban            #+#    #+#             */
/*   Updated: 2024/01/26 14:28:47 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	TO DO:
		-HANDLE LOGICAL OPERATORS USING RETURN VALUES
*/

/*
	Protocol:
		-1: Init all pipes
		Loop:
			-2: Execute commands (Monitor global signal and send to childs)
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

static int exec_commands(t_shell_data *shell_data)
{
	t_s_token	*node;
	int			ret;

	node = shell_data->root;
	int i = 0;
	while (node)
	{
		if (node->token_type == TK_OP)
		{
			if (node->data.op.type == T_AND)
			{
				if (shell_data->last_wstatus)
				{
					// Don't execute this subtree
					// Jump to the next subtree (T_AND or T_OR)
					// node = get_next_subtree(node);
				}
			}
			else if (node->data.op.type = T_OR)
			{
				if (!shell_data->last_wstatus)
				{
					// Don't execute this subtree
					// Jump to the next subtree (T_AND or T_OR)
					// node = get_next_subtree(node);
				}
			}
		}
		else if (node->token_type == TK_CMD)
		{
			ft_fprintf(2, "Executing node %d: %p\n", i, node);
			shell_data->last_command = &node->data.cmd;
			ret = exec_one_command(shell_data, node);
			if (ret)
			{
				ft_fprintf(2, "Error `%s`: %d\n", *node->data.cmd.args, i);
			}
			restore_std_streams(NULL);
		}
		node = get_next_node(node);
		i++;
		fflush(NULL);
	}
	waitpid(shell_data->last_pid, NULL, 0);
	ft_fprintf(2, "\nExecution loop done\n\n");
	return (SUCCESS);
}

int	exec_tree(t_shell_data *shell_data)
{
	if (init_pipes(shell_data))
		return (PIPE_ERROR);
	if (exec_commands(shell_data))
		return (EXECTION_ERROR);
	restore_std_streams(NULL);
	return (SUCCESS);
}
