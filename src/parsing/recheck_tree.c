/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recheck_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:30:17 by loris             #+#    #+#             */
/*   Updated: 2024/02/05 16:12:31 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	replace_file(t_s_token *node)
{
	while (node)
	{
		if (node && node->token_type == TK_OP && (node->data.op.type == 4 || node->data.op.type == 5 || node->data.op.type == 6 || node->data.op.type == 7))
			node->right = new_tokenfile(node->right);
		node = get_next_node(node);
	}
}

t_s_token *new_tokenfile(t_s_token *node_)
{
	t_s_token *node;

	node = our_malloc(sizeof(t_s_token));
	scan_token_extended(node_->data.cmd.args[0], node, TK_FILE);
	node->parent = node_->parent;
	node->left = node_->left;
	node->right = node_->right;
	our_free(node_->data.cmd.args[0]);
	our_free(node_);
	return (node);
}
