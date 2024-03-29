/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_world_desert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:07:48 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 13:34:50 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_s_token	*lcl_get_first_redir_node(t_s_token *node, \
t_e_op_type og_type)
{
	t_s_token	*temp;
	t_s_token	*first_redir;

	if (!node)
		return (NULL);
	temp = node;
	first_redir = node->parent;
	while (temp->parent && temp->parent->token_type == TK_OP \
		&& temp->parent->data.op.type == og_type)
	{
		first_redir = temp->parent;
		temp = temp->parent;
	}
	return (first_redir);
}

/*
	For all files on the way, we open and close them (cuz that's what bash do)
	except for the last one, which will stay open (we'll write in it later)

	The parameter shall be the first file node of the redir subtree
	if the file node has no parents, that's a crash, so let's hope it has one :)
*/
t_s_token	*handle_redir_subtree(t_s_token *node)
{
	t_s_token	*first_redir;

	first_redir = lcl_get_first_redir_node(node, node->parent->data.op.type);
	ft_fprintf(2, "\033[94mHandle_redir_subtree home node %p\033[0m\n", node);
	while (node)
	{
		if (node->token_type == TK_FILE)
		{
			expand_variables(get_shell_data_ptr(NULL), node);
			node->data.file.redir_nodes[0] = first_redir;
			node->data.file.redir_nodes[1] = NULL;
			if (handle_file_bs(node))
				return ((void)dontdoit(2), NULL);
			if (!(!node->right && !node->left && node->parent && node \
			== node->parent->right))
			{
				if (node->data.file.fd > STDERR_FILENO)
					close(node->data.file.fd);
			}
		}
		node = get_next_node(node);
		if (node && node->token_type != TK_FILE && !isbasicredir(node))
			break ;
	}
	return (node);
}
