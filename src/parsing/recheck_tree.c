/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recheck_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:30:17 by loris             #+#    #+#             */
/*   Updated: 2024/02/12 19:16:57 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_file(t_s_token *node)
{
	while (node)
	{
		if (node->token_type == TK_OP && (node->data.op.type > PIPE \
			&& node->data.op.type <= REDIR_HEREDOC))
		{
			node->right = new_tokenfile(node->right);
			if (node->right && node->right->token_type == TK_OP && (node->right->data.op.type > PIPE \
				&& node->right->data.op.type <= REDIR_HEREDOC))
			{
				node->right->left = new_tokenfile(node->right->left);
			}
		}
		node = get_next_node(node);
	}
}

t_s_token *new_tokenfile(t_s_token *node)
{
	t_s_token	*new_node;

	if (!node)
		return (NULL);
	print_node(node);
	new_node = our_malloc(sizeof(t_s_token));
	// to fix
	if (!node->data.cmd.args)
		return (node);
	scan_tk_str_file(node->data.cmd.args[0], new_node);
	new_node->parent = node->parent;
	new_node->left = node->left;
	new_node->right = node->right;
	return (new_node);
}