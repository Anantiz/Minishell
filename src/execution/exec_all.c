/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:39:33 by aurban            #+#    #+#             */
/*   Updated: 2024/02/06 12:13:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
	Searches for the next logical operator starting from the last executed node
*/
static t_s_token	*chek_logical_op(t_shell_data *shell_data, t_s_token *node)
{
	node = get_next_logical_op(node);
	ft_fprintf(2, "\033[34mNext logical op: %p\033[0m\n", node);
	if (!node)
	{
		ft_fprintf(2, "\033[31mNo more logical operators\033[0m\n");
		return (NULL);
	}
	ft_fprintf(2, "\t\033[34mDid_exec: %d\033[0m\n", node->data.op.did_exec);
	if (node->token_type == TK_OP && node->data.op.type == T_AND)
	{
		node->data.op.did_exec = true;
		if (shell_data->last_wstatus == 0)
			return (node->right);
		else
		{
			shell_data->last_wstatus = -1;
			return (chek_logical_op(shell_data, node));
		}
	}
	else if (node->token_type == TK_OP && node->data.op.type == T_OR)
	{
		node->data.op.did_exec = true;
		if (shell_data->last_wstatus != 0)
			return (node->right);
		else
			return (chek_logical_op(shell_data, node));
	}
	return (node);
}

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

/*
	Returns the last node executed
*/
static t_s_token	*exec_subtree(t_shell_data *shell_data, t_s_token *node, int *debug_i)
{
	t_s_token	*prev_node;

	while (node)
	{
		if (node->token_type == TK_CMD)
		{
			ft_fprintf(2, "Executing node %d: %s: %p\n", *debug_i, node->data.cmd.args[0], node);
			ft_fprintf(2, "\tredir[0]: %p\n",node->data.cmd.redir_nodes[0]);
			ft_fprintf(2, "\tredir[1]: %p\n\n", node->data.cmd.redir_nodes[1]);
			exec_one_command(shell_data, node);
			shell_data->last_command = &node->data.cmd;
			restore_std_streams(shell_data);
		}
		(*debug_i)++;
		prev_node = node;
		node = get_next_node_no_op(node);
		ft_fprintf(2, "\t\033[34mNext node: %p\033[0m\n", node);
	}
	return (prev_node);
}

static int exec_commands(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	int debug_i = 0;
	while (node)
	{
		while (node && node->token_type == TK_OP && node->data.op.type < PIPE)
		{
			if (node->data.op.did_exec == false)
			{
				node->data.op.did_exec = true;
				node = node->left;
			}
			else
				node = node->right;
		}
		node = exec_subtree(shell_data, node, &debug_i);
		wait_last_subtree(shell_data);
		ft_fprintf(2, "\t\033[34mLast status: %d\033[0m\n", shell_data->last_wstatus);
		restore_std_streams(NULL);
		node = chek_logical_op(shell_data, node);
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
	return (SUCCESS);
}
