/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recheck_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:30:17 by loris             #+#    #+#             */
/*   Updated: 2024/02/07 11:51:20 by aurban           ###   ########.fr       */
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

t_s_token *new_tokenfile(t_s_token *node)
{
	t_s_token	*new_node;
	char	*t;

	new_node = our_malloc(sizeof(t_s_token));
	new_node->token_type = TK_FILE;
	t = node->data.cmd.args[0];
	new_node->data.file.file_path = t;
	new_node->parent = node->parent;
	new_node->left = node->left;
	new_node->right = node->right;
	return (new_node);
}
