/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:39:33 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 14:21:55 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
About Finding the Different subtrees
	Take the first subtree to do, For this just spam left until
	no more logical Op.

	That's for doing a subtree

	You shall recursivly call the function to do a subtree in
	the logical op supertree (All logical ops will be on top of the
	tree, so we can think of it as a supertree that guides towards subtrees)

	Protocol will be:

		If there is no TOP-level logical op, just call subtree and call it a day.

// ft_fprintf(2, "Executing node : %s: %p\n", node->data.cmd.args[0], node);
// ft_fprintf(2, "\tredir[0]: %p\n",node->data.cmd.redir_nodes[0]);
// ft_fprintf(2, "\tredir[1]: %p\n\n", node->data.cmd.redir_nodes[1]);
*/

/*
	Returns the last node executed
*/
static int	exec_subtree(t_shell_data *shell_data, t_s_token *node)
{
	while (node)
	{
		if (node->token_type == TK_CMD)
		{
			exec_one_command(shell_data, node);
			shell_data->last_command = &node->data.cmd;
			restore_std_streams(shell_data);
		}
		node = get_next_node_no_op(node);
	}
	wait_last_subtree(shell_data);
	return (shell_data->last_wstatus);
}

/*
	Recursively calls itself to execute the subtrees
	Use the return value to know if we should execute the right subtree
*/
int	super_tree(t_shell_data *shell_data, t_s_token *node)
{
	int	ret;

	if (is_logop(node))
	{
		node->data.op.did_exec = true;
		ret = super_tree(shell_data, node->left);
		if (node->data.op.type == T_AND && ret == 0)
			ret = super_tree(shell_data, node->right);
		else if (node->data.op.type == T_OR && ret != 0)
			ret = super_tree(shell_data, node->right);
	}
	else
		ret = exec_subtree(shell_data, node);
	restore_std_streams(NULL);
	return (ret);
}

// Returning an error is useless because they are already handled
int	exec_tree(t_shell_data *shell_data)
{
	if (pre_init(shell_data))
		return (SUCCESS);
	shell_data->skip = 0;
	shell_data->pid_list = our_malloc(shell_data->cmd_count * sizeof(int));
	ft_memset_int(shell_data->pid_list, -69, shell_data->cmd_count);
	super_tree(shell_data, shell_data->root);
	shell_data->last_wstatus = 0;
	shell_data->last_command = NULL;
	our_free(shell_data->pid_list);
	rl_on_new_line();
	return (SUCCESS);
}
