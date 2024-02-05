/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:39:33 by aurban            #+#    #+#             */
/*   Updated: 2024/02/05 19:06:48 by aurban           ###   ########.fr       */
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

static void	wait_last_subtree(t_shell_data *shell_data)
{
	static int	skip = 0;
	while (skip < shell_data->pid_count)
	{
		if (shell_data->pid_list[skip] != -69)
			waitpid(shell_data->pid_list[skip], NULL, 0);
		skip++;
	}
	if (skip == shell_data->cmd_count)
		skip = 0;
}

static int exec_commands(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	int i = 0;
	while (node)
	{
		while (node)
		{
			if (node->token_type == TK_OP)
			{
				ft_fprintf(2, "Executing node %d: %s: %p\tlast_status=%d\n", \
				i, node->data.op.type == T_AND ? "AND" : "OR", node, shell_data->last_wstatus);
				if (node->data.op.type == T_AND)
				{
					if (node->data.op.did_exec == true)
					{
						if (shell_data->last_wstatus != 0)
							node = get_next_subtree(shell_data);
					}
					else
						node->data.op.did_exec = true;
				}
				else if (node->data.op.type == T_OR)
				{
					if (node->data.op.did_exec == true)
					{
						if (shell_data->last_wstatus == 0)
							node = get_next_subtree(shell_data);
					}
					else
						node->data.op.did_exec = true;
				}
			}
			else if (node->token_type == TK_CMD)
			{
				ft_fprintf(2, "Executing node %d: %s: %p\n", i, node->data.cmd.args[0], node);
				ft_fprintf(2, "\tredir[0]: %p\n",node->data.cmd.redir_nodes[0]);
				ft_fprintf(2, "\tredir[1]: %p\n\n", node->data.cmd.redir_nodes[1]);
				exec_one_command(shell_data, node);
				shell_data->last_command = &node->data.cmd;
				restore_std_streams(shell_data);
			}
			node = get_next_node(node);
			i++;
		}
		wait_last_subtree(shell_data);
		node = get_next_subtree(shell_data);
	}
	return (SUCCESS);
}

// Returning an error is useless because they are already handled
int	exec_tree(t_shell_data *shell_data)
{
	if (pre_init(shell_data))
		return (SUCCESS);
	shell_data->pid_list = our_malloc(shell_data->cmd_count * sizeof(int));
	ft_memset_int(shell_data->pid_list, -69, shell_data->cmd_count);
	if (exec_commands(shell_data))
		return (SUCCESS);
	restore_std_streams(NULL);
	return (SUCCESS);
}
