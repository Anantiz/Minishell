/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recheck_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:30:17 by loris             #+#    #+#             */
/*   Updated: 2024/01/31 09:55:02 by lkary-po         ###   ########.fr       */
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

t_s_token	*new_tokenfile(t_s_token *node)
{
	t_s_token	*TK;

	TK = our_malloc(sizeof(t_s_token));
	TK->token_type = TK_FILE;
	TK->data.file.file_path = node->data.cmd.args[0];
	TK->parent = node->parent;
	TK->left = node->left;
	TK->right = node->right;
	return (TK);
}